/**
*  @file fn.c
*  @brief This file has the majority of the different functions used in ToS.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "fn.h"
#include <math.h>


/**
* @brief Sets up menu resources, music and character creation assets.
* @param M Menu Structure
* @param m Music structure
* @param x Character creation structure
* @return Nothing
*/
void init_res(Menu* M,Music* m,CC* x){
    //main menu resources
    m->sfx = Mix_LoadMUS("menu_res/CSFX.mp3"); m->mm = Mix_LoadMUS("menu_res/music.mp3");
    M->MBG = IMG_Load("menu_res/menu/menu.png"); /*menu2*/ M->B1 = IMG_Load("menu_res/menu/1H.png"); 
    M->B2 = IMG_Load("menu_res/menu/arrow.png"); M->B1C = IMG_Load("menu_res/menu/1C.png");
    M->B3 = IMG_Load("menu_res/menu/3H.png"); M->B2C = IMG_Load("menu_res/menu/2C.png");
    M->B3C = IMG_Load("menu_res/menu/3C.png"); M->highlight = IMG_Load("menu_res/menu/arrow.png");
    //settings menu resources
    M->SBG = IMG_Load("menu_res/settings/menu_s.png");
    M->S1H = IMG_Load("menu_res/settings/volume_h.png"); M->S2 = IMG_Load("menu_res/settings/S_2.png");
    M->S3 = IMG_Load("menu_res/settings/S_3.png"); M->S4 = IMG_Load("menu_res/settings/S_4.png");
    //cc main resources
    x->ccbg = IMG_Load("menu_res/cc/cc_bg.png"); x->hl = IMG_Load("menu_res/cc/highlight.png"); 
    x->head.h1 = IMG_Load("menu_res/cc/1.png"); x->head.h2 = IMG_Load("menu_res/cc/2.png"); x->head.h3 = IMG_Load("menu_res/cc/3.png");
    x->body.b1 = IMG_Load("menu_res/cc/4.png"); x->body.b2 = IMG_Load("menu_res/cc/5.png"); x->body.b3 = IMG_Load("menu_res/cc/6.png");
    x->feet.f1 = IMG_Load("menu_res/cc/7.png"); x->feet.f2 = IMG_Load("menu_res/cc/8.png"); x->feet.f3 = IMG_Load("menu_res/cc/9.png");
    x->buffer = IMG_Load("menu_res/cc/buffer.png");
}

/**
* @brief Frees the menu and music assets.
* @param M Menu Structure
* @param m Music structure
* @return Nothing
*/
void free_res(Menu M,Music m){
    Mix_FreeMusic(m.sfx);   SDL_FreeSurface(M.SBG);     
    Mix_FreeMusic(m.mm);    SDL_FreeSurface(M.S4); 
    SDL_FreeSurface(M.MBG); 
    SDL_FreeSurface(M.B1);  
    SDL_FreeSurface(M.B2);  
    SDL_FreeSurface(M.B1C); 
    SDL_FreeSurface(M.B2C); 
    SDL_FreeSurface(M.B3);  
    SDL_FreeSurface(M.B3C); 
    SDL_FreeSurface(M.S1H); 
    SDL_FreeSurface(M.S2);  
    SDL_FreeSurface(M.S3); 
}

/**
* @brief Frees the character creation assets.
* @param x Character creation structure
* @return Nothing
*/
void free_res_cc(CC x){
    SDL_FreeSurface(x.body.b1);
    SDL_FreeSurface(x.body.b2);
    SDL_FreeSurface(x.body.b3);
    SDL_FreeSurface(x.feet.f1);
    SDL_FreeSurface(x.feet.f2);
    SDL_FreeSurface(x.feet.f3);
    SDL_FreeSurface(x.head.h1);
    SDL_FreeSurface(x.head.h2);
    SDL_FreeSurface(x.ccbg);
    SDL_FreeSurface(x.head.h3);
    SDL_FreeSurface(x.hl);
}

/**
* @brief Used to display the volume level in the settings menu.
* @param M Menu Structure
* @param scr The screen
* @param x An integer represeting the volume level.
* @return Nothing
*/
void vl_blit(Menu M,SDL_Surface** scr,int x){
    SDL_Rect pos; pos.x = 153; pos.y = 151; pos.w = M.S1H->w; pos.h = M.S1H->h;
    for(int i=0;i<x;i++){
        SDL_BlitSurface(M.S1H,NULL,(*scr),&pos);
        pos.x += pos.w;
    }
}

/**
* @brief Moves the saved data into an array.
* @param T An array.
* @return Nothing
*/
void savefile_to_array(int T[]){
    FILE* f = NULL;
    f = fopen("save.txt","r");
    for(int i=0;i<6;fscanf(f,"%d",&T[i]),i++);
    fclose(f);
}

/**
* @brief Saves the array in a file.
* @param T An array.
* @return Nothing
*/
void array_to_savefile(int T[]){
    FILE* f = NULL;
    f = fopen("save.txt","w");
    for(int i=0;i<6;fprintf(f,"%d\n",T[i]),i++);
    fclose(f);
}

/**
* @brief Settings menu.
* @param M Menu structure.
* @param m Music structure.
* @param scr The screen.
* @param T An array.
* @return Nothing
*/
int settings(Menu M,Music m,SDL_Surface** scr,int T[]){
    SDL_Rect pos; pos.x = 0; pos.y = 0; SDL_Event event; int x,y,i=0,test=0,ftest=0,test2=0; FILE* f = NULL;
    SDL_Rect pos1; pos1.x = 120; pos1.y = 282;
    SDL_Rect pos2; pos2.x = 122; pos2.y = 393;
    SDL_Rect pos3; pos3.x = 983; pos3.y = 567;
    
    printf("%d----------------------------\n",T[4]);

    Mix_PlayMusic(m.mm,-1);

    SDL_BlitSurface(M.SBG,NULL,(*scr),&pos);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    free_res(M,m);
                    return 0;
                break;   
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>120&&x<377)&&(y>281&&y<330)){
                        SDL_BlitSurface(M.S2,NULL,(*scr),&pos1); printf("Yes//1\n"); test = 1; test2 = 1;
                    }
                    else{
                        if((x>120&&x<377)&&(y>391&&y<445)){
                            SDL_BlitSurface(M.S3,NULL,(*scr),&pos2); printf("Yes//2\n"); test = 2; test2 = 2;
                        }
                        else{
                            if((x>982&&x<1060)&&(y>567&&y<645)){
                                SDL_BlitSurface(M.S4,NULL,(*scr),&pos3); printf("Yes//3\n"); test = 3; test2 = 3;
                            }
                            else{
                                if((x>347&&x<374)&&(y>151&&y<182)){
                                    test = 4; 
                                }
                                else{
                                    if((x>113&&x<142)&&(y>157&&y<186)){
                                        test = 5;
                                    }
                                    else{
                                        SDL_BlitSurface(M.SBG,NULL,(*scr),&pos); test = 0;
                                        switch(T[4]){
                                            case 0: vl_blit(M,scr,0); Mix_VolumeMusic(0); break;
                                            case 1: vl_blit(M,scr,1); Mix_VolumeMusic(42); break;
                                            case 2: vl_blit(M,scr,2); Mix_VolumeMusic(84); break;
                                            case 3: vl_blit(M,scr,3); Mix_VolumeMusic(128); break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    SDL_Flip((*scr));
                break; 

                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        switch(ftest){
                            case 0: (*scr) = SDL_SetVideoMode(1366,768,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN); ftest = 1; printf("111\n"); break;
                            case 1: (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF); ftest = 0; printf("000\n"); break;
                        }
                    }

                    if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                        T[0] = 0;
                        T[1] = 0;
                        T[2] = 0;
                        T[3] = 0;
                        T[4] = 2;
                        T[5] = 0;
                        printf("reset--------\n");
                    }

                    if(test == 3 && event.button.button == SDL_BUTTON_LEFT)
                        return 1;
                    
                    if(test == 4 && event.button.button == SDL_BUTTON_LEFT){
                        if(T[4]<3)
                            T[4]++;
                    }
                    
                    if(test == 5 && event.button.button == SDL_BUTTON_LEFT){
                        if(T[4]>0)
                            T[4]--;
                    }
                    
                    
                break;

                case SDL_KEYDOWN:
                    SDL_BlitSurface(M.SBG,NULL,(*scr),&pos); 
                    SDL_Flip((*scr));
                    printf("---%d\n",test2);
                    if(event.key.keysym.sym == SDLK_DOWN){
                        if(test2<4)
                            test2++;
                        else
                            test2 = 1;
                    }
                    if(event.key.keysym.sym == SDLK_UP){
                        if(test2>1)
                            test2--;
                        else
                            test2 = 4;
                    }
                    switch(test2){
                        case 1: 
                            if(event.key.keysym.sym == SDLK_RIGHT){
                                if(T[4]<3)
                                    T[4]++;
                                printf("--%d--\n",T[4]);
                            }
                            if(event.key.keysym.sym == SDLK_LEFT){
                                if(T[4]>0)
                                    T[4]--;
                                printf("--%d--\n",T[4]);
                            }
                        break;
                        case 2: SDL_BlitSurface(M.S2,NULL,(*scr),&pos1); printf("Yes//1 ::%d\n",test2); 
                        test = 1; SDL_Flip((*scr)); break;
                        case 3: SDL_BlitSurface(M.S3,NULL,(*scr),&pos2); printf("Yes//2 ::%d\n",test2); 
                        test = 2; SDL_Flip((*scr)); break;
                        case 4: SDL_BlitSurface(M.S4,NULL,(*scr),&pos3); printf("Yes//3 ::%d\n",test2);
                        test = 3; SDL_Flip((*scr)); break;
                    }
                    if(event.key.keysym.sym == SDLK_SPACE){
                        switch(test2){
                            case 2: 
                                switch(ftest){
                                    case 0: (*scr) = SDL_SetVideoMode(1366,768,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN); ftest = 1; printf("111\n"); break;
                                    case 1: (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF); ftest = 0; printf("000\n"); break;
                                }
                            break;
                            case 3: 
                                T[0] = 0;
                                T[1] = 0;
                                T[2] = 0;
                                T[3] = 0;
                                T[4] = 2;
                                T[5] = 0;
                                printf("reset--------\n");
                            break;
                            case 4:
                                return 1;
                            break;
                        }
                    }
                    switch(T[4]){
                        case 0: vl_blit(M,scr,0); Mix_VolumeMusic(0); break;
                        case 1: vl_blit(M,scr,1); Mix_VolumeMusic(42); break;
                        case 2: vl_blit(M,scr,2); Mix_VolumeMusic(84); break;
                        case 3: vl_blit(M,scr,3); Mix_VolumeMusic(128); break;
                    }
                    SDL_Flip((*scr));
                break;
            } 
        }
    }
}

/**
* @brief Saves a custom character in a text file.
* @param x The head shape.
* @param y The body shape.
* @param z The lower body shape.
* @return Nothing
*/
void savecc(int x,int y,int z){
    FILE* f = NULL;
    f = fopen("savecc.txt","w");
    fprintf(f,"%d %d %d",x,y,z);
    fclose(f);
}

/**
* @brief The menu in which a player can make a custom character.
* @param cc The custom character structure.
* @param m Music structure.
* @param scr The screen.
* @param T An array containing saved data.
* @return 1 if the operation is successful otherwise returns 0.
*/
int cc_menu(CC cc,Music m,SDL_Surface** scr,int T[]){
    SDL_Rect pos; pos.x = 0; pos.y = 0; SDL_Event event; int i=0,x,y,test,testh=0,testb=0,testf=0;
    SDL_Rect pos2; 
    SDL_Rect posh; posh.x = 250-(cc.head.h1->w/2); posh.y = 223-(cc.head.h1->h/2); 
    SDL_Rect posb; posb.x = 250-(cc.head.h1->w/2); posb.y = 364-(cc.head.h1->h/2);
    SDL_Rect posf; posf.x = 250-(cc.head.h1->w/2); posf.y = 506-(cc.head.h1->h/2);
    SDL_Rect posbuff; posbuff.x = 41; posbuff.y = 37;


    Mix_PlayMusic(m.mm,-1);
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_BlitSurface(cc.ccbg,NULL,(*scr),&pos);
    SDL_Flip((*scr));
    while(1){
        SDL_BlitSurface(cc.buffer,NULL,(*scr),&posbuff);
        switch(testh){
            case 1: SDL_BlitSurface(cc.head.h1,NULL,(*scr),&posh); break; 
            case 2: SDL_BlitSurface(cc.head.h2,NULL,(*scr),&posh); break; 
            case 3: SDL_BlitSurface(cc.head.h3,NULL,(*scr),&posh); break; 
        }
        switch(testb){
            case 1: SDL_BlitSurface(cc.body.b1,NULL,(*scr),&posb); break; 
            case 2: SDL_BlitSurface(cc.body.b2,NULL,(*scr),&posb); break; 
            case 3: SDL_BlitSurface(cc.body.b3,NULL,(*scr),&posb); break; 
        }
        switch(testf){
            case 1: printf("%d\n",SDL_BlitSurface(cc.feet.f1,NULL,(*scr),&posf)); break; 
            case 2: printf("%d\n",SDL_BlitSurface(cc.feet.f2,NULL,(*scr),&posf)); break;
            case 3: printf("%d\n",SDL_BlitSurface(cc.feet.f3,NULL,(*scr),&posf)); break;
        }
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return 0;
                break;   
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>609&&x<715)&&(y>80&&y<185)){
                        pos2.x = 610; pos2.y = 81; test = 1;
                        SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                    }
                    else{
                        if((x>854&&x<960)&&(y>80&&y<185)){
                            pos2.x = 855; pos2.y = 81; test = 2;
                            SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                        }else{
                            if((x>1087&&x<1192)&&(y>80&&y<185)){
                                pos2.x = 1088; pos2.y = 81; test = 3;
                                SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                            }
                            else{
                                if((x>609&&x<715)&&(y>298&&y<403)){
                                    pos2.x = 610; pos2.y = 299; test = 4;
                                    SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);        
                                }
                                else{
                                    if((x>847&&x<954)&&(y>302&&y<409)){
                                        pos2.x = 848; pos2.y = 303; test = 5;
                                        SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                                    }
                                    else{
                                        if((x>1085&&x<1191)&&(y>302&&y<408)){
                                            pos2.x = 1086; pos2.y = 303; test = 6;
                                            SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                                        }
                                        else{
                                            if((x>607&&x<712)&&(y>532&&y<639)){
                                                pos2.x = 608; pos2.y = 533; test = 7;
                                                SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                                            }
                                            else{
                                                if((x>838&&x<942)&&(y>520&&y<627)){
                                                    pos2.x = 838; pos2.y = 520; test = 8;
                                                    SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                                                }
                                                else{
                                                    if((x>1057&&x<1163)&&(y>512&&y<615)){
                                                        pos2.x = 1058; pos2.y = 513; test = 9;
                                                        SDL_BlitSurface(cc.hl,NULL,(*scr),&pos2);
                                                    }
                                                    else{
                                                        if((x>1027&&x<1083)&&(y>630&&y<659)){
                                                            test = 10;
                                                            printf("test ---- 10\n");
                                                        }
                                                        else{
                                                            if((x>1094&&x<1151)&&(y>630&&y<656)){
                                                                test = 11;
                                                                printf("test ---- 11\n");
                                                            }
                                                            else{
                                                                SDL_BlitSurface(cc.ccbg,NULL,(*scr),&pos);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        testh = 1;
                    }
                    if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                        testh = 2;
                    }
                    if(test == 3 && event.button.button == SDL_BUTTON_LEFT){
                        testh = 3;
                    }
                    if(test == 4 && event.button.button == SDL_BUTTON_LEFT){
                        testb = 1;
                    }
                    if(test == 5 && event.button.button == SDL_BUTTON_LEFT){
                        testb = 2;
                    }
                    if(test == 6 && event.button.button == SDL_BUTTON_LEFT){
                        testb = 3;
                    }
                    if(test == 7 && event.button.button == SDL_BUTTON_LEFT){
                        testf = 1;
                    }
                    if(test == 8 && event.button.button == SDL_BUTTON_LEFT){
                        testf = 2;
                    }
                    if(test == 9 && event.button.button == SDL_BUTTON_LEFT){
                        testf = 3;
                    }
                    if(test == 10 && event.button.button == SDL_BUTTON_LEFT){
                        savecc(testh,testb,testf); printf("Saved");
                    }
                    if(test == 11 && event.button.button == SDL_BUTTON_LEFT){
                        return 1;
                    }
                break;
            }
        }
        printf("%d %d %d ---\n",testh,testb,testf);
        SDL_Flip(*scr);
    }
}

void game(SDL_Surface** scr);

/**
* @brief Used to pick a character.
* @param m Music structure.
* @param scr The screen.
* @param T An array containing saved data.
* @return Nothing.
*/
void characterpicker(SDL_Surface** scr,int T[],Music m){
    SDL_Surface* img = IMG_Load("media/screens/cs.png"); SDL_Event event;
    SDL_Surface* img2 = IMG_Load("media/player/p2/p2.png"); SDL_Rect pos;  pos.x = 230;   pos.y = 200;
    SDL_Surface* img3 = IMG_Load("media/player/p3/p1.png"); SDL_Rect pos1; pos1.x = 950; pos1.y = 200;
    Mix_PlayMusic(m.mm,-1);
    switch(T[4]){
    case 0: Mix_VolumeMusic(0); break;
    case 1: Mix_VolumeMusic(42); break;
    case 2: Mix_VolumeMusic(84); break;
    case 3: Mix_VolumeMusic(128); break;
    }
    SDL_BlitSurface(img,NULL,(*scr),NULL);
    SDL_BlitSurface(img2,NULL,(*scr),&pos);
    SDL_BlitSurface(img3,NULL,(*scr),&pos1);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
		case SDL_QUIT:
			return;
		break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_RIGHT){
                gamelvl1(scr,0,1);
                gamelvl2(scr,0,1);
                gamelvl3(scr,0,1);
                return;
            }
            if(event.key.keysym.sym == SDLK_LEFT){
                gamelvl1(scr,0,0);
                gamelvl2(scr,0,0);
                gamelvl3(scr,0,0);
                return;
            }
        break;
    }
}
    }
}

/**
* @brief Used to pick the game mode.
* @param m Music structure.
* @param scr The screen.
* @param T An array containing saved data.
* @return Nothing.
*/
void gamemenu(SDL_Surface** scr,int T[],Music m){
    SDL_Surface* img = IMG_Load("media/screens/mselect.png"); SDL_Event event;
    Mix_PlayMusic(m.mm,-1);
    switch(T[4]){
    case 0: Mix_VolumeMusic(0); break;
    case 1: Mix_VolumeMusic(42); break;
    case 2: Mix_VolumeMusic(84); break;
    case 3: Mix_VolumeMusic(128); break;
    }
    SDL_BlitSurface(img,NULL,(*scr),NULL);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return;
                break;
                case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_RIGHT){
                    gamelvl1(scr,1,0);
                    gamelvl2(scr,1,0);
                    gamelvl3(scr,1,0);
                    return;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    characterpicker(scr,T,m);
                    return;
                }
                break;
            }   
        } 
    }
}

/**
* @brief The games main menu.
* @param M Menu structure.
* @param m Music structure.
* @param scr The screen.
* @param T An array containing saved data.
* @param cc CC structure.
* @return Nothing.
*/
void menu(Menu M,Music m,SDL_Surface** scr,int T[],CC cc){
    int x = 0,y = 0; SDL_Event event; int test,test2=0; SDL_Rect pos,posb,posb2,posb3,posb4; int i = 0;
    pos.x = 0; pos.y = 0; pos.w = M.MBG->w; pos.h = M.MBG->h;
    posb.x = 1163; posb.y = 330; posb.w = M.B1->w; posb.h = M.B1->h;
    posb2.x = 1210; posb2.y = 433; posb2.w = M.B2->w; posb2.h = M.B2->h;
    posb3.x = 1194; posb3.y = 528;
    posb4.x = 1168; posb4.y = 627;
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF); 
    Mix_PlayMusic(m.mm,-1);
    switch(T[4]){
    case 0: Mix_VolumeMusic(0); break;
    case 1: Mix_VolumeMusic(42); break;
    case 2: Mix_VolumeMusic(84); break;
    case 3: Mix_VolumeMusic(128); break;
    }
    SDL_BlitSurface(M.MBG,NULL,(*scr),&pos);
    SDL_Flip((*scr));
     while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    free_res(M,m);
                    return;
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y); test2 = 0;
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>1036&&x<1151)&&(y>326&&y<358)){
                        SDL_BlitSurface(M.B2,NULL,(*scr),&posb); printf("Yes//1\n"); test = 1; test2 = 1;
                        //SDL_Flip((*scr));
                    }
                    else{
                        if((x>994&&x<1196)&&(y>429&&y<461)){
                        SDL_BlitSurface(M.B2,NULL,(*scr),&posb2); printf("Yes//2\n"); test = 2; test2 = 2;
                        //SDL_Flip((*scr));
                        }
                        else{
                            if((x>1050&&x<1152)&&(y>629&&y<665)){
                                SDL_BlitSurface(M.B2,NULL,(*scr),&posb4); printf("Yes//3\n"); test = 3; test2 = 3;
                                //SDL_Flip((*scr));
                            }
                            else{
                                if((x>1008&&x<1183)&&(y>527&&y<557)){
                                    SDL_BlitSurface(M.B2,NULL,(*scr),&posb3); printf("Yes//3\n"); test = 4; test2 = 4;
                                    //SDL_Flip((*scr));
                                }
                                else{
                                    SDL_BlitSurface(M.MBG,NULL,(*scr),&pos); printf("No\n"); test = 0;
                                    //SDL_Flip((*scr));
                                }
                            }
                        }
                    }
                    SDL_Flip((*scr));
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        //SDL_BlitSurface(M.B1C,NULL,(*scr),&posb); 
                        Mix_PlayMusic(m.sfx,1);
                        gamemenu(scr,T,m);
                    }
                    else{
                        if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                            //SDL_BlitSurface(M.B2C,NULL,(*scr),&posb2); 
                            Mix_PlayMusic(m.sfx,1);
                                if(!settings(M,m,scr,T))
                                    return;
                            
                        }
                        else{
                            if(test == 3 && event.button.button == SDL_BUTTON_LEFT){
                                //SDL_BlitSurface(M.B3C,NULL,(*scr),&posb3); 
                                Mix_PlayMusic(m.sfx,1);
                                free_res(M,m);
                                return;    
                            }
                            else{
                                if(test == 4 && event.button.button == SDL_BUTTON_LEFT){
                                    //SDL_BlitSurface(M.B3C,NULL,(*scr),&posb3); 
                                    Mix_PlayMusic(m.sfx,1);
                                    credits(scr);    
                                }
                                SDL_BlitSurface(M.MBG,NULL,(*scr),&pos);
                            }
                        }
                    }
                    SDL_Flip((*scr));
                break;
                case SDL_KEYDOWN:
                    SDL_BlitSurface(M.MBG,NULL,(*scr),&pos); SDL_Flip((*scr));
                    printf("---%d\n",test2);
                    if(event.key.keysym.sym == SDLK_DOWN){
                        if(test2<4)
                            test2++;
                        else
                            test2 = 1;
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B2,NULL,(*scr),&posb); printf("Yes//1 ::%d\n",test2); 
                            test = 1; SDL_Flip((*scr)); break;
                            case 2: SDL_BlitSurface(M.B2,NULL,(*scr),&posb2); printf("Yes//2 ::%d\n",test2); 
                            test = 2; SDL_Flip((*scr)); break;
                            case 3: SDL_BlitSurface(M.B2,NULL,(*scr),&posb3); printf("Yes//3 ::%d\n",test2); 
                            test = 3; SDL_Flip((*scr)); break;
                            case 4: SDL_BlitSurface(M.B2,NULL,(*scr),&posb4); printf("Yes//4 ::%d\n",test2); 
                            test = 4; SDL_Flip((*scr)); break;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_UP){
                        if(test2>1)
                            test2--;
                        else
                            test2 = 4;
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B2,NULL,(*scr),&posb); printf("Yes//1 ::%d\n",test2); 
                            test = 1; SDL_Flip((*scr)); break;
                            case 2: SDL_BlitSurface(M.B2,NULL,(*scr),&posb2); printf("Yes//2 ::%d\n",test2); 
                            test = 2; SDL_Flip((*scr)); break;
                            case 3: SDL_BlitSurface(M.B2,NULL,(*scr),&posb3); printf("Yes//3 ::%d\n",test2); 
                            test = 3; SDL_Flip((*scr)); break;
                            case 4: SDL_BlitSurface(M.B2,NULL,(*scr),&posb4); printf("Yes//4 ::%d\n",test2); 
                            test = 4; SDL_Flip((*scr)); break;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_SPACE){
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B1C,NULL,(*scr),&posb); Mix_PlayMusic(m.sfx,1); 
                                    //if(!cc_menu(cc,m,scr,T))
                                    //    return;
                                    gamemenu(scr,T,m);
                            break;
                            
                            case 2: SDL_BlitSurface(M.B2C,NULL,(*scr),&posb2); //Mix_PlayMusic(m.sfx,1); 
                                    if(!settings(M,m,scr,T))
                                        return;
                            break;
                            case 3: credits(scr); break;
                            case 4: 
                            SDL_BlitSurface(M.B3C,NULL,(*scr),&posb3); 
                            Mix_PlayMusic(m.sfx,1);
                            free_res(M,m);
                            return;
                            break;
                        }
                    }
                    SDL_Flip((*scr));
                break;
            } 
        }
    }
}

/**
* @brief Used to initialize player 1 sprites.
* @param p Player structure.
* @return Nothing.
*/
void init_anim_p1(Player* p){
    p->anim.imgI[0] = IMG_Load("media/player/p2/p1.png");
    p->anim.imgI[1] = IMG_Load("media/player/p2/p2.png");
    p->anim.imgD[0] = IMG_Load("media/player/p2/p3_D.png");
    p->anim.imgD[1] = IMG_Load("media/player/p2/p4_D.png");
    p->anim.imgG[0] = IMG_Load("media/player/p2/p3_G.png");
    p->anim.imgG[1] = IMG_Load("media/player/p2/p4_G.png");
    p->anim.imgSD[0] = IMG_Load("media/player/p2/p5_D.png");
    p->anim.imgSD[1] = IMG_Load("media/player/p2/p6_D.png");
    p->anim.imgSD[2] = IMG_Load("media/player/p2/p7_D.png");
    p->anim.imgSG[0] = IMG_Load("media/player/p2/p5_G.png");
    p->anim.imgSG[1] = IMG_Load("media/player/p2/p6_G.png");
    p->anim.imgSG[2] = IMG_Load("media/player/p2/p7_G.png");
}

/**
* @brief Used to initialize player 2 sprites.
* @param p Player structure.
* @return Nothing.
*/
void init_anim_p2(Player* p){
    p->anim.imgI[0] = IMG_Load("media/player/p3/p1.png");
    p->anim.imgI[1] = IMG_Load("media/player/p3/p2.png");
    p->anim.imgD[0] = IMG_Load("media/player/p3/p3_D.png");
    p->anim.imgD[1] = IMG_Load("media/player/p3/p4_D.png");
    p->anim.imgG[0] = IMG_Load("media/player/p3/p3_G.png");
    p->anim.imgG[1] = IMG_Load("media/player/p3/p4_G.png");
    p->anim.imgSD[0] = IMG_Load("media/player/p3/p5_D.png");
    p->anim.imgSD[1] = IMG_Load("media/player/p3/p6_D.png");
    p->anim.imgSD[2] = IMG_Load("media/player/p3/p7_D.png");
    p->anim.imgSG[0] = IMG_Load("media/player/p3/p5_G.png");
    p->anim.imgSG[1] = IMG_Load("media/player/p3/p6_G.png");
    p->anim.imgSG[2] = IMG_Load("media/player/p3/p7_G.png");
}

/**
* @brief Intro animation function.
* @param scr The screen.
* @return Nothing.
*/
void intro(SDL_Surface** scr){
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface *f1,*f2,*f3,*f4;
    f1 = IMG_Load("media/intro/1.png");
    f2 = IMG_Load("media/intro/2.png");
    f3 = IMG_Load("media/intro/3.png");
    f4 = IMG_Load("media/intro/4.png");

    SDL_BlitSurface(f1,NULL,(*scr),NULL);
    SDL_Delay(500);
    SDL_Flip((*scr));
    SDL_BlitSurface(f2,NULL,(*scr),NULL);
    SDL_Delay(500);
    SDL_Flip((*scr));
    SDL_BlitSurface(f3,NULL,(*scr),NULL);
    SDL_Delay(500);
    SDL_Flip((*scr));
    SDL_BlitSurface(f4,NULL,(*scr),NULL);
    SDL_Delay(500);
    SDL_Flip((*scr));
    SDL_Delay(500);
}

/**
* @brief Displays the credits.
* @param scr The screen.
* @return Nothing.
*/
void credits(SDL_Surface** scr){
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* crd = IMG_Load("menu_res/menu/credits.png"); SDL_Event event; //SDL_Rect pos; pos.y = 100; pos.x = 0;
    SDL_BlitSurface(crd,NULL,(*scr),NULL);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    free(crd);
                    return;
                break;   
           }
        }
    }
}

/**
* @brief Grabs the color of a chosen pixel.
* @param pSurface The image from which the function determines colors.
* @param x,y coords.
* @return RGB Color codes.
*/
SDL_Color GetPixel(SDL_Surface* pSurface,int x,int y){
  SDL_Color color;
  Uint32 col = 0 ;

  //determine position
  char* pPosition = ( char* ) pSurface->pixels ;

  //offset by y
  pPosition += ( pSurface->pitch * y ) ;

  //offset by x
  pPosition += ( pSurface->format->BytesPerPixel * x ) ;

  //copy pixel data
  memcpy ( &col , pPosition , pSurface->format->BytesPerPixel ) ;

  //convert color
  SDL_GetRGB ( col , pSurface->format , &color.r , &color.g , &color.b ) ;
  return ( color ) ;
}

/**
* @brief Checks for collision with designated colors on the map.
* @param img The image from which the function determines colors and checks for collision.
* @param pos coords.
* @param z An integer used to determine whether the function is going to check for collision on a vertical or horizontal axis.
* @param type An integer used to determine whether the function is going to check for collision beneath or above the player.
* @return true or false as an int.
*/
int collisioncheck(SDL_Surface* img,SDL_Rect pos,int z,int type){
    SDL_Color C;
    if(type)
        C = GetPixel(img,pos.x+70,pos.y+228+z);
    else
        C = GetPixel(img,pos.x+70+z,pos.y+228);
    //printf("--printf("--%d-- --%d-- --%d--  %d\n",C.r,C.g,C.b,C.r && C.g && C.b);
    if(C.r == 237 && C.g == 28 && C.b == 36)
        return 2;
    else
        if(C.r && C.g && C.b)
            return 1;
    return 0;
}

/*void hp_blit(Player P,SDL_Surface** scr,int x){
    SDL_Rect pos; SDL_Surface* img = IMG_Load("media/levels/level1.png");
    for(int i=0;i<x;i++){
        SDL_BlitSurface(,NULL,(*scr),&pos);
        pos.x += pos.w;
    }
}*/

/**
* @brief A function that blits how much time is left until the game is over.
* @param scr The screen.
* @param T An array that contains digits ranging from 0-9.
* @param x The integer to be blitted.
* @return Nothing.
*/
void BlitTime(int x,SDL_Surface* T[],SDL_Surface** scr){
    int t[3];
    
    SDL_Rect p1,p2,p3; p1.y = 40; p2.y = 40; p3.y = 40; p1.x = 1160; p2.x = 1186; p3.x = 1212; 
    t[0] = x/100; t[1] = (x/10)%10; t[2] = (x%100)%10;
    
    SDL_BlitSurface(T[t[0]],NULL,(*scr),&p1);
    SDL_BlitSurface(T[t[1]],NULL,(*scr),&p2);
    SDL_BlitSurface(T[t[2]],NULL,(*scr),&p3);
       
}

/**
* @brief A function that blits the player's score.
* @param scr The screen.
* @param T An array that contains digits ranging from 0-9.
* @param x The integer to be blitted.
* @return Nothing.
*/
void BlitScore(int x,SDL_Surface* T[],SDL_Surface** scr){
    int t[3];
    
    SDL_Rect p1,p2,p3; p1.y = 95; p2.y = 95; p3.y = 95; p1.x = 1160; p2.x = 1186; p3.x = 1212; 
    t[0] = x/100; t[1] = (x/10)%10; t[2] = (x%100)%10;
    
    SDL_BlitSurface(T[t[0]],NULL,(*scr),&p1);
    SDL_BlitSurface(T[t[1]],NULL,(*scr),&p2);
    SDL_BlitSurface(T[t[2]],NULL,(*scr),&p3);
       
}

/**
* @brief This function loads all the puzzles.
* @param p An array of puzzles.
* @return Nothing.
*/
void init_puzzle(puzzle p[]){
    p[0].img = IMG_Load("media/puzzles/P1.png"); p[0].rep = SDLK_LEFT;
    p[1].img = IMG_Load("media/puzzles/P2.png"); p[1].rep = SDLK_RIGHT;
    p[2].img = IMG_Load("media/puzzles/P3.png"); p[2].rep = SDLK_DOWN;
    p[3].img = IMG_Load("media/puzzles/P4.png"); p[3].rep = SDLK_UP;
    p[4].img = IMG_Load("media/puzzles/P5.png"); p[4].rep = SDLK_UP;
}

/**
* @brief This function executes a puzzle minigame.
* @param p An array of puzzles.
* @param scr The screen.
* @return An integer representing whether the player guessed the puzzle right.
*/
int enigme(SDL_Surface** scr,puzzle p){
    SDL_Event event;
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    while(1){
        SDL_BlitSurface(p.img,NULL,(*scr),NULL);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return -1;
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == p.rep){
                        printf("Yes\n");
                        return 1;
                    }
                    else{
                        printf("No\n");
                        return 0;
                    }
                break;
            }
        }
        SDL_Flip((*scr));
    }
}

/**
* @brief This function loads the bat ennemy.
* @param B The bat structure.
* @return Nothing.
*/
void initialiser_bat(bat* B)
{
    B->position_bat.x = 640;
    B->position_bat.y = 0;
    B->position_bat.h = 100;
    B->position_bat.w = 100;
    B->ac = 0;
    B->image_bat[0] = IMG_Load("media/objects/bat1.png"); 
    B->image_bat[1] = IMG_Load("media/objects/bat2.png");    
}

/**
* @brief Returns an integer between 0 and 100.
* @return The integer.
*/
int SOSO(){ // 50/50
int t ;
srand(time(NULL));
t=rand()%101;
if (t < 50) 
  return 1;
  else return 0;
}

/**
* @brief This function randomly moves a 2nd entity (in this case the bat).
* @param B The bat structure.
* @param scr The screen.
* @param y Used to animate the bat.
* @return Nothing.
*/
void deplacement_aleatoire(bat* B,SDL_Surface** scr,int y)
{
    int x=100;
    if(SOSO()==1){
         x=rand()%641;
     }else{
         x=rand()%641 +641 ;
         }
    int posfin=4000 , posdeb=0;
    if(posfin - B->position_bat.y > 0){ 
    if(B->position_bat.x == x){
    srand(time(NULL));
    if(SOSO()==1){
        x=rand()%641;
    }else{
        x=rand()%641 +641 ;
        }
    }
    if(B->position_bat.x < x){
        B->position_bat.x+=2;
        B->position_bat.y+=2;
    } else if (B->position_bat.x > x){
     B->position_bat.x-=2;
     B->position_bat.y+=2;
    }
//printf("%d %d %xbat\n",B->position_bat.x,B->position_bat.y,B->image_bat);
SDL_BlitSurface(B->image_bat[y%2],NULL,(*scr),&B->position_bat);
}
}

/**
* @brief This function determines whether a collision between the player and the ennemy has occured.
* @param pp Player position.
* @param ep Ennemy position.
* @return True or false as an integer.
*/
int PEcollision(SDL_Rect pp,SDL_Rect ep){
    if((pp.x+pp.w) >= ep.x && pp.x <= (ep.x+ep.w) && (pp.y+pp.h) >= ep.y && pp.y <= (ep.y+ep.h))
        return 1;
    return 0; 
}

/**
* @brief This function sets up the player structure.
* @param p Player structure.
* @param n Used to choose which character to load.
* @return Nothing.
*/
void player_setup(Player* p,int n){
    
    if(n == 1)
        init_anim_p1(p);
    else
        init_anim_p2(p);

    p->frames = 0;
    p->jframes = 0;
    p->ic = 0;
    p->jc = 0;
    p->rc = 0;
    p->lc = 0;
    p->Itest = 1;
    p->score = 100;
    p->posJ.x = 640;
    p->posJ.y = 400;
    p->posJ.h = 228;
    p->posJ.w = 139;

}

/**
* @brief This function sets up the array containing pictures of digits.
* @param T Said array.
* @return Nothing.
*/
void init_numbers(SDL_Surface* T[]){
    T[0] = IMG_Load("media/temps/0.png");
    T[1] = IMG_Load("media/temps/1.png");
    T[2] = IMG_Load("media/temps/2.png");
    T[3] = IMG_Load("media/temps/3.png");
    T[4] = IMG_Load("media/temps/4.png");
    T[5] = IMG_Load("media/temps/5.png");
    T[6] = IMG_Load("media/temps/6.png");
    T[7] = IMG_Load("media/temps/7.png");
    T[8] = IMG_Load("media/temps/8.png");
    T[9] = IMG_Load("media/temps/9.png");
}

/**
* @brief This function sets up the coins in the game.
* @param C Said coins.
* @return Nothing.
*/
void init_coins(coin* C){
    C->value = 50; C->ac = 0; C->r = 40;
    C->cimg[0] = IMG_Load("media/objects/coin1.png");
    C->cimg[1] = IMG_Load("media/objects/coin2.png");
    C->cimg[2] = IMG_Load("media/objects/coin3.png");
    C->cimg[3] = IMG_Load("media/objects/coin4.png");
    C->cimg[4] = IMG_Load("media/objects/coin5.png");
    C->cimg[5] = IMG_Load("media/objects/coin6.png");
}

/**
* @brief This function displays the coins in the game.
* @param C Said coins.
* @return Nothing.
*/
void displaycoins(coin C,SDL_Surface** scr){
    SDL_BlitSurface(C.cimg[C.ac%6],NULL,(*scr),&C.pos);
}

/**
* @brief This function is literally useless.
* @param C USELESS.
* @return Nothing.
*/
int collisiontrigo(coin P1,coin P2){
	SDL_Rect centreA, centreB;
	centreA.x=P1.pos.x+P1.r;
	centreA.y=P1.pos.y+P1.r;
	centreB.x=P2.pos.x+P2.r;
	centreB.y=P2.pos.y+P2.r;
	
	
			
   int d = sqrt((centreB.x-centreA.x)*(centreB.y-centreA.y))+((centreB.y-centreA.y)*(centreB.x-centreA.y));

   if (d>(P1.r)+(P2.r)){
	printf("0\n");
      return 0;
	}
   else{
	printf("1\n");
      return 1;
	}
}

/**
* @brief Displays the gameover screen.
* @param scr The screen.
* @return Nothing.
*/
void deathscreen(SDL_Surface** scr){
    SDL_Surface* img = IMG_Load("media/screens/gameover.png"); SDL_Event event;
    SDL_BlitSurface(img,NULL,(*scr),NULL);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
		case SDL_QUIT:
			return;
		break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_SPACE)
                return;
        break;
        }
        }
    }
}

/**
* @brief This function displays the victory screen.
* @param scr screen.
* @return Nothing.
*/
void victory(SDL_Surface** scr){
    SDL_Surface* img = IMG_Load("media/screens/gj.png"); SDL_Event event;
    SDL_BlitSurface(img,NULL,(*scr),NULL);
    SDL_Flip((*scr));
    while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
		case SDL_QUIT:
			return;
		break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_SPACE)
                return;
        break;
        }
        }
    }
}

/**
* @brief Our games 1st level.
* @param scr The screen.
* @param n The number of players.
* @param s Determines which character to load if the player chose to play by himself.
* @return Nothing.
*/
void gamelvl1(SDL_Surface** scr,int n,int s){
    //Set up
    SDL_Rect pos; int i=0;
    int z = 3725; int x = 0,y = 0; int time = 100;  SDL_Rect posHG; puzzle puz[5]; int score = 100; bat b; initialiser_bat(&b);
    SDL_Event event; Player p,p2; coin C,CP; init_coins(&C); C.pos.y = 1; C.pos.x = 640;
    
    SDL_Surface* hourglass = IMG_Load("media/temps/hourglass.png");
    SDL_Surface* imglvl = IMG_Load("media/levels/lvl1/level1.png");
    SDL_Surface* imglvlm = IMG_Load("media/levels/lvl1/level1m.png");
    
    //Setting up background coords
    pos.x = 0; pos.y = 3725; pos.h = 720; pos.w = 1280;
    
    posHG.x = 1110; posHG.y = 40;
    Uint32 tempsPrecedent = 0, tempsActuel = 0,tempsPrecedent2 = 0, tempsActuel2 = 0;
    Uint32 tempsPrecedentS = 0, tempsActuelS = 0,tempsPrecedentS2 = 0, tempsActuelS2 = 0;
    Uint32 tempsPrecedentA = 0, tempsActuelA = 0,tempsPrecedentA2 = 0, tempsActuelA2 = 0;
    Uint32 tempsPrecedentAr = 0, tempsActuelAr = 0,tempsPrecedentAr2 = 0, tempsActuelAr2 = 0;
    Uint32 tempsPrecedentT = 0, tempsActuelT = 0,tempsPrecedentT2 = 0, tempsActuelT2 = 0;
    SDL_EnableKeyRepeat(10,10);
    init_puzzle(puz);
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    //Character set up
    switch(n){
        case 0: if(s) player_setup(&p,2); else player_setup(&p,1); break;
        case 1: player_setup(&p,1); player_setup(&p2,2); break;       
    }

    //Numbers set up
    SDL_Surface* T[10];
    init_numbers(T);
    
    //Game loop
    while(1){
        //SDL_GetMouseState(&x,&y);
        //printf("%d,%d ::%d\n",x,y,i); i++;
        
        //scrolling
        tempsActuelS = SDL_GetTicks();
        if (tempsActuelS - tempsPrecedentS > 2){
            if(z>100)
                z-=2;
            if(0 < C.pos.y < 720)
                C.pos.y += 2;
            pos.y = z;
            tempsPrecedentS = tempsActuelS;
        }

        SDL_BlitSurface(imglvl,&pos,(*scr),NULL);
        
        //Idle animation counter 
        tempsActuelA = SDL_GetTicks();
        if(tempsActuelA - tempsPrecedentA > 100){
            if(!p.jframes && !p.frames){
                p.ic++;
            }
            if(n){
                    if(!p2.jframes && !p2.frames){
                        p2.ic++;
                }
            }
            tempsPrecedentA = tempsActuelA;
        }

        //if character is idle play idle animation
        if(p.Itest)
            SDL_BlitSurface(p.anim.imgI[p.ic%2],NULL,(*scr),&p.posJ); 
        if(n)
            if(p2.Itest)
                SDL_BlitSurface(p2.anim.imgI[p2.ic%2],NULL,(*scr),&p2.posJ); 
        

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return;
                break;
                case SDL_KEYDOWN:
                   if(event.key.keysym.sym == SDLK_RIGHT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        tempsActuelAr = SDL_GetTicks();
                        //Right mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.rc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.posJ.x<920){
                            if(p.frames < 5){
                                p.posJ.x += 4;
                            }
                            else{
                                p.posJ.x += 20;
                            }
                        }
                        
                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSD[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSD[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSD[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgD[p.rc%2],NULL,(*scr),&p.posJ);
                    }

                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.lc++;
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        //Left mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.lc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.posJ.x>214){
                            if(p.frames < 5){
                            p.posJ.x -= 4;
                        }
                        else{
                            p.posJ.x -= 20;
                        }
                        }
                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSG[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSG[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSG[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgG[p.lc%2],NULL,(*scr),&p.posJ);
                    }
                    
                    //Jump initiation
                    if(event.key.keysym.sym == SDLK_UP){
                        p.jframes = 50;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                         enigme(scr,puz[0]);
                break;
                case SDL_KEYUP: //Frames and idle state reset
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        p.frames = 0; p.rc = 0; p.Itest = 1;
                    }
                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.frames = 0; p.lc = 0; p.Itest = 1;
                    }
                break;
            }
            if(n){
            
                switch(event.type){
                    case SDL_QUIT:
                        return;
                    break;
                    case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_f){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            tempsActuelAr2 = SDL_GetTicks();
                            //Right mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.rc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.posJ.x+139 < 1280){
                                if(p2.frames < 5){
                                    p2.posJ.x += 4;
                                }
                                else{
                                    p2.posJ.x += 20;
                                }
                            }

                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSD[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSD[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSD[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgD[p2.rc%2],NULL,(*scr),&p2.posJ);
                        }

                        if(event.key.keysym.sym == SDLK_s){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.lc++;
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            //Left mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.lc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.frames < 5){
                                p2.posJ.x -= 4;
                            }
                            else{
                                p2.posJ.x -= 20;
                            }
                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSG[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSG[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSG[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgG[p2.lc%2],NULL,(*scr),&p2.posJ);
                        }
                        
                        //Jump initiation
                        if(event.key.keysym.sym == SDLK_e){
                            p2.jframes = 50;
                        }

                        if(event.key.keysym.sym == SDLK_RETURN)
                            enigme(scr,puz[0]);
                    break;
                    case SDL_KEYUP: //Frames and idle state reset
                        if(event.key.keysym.sym == SDLK_f){
                            p2.frames = 0; p2.rc = 0; p2.Itest = 1;
                        }
                        if(event.key.keysym.sym == SDLK_s){
                            p2.frames = 0; p2.lc = 0; p2.Itest = 1;
                        }
                    break;
                }
            }
        }
        
        //Jump code

        tempsActuel = SDL_GetTicks();
        if((p.jframes > 0) && (tempsActuel - tempsPrecedent > 20)){
            tempsPrecedent = tempsActuel;
            if(p.jframes > 27){
                p.posJ.y -= 10;
                p.jframes --;
            }
            else{
                p.posJ.y += 10;
                p.jframes --;
            }
        }
        if(n){
            tempsActuel2 = SDL_GetTicks();
            if((p2.jframes > 0) && (tempsActuel2 - tempsPrecedent2 > 20)){
                tempsPrecedent2 = tempsActuel2;
                if(p2.jframes > 27){
                    p2.posJ.y -= 10;
                    p2.jframes --;
                }
                else{
                    p2.posJ.y += 10;
                    p2.jframes --;
                }
            }
        }


        //collision check

        //SDL_GetMouseState(&x,&y);
        //printf("%d %d \n",x,y);
        
        switch(collisioncheck(imglvlm,p.posJ,z,1)){
            case 1:
                if(p.posJ.y + 228 > 300)
                    if(p.jframes < 28){
                        p.posJ.y += 10;
                        p.jframes = 0;
                    }
            break;
            case 2:
                if(p.score){
                    p.score --;
                }
            break;
        }
        
        if(PEcollision(p.posJ,b.position_bat)){
            if(p.score)
                p.score --; 
        }

        if(n){
            if(PEcollision(p2.posJ,b.position_bat)){
                if(p2.score)
                    p2.score --; 
        }
        }

        if(PEcollision(p.posJ,b.position_bat)){
            if(p.score)
                p.score --; 
        }

        if(n){
            if(PEcollision(p2.posJ,b.position_bat)){
                if(p2.score)
                    p2.score --; 
        }
        }

        if(n){
            switch(collisioncheck(imglvlm,p2.posJ,z,1)){
            case 1:
                if(p2.posJ.y + 228 > 300)
                    if(p2.jframes < 28){
                        p2.posJ.y += 10;
                        p2.jframes = 0;
                    }
            break;
            case 2:
                if(p2.score){
                    p2.score --;
                }
            break;
        }
        }

        CP.pos = p.posJ;
        if(PEcollision(p.posJ,C.pos)){
            p.score += 100;
            C.pos.y = 1000;
        }
        if(n)
            if(PEcollision(p2.posJ,C.pos)){
                p.score += 100;
                C.pos.y = 1000;
            }

        //Time management
        tempsActuelT = SDL_GetTicks();
        if (tempsActuelT - tempsPrecedentT > 1000){
            time--; b.ac ++; C.ac++;
            tempsPrecedentT = tempsActuelT;
        }
        SDL_BlitSurface(hourglass,NULL,(*scr),&posHG);
        BlitTime(time,T,scr);
        
        if(n)
            BlitScore(p.score + p2.score,T,scr);
        else
            BlitScore(p.score,T,scr);

        //2nd Entities management
        if(b.position_bat.y<p.posJ.y+z)
            deplacement_aleatoire(&b,scr,b.ac);
        displaycoins(C,scr);
        //SDL_BlitSurface(C.cimg[C.ac%6],NULL,(*scr),&p.posJ);

        //End game conditions
        
        if(n){
            if(!p.score && !p2.score || !time){
                deathscreen(scr);
                return;
            }
        }
        else{
            if(!p.score || !time){
                deathscreen(scr);
                return;
        }
        }

        printf("%d %d %d\n",z,p.posJ.x,p.posJ.y);
        if(n){
            if(z == 99 && p.posJ.y == p2.posJ.y == 120 && p.posJ.x == p2.posJ.x == 920)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        else{
            if(z == 99 && p.posJ.y == 120 && p.posJ.x == 920)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        SDL_Flip((*scr));
    }
}

/**
* @brief Enables parallax scrolling in the game.
* @param scr The screen.
* @param x The scrolling factor.
* @param b1-3 The different backgrounds.
* @param p1-3 The different positions.
* @return Nothing.
*/
void parallax_scrolling(SDL_Surface** scr,int x,SDL_Surface* b1,SDL_Surface* b2,SDL_Surface* b3,SDL_Rect* p1,SDL_Rect* p2,SDL_Rect* p3){
    
    //printf("%d \n",x);
    p1->x = x+4; p2->x = x+2; p3->x = x;
    SDL_BlitSurface(b3,p3,(*scr),NULL);
    SDL_BlitSurface(b2,p2,(*scr),NULL);
    SDL_BlitSurface(b1,p1,(*scr),NULL);
    SDL_Flip((*scr));
}

/**
* @brief Our games 2st level.
* @param scr The screen.
* @param n The number of players.
* @param s Determines which character to load if the player chose to play by himself.
* @return Nothing.
*/
void gamelvl2(SDL_Surface** scr,int n,int s){
    //Set up
    SDL_Rect pos1,pos2,pos3; int i=0;
    int z = 0; int x = 0,y = 0; int time = 120;  SDL_Rect posHG; puzzle puz[5]; int score = 100;
    SDL_Event event; Player p,p2; coin C,CP; init_coins(&C); C.pos.y = 1; C.pos.x = 640;
    
    SDL_Surface* hourglass = IMG_Load("media/temps/hourglass.png");
    SDL_Surface* imglvlm = IMG_Load("media/levels/lvl2/levelm.png");
    SDL_Surface* b1 = IMG_Load("media/levels/lvl2/level.png");
    SDL_Surface* b2 = IMG_Load("media/levels/lvl2/LEVELBG1.png");
    SDL_Surface* b3 = IMG_Load("media/levels/lvl2/LEVELBG2.png");

    //Setting up the background coords
    pos1.y = 0; pos2.y = 0; pos3.y = 0;
    pos1.w = 1280; pos2.w = 1280; pos3.w = 1280;
    pos1.h = 720; pos2.h = 720; pos3.h = 720;

    posHG.x = 1110; posHG.y = 40;
    Uint32 tempsPrecedent = 0, tempsActuel = 0,tempsPrecedent2 = 0, tempsActuel2 = 0;
    Uint32 tempsPrecedentS = 0, tempsActuelS = 0,tempsPrecedentS2 = 0, tempsActuelS2 = 0;
    Uint32 tempsPrecedentA = 0, tempsActuelA = 0,tempsPrecedentA2 = 0, tempsActuelA2 = 0;
    Uint32 tempsPrecedentAr = 0, tempsActuelAr = 0,tempsPrecedentAr2 = 0, tempsActuelAr2 = 0;
    Uint32 tempsPrecedentT = 0, tempsActuelT = 0,tempsPrecedentT2 = 0, tempsActuelT2 = 0;
    SDL_EnableKeyRepeat(10,10);
    
    //Character set up
    switch(n){
        case 0: if(s) player_setup(&p,2); else player_setup(&p,1); break;
        case 1: player_setup(&p,1); player_setup(&p2,2); break;       
    }

    init_puzzle(puz);
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    //Numbers set up
    SDL_Surface* T[10];
    init_numbers(T);
    
    //Game loop
    while(1){
        //SDL_GetMouseState(&x,&y);
        //printf("%d,%d ::%d\n",x,y,i); i++;
        
        //scrolling
        tempsActuelS = SDL_GetTicks();
        if (tempsActuelS - tempsPrecedentS > 2){
            if(z<3500){
                z+=2;
                p.posJ.x -= 2;
                if(n)
                    p2.posJ.x -= 2;
            }
            tempsPrecedentS = tempsActuelS;
        }

        parallax_scrolling(scr,z,b1,b2,b3,&pos1,&pos2,&pos3);
        
        //Idle animation counter 
        tempsActuelA = SDL_GetTicks();
        if(tempsActuelA - tempsPrecedentA > 100){
            if(!p.jframes && !p.frames){
                p.ic++;
                if(n){
                    if(!p2.jframes && !p2.frames){
                        p2.ic++;
                    }
                }
            }
            tempsPrecedentA = tempsActuelA;
        }

        //if character is idle play idle animation
        if(p.Itest)
            SDL_BlitSurface(p.anim.imgI[p.ic%2],NULL,(*scr),&p.posJ); 
        if(n)
            if(p2.Itest)
                SDL_BlitSurface(p2.anim.imgI[p2.ic%2],NULL,(*scr),&p2.posJ); 
        

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return;
                break;
                case SDL_KEYDOWN:
                   if(event.key.keysym.sym == SDLK_RIGHT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        tempsActuelAr = SDL_GetTicks();
                        //Right mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.rc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.posJ.x+139 < 1280){
                            if(p.frames < 5){
                                p.posJ.x += 4;
                            }
                            else{
                                p.posJ.x += 20;
                            }
                        }

                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSD[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSD[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSD[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgD[p.rc%2],NULL,(*scr),&p.posJ);
                    }

                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.lc++;
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        //Left mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.lc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.frames < 5){
                            p.posJ.x -= 4;
                        }
                        else{
                            p.posJ.x -= 20;
                        }
                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSG[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSG[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSG[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgG[p.lc%2],NULL,(*scr),&p.posJ);
                    }
                    
                    //Jump initiation
                    if(event.key.keysym.sym == SDLK_UP){
                        p.jframes = 50;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                         enigme(scr,puz[0]);
                break;
                case SDL_KEYUP: //Frames and idle state reset
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        p.frames = 0; p.rc = 0; p.Itest = 1;
                    }
                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.frames = 0; p.lc = 0; p.Itest = 1;
                    }
                break;
            }
        }

        if(n){
            
                switch(event.type){
                    case SDL_QUIT:
                        return;
                    break;
                    case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_f){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            tempsActuelAr2 = SDL_GetTicks();
                            //Right mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.rc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.posJ.x+139 < 1280){
                                if(p2.frames < 5){
                                    p2.posJ.x += 4;
                                }
                                else{
                                    p2.posJ.x += 20;
                                }
                            }

                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSD[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSD[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSD[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgD[p2.rc%2],NULL,(*scr),&p2.posJ);
                        }

                        if(event.key.keysym.sym == SDLK_s){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.lc++;
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            //Left mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.lc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.frames < 5){
                                p2.posJ.x -= 4;
                            }
                            else{
                                p2.posJ.x -= 20;
                            }
                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSG[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSG[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSG[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgG[p2.lc%2],NULL,(*scr),&p2.posJ);
                        }
                        
                        //Jump initiation
                        if(event.key.keysym.sym == SDLK_e){
                            p2.jframes = 50;
                        }

                        if(event.key.keysym.sym == SDLK_RETURN)
                            enigme(scr,puz[0]);
                    break;
                    case SDL_KEYUP: //Frames and idle state reset
                        if(event.key.keysym.sym == SDLK_f){
                            p2.frames = 0; p2.rc = 0; p2.Itest = 1;
                        }
                        if(event.key.keysym.sym == SDLK_s){
                            p2.frames = 0; p2.lc = 0; p2.Itest = 1;
                        }
                    break;
                }
            }
        
        //Jump code

        tempsActuel = SDL_GetTicks();
        if((p.jframes > 0) && (tempsActuel - tempsPrecedent > 20)){
            tempsPrecedent = tempsActuel;
            if(p.jframes > 27){
                p.posJ.y -= 10;
                p.jframes --;
            }
            else{
                p.posJ.y += 10;
                p.jframes --;
            }
        }
        if(n){
            tempsActuel2 = SDL_GetTicks();
            if((p2.jframes > 0) && (tempsActuel2 - tempsPrecedent2 > 20)){
                tempsPrecedent2 = tempsActuel2;
                if(p2.jframes > 27){
                    p2.posJ.y -= 10;
                    p2.jframes --;
                }
                else{
                    p2.posJ.y += 10;
                    p2.jframes --;
                }
            }
        }
        
        //collision check

        /*SDL_GetMouseState(&x,&y);
        cu = GetPixel(imglvlm,x+z,y);
        printf("%d %d %d\n",cu.r,cu.g,cu.b);*/

        switch(collisioncheck(imglvlm,p.posJ,z,0)){
            case 1:
                if(p.posJ.y + 228 > 300)
                    if(p.jframes < 28){
                        p.posJ.y += 10;
                        p.jframes = 0;
                    }
            break;
            case 2:
                if(p.score){
                    p.score --;
                }
            break;
        }

        if(n){
            switch(collisioncheck(imglvlm,p2.posJ,z,0)){
            case 1:
                if(p2.posJ.y + 228 > 300)
                    if(p2.jframes < 28){
                        p2.posJ.y += 10;
                        p2.jframes = 0;
                    }
            break;
            case 2:
                if(p2.score){
                    p2.score --;
                }
            break;
        }
        }

        //Time management
        tempsActuelT = SDL_GetTicks();
        if (tempsActuelT - tempsPrecedentT > 1000){
            time--;
            tempsPrecedentT = tempsActuelT;
        }
        SDL_BlitSurface(hourglass,NULL,(*scr),&posHG);
        BlitTime(time,T,scr);
        
        if(n)
            BlitScore(p.score + p2.score,T,scr);
        else
            BlitScore(p.score,T,scr);

        //End game conditions
        
        if(n){
            if(!p.score && !p2.score || !time){
                deathscreen(scr);
                return;
            }
        }
        else{
            if(!p.score || !time){
                deathscreen(scr);
                return;
        }
        }

        printf("%d %d %d\n",z,p.posJ.x,p.posJ.y);
        if(n){
            if(z == 3500 && p.posJ.y == p2.posJ.y == 450 && p.posJ.x == p2.posJ.x < 1200)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        else{
            if(z == 3500 && p.posJ.y == 450 && p.posJ.x < 1200)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        
        SDL_Flip((*scr));
    }
}

/**
* @brief Our games final level.
* @param scr The screen.
* @param n The number of players.
* @param s Determines which character to load if the player chose to play by himself.
* @return Nothing.
*/
void gamelvl3(SDL_Surface** scr,int n,int s){
    //Set up
    SDL_Rect pos1,pos2,pos3; int i=0;
    int z = 0; int x = 0,y = 0; int time = 120;  SDL_Rect posHG; puzzle puz[5]; int score = 100;
    SDL_Event event; Player p,p2; coin C,CP; init_coins(&C); C.pos.y = 1; C.pos.x = 640;
    
    SDL_Surface* hourglass = IMG_Load("media/temps/hourglass.png");
    SDL_Surface* imglvlm = IMG_Load("media/levels/lvl3/levelm.png");
    SDL_Surface* b1 = IMG_Load("media/levels/lvl3/level.png");
    SDL_Surface* b2 = IMG_Load("media/levels/lvl3/LEVELBG1.png");
    SDL_Surface* b3 = IMG_Load("media/levels/lvl3/LEVELBG2.png");

    //Setting up the background coords
    pos1.y = 0; pos2.y = 0; pos3.y = 0;
    pos1.w = 1280; pos2.w = 1280; pos3.w = 1280;
    pos1.h = 720; pos2.h = 720; pos3.h = 720;

    posHG.x = 1110; posHG.y = 40;
    Uint32 tempsPrecedent = 0, tempsActuel = 0,tempsPrecedent2 = 0, tempsActuel2 = 0;
    Uint32 tempsPrecedentS = 0, tempsActuelS = 0,tempsPrecedentS2 = 0, tempsActuelS2 = 0;
    Uint32 tempsPrecedentA = 0, tempsActuelA = 0,tempsPrecedentA2 = 0, tempsActuelA2 = 0;
    Uint32 tempsPrecedentAr = 0, tempsActuelAr = 0,tempsPrecedentAr2 = 0, tempsActuelAr2 = 0;
    Uint32 tempsPrecedentT = 0, tempsActuelT = 0,tempsPrecedentT2 = 0, tempsActuelT2 = 0;
    SDL_EnableKeyRepeat(10,10);
    
    //Character set up
    switch(n){
        case 0: if(s) player_setup(&p,2); else player_setup(&p,1); break;
        case 1: player_setup(&p,1); player_setup(&p2,2); break;       
    }

    init_puzzle(puz);
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    //Numbers set up
    SDL_Surface* T[10];
    init_numbers(T);
    
    //Game loop
    while(1){
        //SDL_GetMouseState(&x,&y);
        //printf("%d,%d ::%d\n",x,y,i); i++;
        
        //scrolling
        tempsActuelS = SDL_GetTicks();
        if (tempsActuelS - tempsPrecedentS > 2){
            if(z<3500){
                z+=2;
                p.posJ.x -= 2;
                if(n)
                    p2.posJ.x -= 2;
            }
            tempsPrecedentS = tempsActuelS;
        }

        parallax_scrolling(scr,z,b1,b2,b3,&pos1,&pos2,&pos3);
        
        //Idle animation counter 
        tempsActuelA = SDL_GetTicks();
        if(tempsActuelA - tempsPrecedentA > 100){
            if(!p.jframes && !p.frames){
                p.ic++;
                if(n){
                    if(!p2.jframes && !p2.frames){
                        p2.ic++;
                    }
                }
            }
            tempsPrecedentA = tempsActuelA;
        }

        //if character is idle play idle animation
        if(p.Itest)
            SDL_BlitSurface(p.anim.imgI[p.ic%2],NULL,(*scr),&p.posJ); 
        if(n)
            if(p2.Itest)
                SDL_BlitSurface(p2.anim.imgI[p2.ic%2],NULL,(*scr),&p2.posJ); 
        

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return;
                break;
                case SDL_KEYDOWN:
                   if(event.key.keysym.sym == SDLK_RIGHT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        tempsActuelAr = SDL_GetTicks();
                        //Right mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.rc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.posJ.x+139 < 1280){
                            if(p.frames < 5){
                                p.posJ.x += 4;
                            }
                            else{
                                p.posJ.x += 20;
                            }
                        }

                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSD[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSD[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSD[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgD[p.rc%2],NULL,(*scr),&p.posJ);
                    }

                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.Itest = 0;
                        tempsActuel = SDL_GetTicks();
                        if ((tempsActuel - tempsPrecedent > 50)&&(p.frames < 50)){
                            p.lc++;
                            p.frames ++;
                            tempsPrecedent = tempsActuel;
                        }
                        //Left mouvement animation setup
                        if(tempsActuelAr - tempsPrecedentAr > 10){
                            p.lc++;
                            tempsPrecedentAr = tempsActuelAr;
                        }
                        if(p.frames < 5){
                            p.posJ.x -= 4;
                        }
                        else{
                            p.posJ.x -= 20;
                        }
                        if(p.jframes > 45)
                            SDL_BlitSurface(p.anim.imgSG[0],NULL,(*scr),&p.posJ);
                        else
                            if(p.jframes > 5)
                                SDL_BlitSurface(p.anim.imgSG[1],NULL,(*scr),&p.posJ);
                                else
                                    if(p.jframes)
                                        SDL_BlitSurface(p.anim.imgSG[2],NULL,(*scr),&p.posJ);
                                    else
                                        SDL_BlitSurface(p.anim.imgG[p.lc%2],NULL,(*scr),&p.posJ);
                    }
                    
                    //Jump initiation
                    if(event.key.keysym.sym == SDLK_UP){
                        p.jframes = 50;
                    }

                    if(event.key.keysym.sym == SDLK_RETURN)
                         enigme(scr,puz[0]);
                break;
                case SDL_KEYUP: //Frames and idle state reset
                    if(event.key.keysym.sym == SDLK_RIGHT){
                        p.frames = 0; p.rc = 0; p.Itest = 1;
                    }
                    if(event.key.keysym.sym == SDLK_LEFT){
                        p.frames = 0; p.lc = 0; p.Itest = 1;
                    }
                break;
            }
        }

        if(n){
            
                switch(event.type){
                    case SDL_QUIT:
                        return;
                    break;
                    case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_f){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            tempsActuelAr2 = SDL_GetTicks();
                            //Right mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.rc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.posJ.x+139 < 1280){
                                if(p2.frames < 5){
                                    p2.posJ.x += 4;
                                }
                                else{
                                    p2.posJ.x += 20;
                                }
                            }

                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSD[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSD[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSD[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgD[p2.rc%2],NULL,(*scr),&p2.posJ);
                        }

                        if(event.key.keysym.sym == SDLK_s){
                            p2.Itest = 0;
                            tempsActuel2 = SDL_GetTicks();
                            if ((tempsActuel2 - tempsPrecedent2 > 50)&&(p2.frames < 50)){
                                p2.lc++;
                                p2.frames ++;
                                tempsPrecedent2 = tempsActuel2;
                            }
                            //Left mouvement animation setup
                            if(tempsActuelAr2 - tempsPrecedentAr2 > 10){
                                p2.lc++;
                                tempsPrecedentAr2 = tempsActuelAr2;
                            }
                            if(p2.frames < 5){
                                p2.posJ.x -= 4;
                            }
                            else{
                                p2.posJ.x -= 20;
                            }
                            if(p2.jframes > 45)
                                SDL_BlitSurface(p2.anim.imgSG[0],NULL,(*scr),&p2.posJ);
                            else
                                if(p2.jframes > 5)
                                    SDL_BlitSurface(p2.anim.imgSG[1],NULL,(*scr),&p2.posJ);
                                    else
                                        if(p2.jframes)
                                            SDL_BlitSurface(p2.anim.imgSG[2],NULL,(*scr),&p2.posJ);
                                        else
                                            SDL_BlitSurface(p2.anim.imgG[p2.lc%2],NULL,(*scr),&p2.posJ);
                        }
                        
                        //Jump initiation
                        if(event.key.keysym.sym == SDLK_e){
                            p2.jframes = 50;
                        }

                        if(event.key.keysym.sym == SDLK_RETURN)
                            enigme(scr,puz[0]);
                    break;
                    case SDL_KEYUP: //Frames and idle state reset
                        if(event.key.keysym.sym == SDLK_f){
                            p2.frames = 0; p2.rc = 0; p2.Itest = 1;
                        }
                        if(event.key.keysym.sym == SDLK_s){
                            p2.frames = 0; p2.lc = 0; p2.Itest = 1;
                        }
                    break;
                }
            }
        
        //Jump code

        tempsActuel = SDL_GetTicks();
        if((p.jframes > 0) && (tempsActuel - tempsPrecedent > 20)){
            tempsPrecedent = tempsActuel;
            if(p.jframes > 27){
                p.posJ.y -= 10;
                p.jframes --;
            }
            else{
                p.posJ.y += 10;
                p.jframes --;
            }
        }
        if(n){
            tempsActuel2 = SDL_GetTicks();
            if((p2.jframes > 0) && (tempsActuel2 - tempsPrecedent2 > 20)){
                tempsPrecedent2 = tempsActuel2;
                if(p2.jframes > 27){
                    p2.posJ.y -= 10;
                    p2.jframes --;
                }
                else{
                    p2.posJ.y += 10;
                    p2.jframes --;
                }
            }
        }
        
        //collision check

        /*SDL_GetMouseState(&x,&y);
        cu = GetPixel(imglvlm,x+z,y);
        printf("%d %d %d\n",cu.r,cu.g,cu.b);*/

        switch(collisioncheck(imglvlm,p.posJ,z,0)){
            case 1:
                if(p.posJ.y + 228 > 300)
                    if(p.jframes < 28){
                        p.posJ.y += 10;
                        p.jframes = 0;
                    }
            break;
            case 2:
                if(p.score){
                    p.score --;
                }
            break;
        }

        if(n){
            switch(collisioncheck(imglvlm,p2.posJ,z,0)){
            case 1:
                if(p2.posJ.y + 228 > 300)
                    if(p2.jframes < 28){
                        p2.posJ.y += 10;
                        p2.jframes = 0;
                    }
            break;
            case 2:
                if(p2.score){
                    p2.score --;
                }
            break;
        }
        }

        //Time management
        tempsActuelT = SDL_GetTicks();
        if (tempsActuelT - tempsPrecedentT > 1000){
            time--;
            tempsPrecedentT = tempsActuelT;
        }
        SDL_BlitSurface(hourglass,NULL,(*scr),&posHG);
        BlitTime(time,T,scr);
        
        if(n)
            BlitScore(p.score + p2.score,T,scr);
        else
            BlitScore(p.score,T,scr);

        //End game conditions
        
        if(n){
            if(!p.score && !p2.score || !time){
                deathscreen(scr);
                return;
            }
        }
        else{
            if(!p.score || !time){
                deathscreen(scr);
                return;
        }
        }

        printf("%d %d %d\n",z,p.posJ.x,p.posJ.y);
        if(n){
            if(z == 3500 && p.posJ.y == p2.posJ.y > 140 && p.posJ.x == p2.posJ.x < 1200)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        else{
            if(z == 3500 && p.posJ.y > 140 && p.posJ.x < 1200)
            if(enigme(scr,puz[4])){
                victory(scr);
                return;
            }
            else{
                deathscreen(scr);
                return;
            }
        }
        
        SDL_Flip((*scr));
    }
}

