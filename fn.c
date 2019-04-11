#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fn.h"

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

void vl_blit(Menu M,SDL_Surface** scr,int x){
    SDL_Rect pos; pos.x = 153; pos.y = 151; pos.w = M.S1H->w; pos.h = M.S1H->h;
    for(int i=0;i<x;i++){
        SDL_BlitSurface(M.S1H,NULL,(*scr),&pos);
        pos.x += pos.w;
    }
}

void savefile_to_array(int T[]){
    FILE* f = NULL;
    f = fopen("save.txt","r");
    for(int i=0;i<6;fscanf(f,"%d",&T[i]),i++);
    fclose(f);
}

void array_to_savefile(int T[]){
    FILE* f = NULL;
    f = fopen("save.txt","w");
    for(int i=0;i<6;fprintf(f,"%d\n",T[i]),i++);
    fclose(f);
}

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

void savecc(int x,int y,int z){
    FILE* f = NULL;
    f = fopen("savecc.txt","w");
    fprintf(f,"%d %d %d",x,y,z);
    fclose(f);
}

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
                        game(scr);
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
                                    game(scr);
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


void init_anim(personnage* p){
    p->anim.imgI[0] = IMG_Load("media/player/p1.png");
    p->anim.imgI[1] = IMG_Load("media/player/p2.png");
    p->anim.imgD[0] = IMG_Load("media/player/p3_D.png");
    p->anim.imgD[1] = IMG_Load("media/player/p4_D.png");
    p->anim.imgG[0] = IMG_Load("media/player/p3_G.png");
    p->anim.imgG[1] = IMG_Load("media/player/p4_G.png");
    p->anim.imgS[0] = IMG_Load("media/player/p5.png");
    p->anim.imgS[1] = IMG_Load("media/player/p6.png");
    p->anim.imgS[2] = IMG_Load("media/player/p7.png");
}


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


void game(SDL_Surface** scr){
    SDL_Rect posCam,pos,posJ; int i=0; Uint32 tempsPrecedent = 0, tempsActuel = 0; 
    int z = 3725; int x = 0,y = 0,test = -1;
    SDL_Event event; personnage p;
    SDL_Surface* imglvl = IMG_Load("media/levels/level1.png");
    posCam.x = 0; posCam.y = 0; pos.x = 0; pos.y = 3725; pos.h = 720; pos.w = 1280;
    posJ.x = 640; posJ.y = 400; 
    

    
    SDL_EnableKeyRepeat(10,10);
    init_anim(&p);
    (*scr) = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    
    
    while(1){
        SDL_GetMouseState(&x,&y);
        printf("%d,%d ::%d\n",x,y,i); i++;
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 2){
            printf("%d  %d---------------\n",z,posCam.y);
            if(z>1800)
                z-=2;
            else{
                z = 3725; 
            }
            pos.y = z;
            tempsPrecedent = tempsActuel;
        }

        SDL_BlitSurface(imglvl,&pos,(*scr),NULL); 
        SDL_BlitSurface(p.anim.imgI[0],NULL,(*scr),&posJ);
        SDL_Flip((*scr));
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    return;
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_RIGHT)
                        posJ.x += 5;
                    if(event.key.keysym.sym == SDLK_LEFT)
                        posJ.x -= 5;
                    if(event.key.keysym.sym == SDLK_SPACE)
                        posJ.y -= 30;
                    if(event.key.keysym.sym == SDLK_DOWN)
                        posJ.y += 30;
                break;
            }
        }
    }
}