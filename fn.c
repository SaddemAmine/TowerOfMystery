#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fn.h"

    Menu M; Mix_Music *sfx; Mix_Music *mm; SDL_Surface* scr;

void init_res(){
    sfx = Mix_LoadMUS("menu_res/CSFX.mp3"); mm = Mix_LoadMUS("menu_res/music.mp3");
    M.MBG = IMG_Load("menu_res/menu2.png"); M.B1 = IMG_Load("menu_res/1H.png"); 
    M.B2 = IMG_Load("menu_res/2H.png"); M.B1C = IMG_Load("menu_res/1C.png");
    M.B3 = IMG_Load("menu_res/3H.png"); M.B2C = IMG_Load("menu_res/2C.png");
    M.B3C = IMG_Load("menu_res/3C.png"); M.SBG = IMG_Load("menu_res/settings/menu_s.png");
    M.S1H = IMG_Load("menu_res/settings/volume_h.png"); M.S2 = IMG_Load("menu_res/settings/S_2.png");
}

void free_res(){
    Mix_FreeMusic(sfx);
    SDL_FreeSurface(M.MBG);
    SDL_FreeSurface(M.B1);
    SDL_FreeSurface(M.B2);
    SDL_FreeSurface(M.B1C);
}

void settings(){

}

void menu(){
    int x = 0,y = 0; SDL_Event event; int test,test2=0; SDL_Rect pos,posb,posb2,posb3; int i = 0;
    pos.x = 0; pos.y = 0; pos.w = M.MBG->w; pos.h = M.MBG->h;
    posb.x = 911; posb.y = 188; posb.w = M.B1->w; posb.h = M.B1->h;
    posb2.x = 912; posb2.y = 302; posb2.w = M.B2->w; posb2.h = M.B2->h;
    posb3.x = 913; posb3.y = 415;
    scr = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    Mix_PlayMusic(mm,-1);
    SDL_BlitSurface(M.MBG,NULL,scr,&pos);
    SDL_Flip(scr);
     while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    free_res();
                    return;
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y); test2 = 0;
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>909&&x<1011)&&(y>179&&y<281)){
                        SDL_BlitSurface(M.B1,NULL,scr,&posb); printf("Yes//1\n"); test = 1;
                        //SDL_Flip(scr);
                    }
                    else{
                        if((x>909&&x<1011)&&(y>303&&y<400)){
                        SDL_BlitSurface(M.B2,NULL,scr,&posb2); printf("Yes//2\n"); test = 2;
                        //SDL_Flip(scr);
                    }
                    else{
                        if((x>909&&x<1011)&&(y>414&&y<514)){
                            SDL_BlitSurface(M.B3,NULL,scr,&posb3); printf("Yes//3\n"); test = 3;
                            //SDL_Flip(scr);
                        }
                        else{
                            SDL_BlitSurface(M.MBG,NULL,scr,&pos); printf("No\n");
                            //SDL_Flip(scr);
                        }
                    }
                    }
                    SDL_Flip(scr);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        SDL_BlitSurface(M.B1C,NULL,scr,&posb); Mix_PlayMusic(sfx,1);
                    }
                    else{
                        if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                            SDL_BlitSurface(M.B2C,NULL,scr,&posb2); Mix_PlayMusic(sfx,1);
                        }
                    else{
                        if(test == 3 && event.button.button == SDL_BUTTON_LEFT){
                            SDL_BlitSurface(M.B3C,NULL,scr,&posb3); Mix_PlayMusic(sfx,1);
                            Mix_FreeMusic(sfx);
                            SDL_FreeSurface(M.MBG);
                            SDL_FreeSurface(M.B1);
                            SDL_FreeSurface(M.B2);
                            SDL_FreeSurface(M.B1C);
                            return;    
                        }
                        else{
                            SDL_BlitSurface(M.MBG,NULL,scr,&pos);
                        }
                    }
                    }
                    SDL_Flip(scr);
                break;
                case SDL_KEYDOWN:
                    SDL_BlitSurface(M.MBG,NULL,scr,&pos); SDL_Flip(scr);
                    printf("---%d\n",test2);
                    if(event.key.keysym.sym == SDLK_DOWN){
                        if(test2<3)
                            test2++;
                        else
                            test2 = 1;
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B1,NULL,scr,&posb); printf("Yes//1 ::%d\n",test2); 
                            test = 1; SDL_Flip(scr); break;
                            case 2: SDL_BlitSurface(M.B2,NULL,scr,&posb2); printf("Yes//2 ::%d\n",test2); 
                            test = 2; SDL_Flip(scr); break;
                            case 3: SDL_BlitSurface(M.B3,NULL,scr,&posb3); printf("Yes//3 ::%d\n",test2); 
                            test = 3; SDL_Flip(scr); break;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_UP){
                        if(test2>1)
                            test2--;
                        else
                            test2 = 3;
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B1,NULL,scr,&posb); printf("Yes//1 ::%d\n",test2); 
                            test = 1; SDL_Flip(scr); break;
                            case 2: SDL_BlitSurface(M.B2,NULL,scr,&posb2); printf("Yes//2 ::%d\n",test2); 
                            test = 2; SDL_Flip(scr); break;
                            case 3: SDL_BlitSurface(M.B3,NULL,scr,&posb3); printf("Yes//3 ::%d\n",test2); 
                            test = 3; SDL_Flip(scr); break;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_SPACE){
                        switch(test2){
                            case 1: SDL_BlitSurface(M.B1C,NULL,scr,&posb); Mix_PlayMusic(sfx,1); break;
                            case 2: SDL_BlitSurface(M.B2C,NULL,scr,&posb2); Mix_PlayMusic(sfx,1); break;
                            case 3: 
                            SDL_BlitSurface(M.B3C,NULL,scr,&posb3); 
                            Mix_PlayMusic(sfx,1);
                            free_res();
                            return;
                            break;
                        }
                    }
                    SDL_Flip(scr);
                break;
            } 
        }
    }
}