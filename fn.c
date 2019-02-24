#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

    SDL_Surface *scr = NULL; 
    SDL_Surface *bg = NULL; SDL_Surface *bg1 = NULL; SDL_Surface *bg2 = NULL;
    SDL_Surface *bgH = NULL; Mix_Music *sfx;

void init_res(){
    sfx = Mix_LoadMUS("Menu_Res/CSFX.wav");
    bg = IMG_Load("Menu_Res/menu.png"); bg1 = IMG_Load("Menu_Res/1.png"); 
    bg2 = IMG_Load("Menu_Res/2.png"); bgH = IMG_Load("Menu_Res/c.png");
}

void menu(){
    int x = 0,y = 0; SDL_Event event; int test; SDL_Rect pos,posb,posb2; int i = 0;
    pos.x = 0; pos.y = 0; pos.w = bg->w; pos.h = bg->h;
    posb.x = 240; posb.y = 125; posb.w = bg1->w; posb.h = bg1->h;
    posb2.x = 240; posb2.y = 250; posb2.w = bg1->w; posb2.h = bg1->h;
    scr = SDL_SetVideoMode(500,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_BlitSurface(bg,NULL,scr,&pos);
    SDL_Flip(scr);
     while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    Mix_FreeMusic(sfx);
                    SDL_FreeSurface(bg);
                    SDL_FreeSurface(bg1);
                    SDL_FreeSurface(bg2);
                    SDL_FreeSurface(bgH);
                    return;
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>240&&x<395)&&(y>125&&y<190)){
                        SDL_BlitSurface(bg1,NULL,scr,&posb); printf("Yes//1\n"); test = 1;
                        //SDL_Flip(scr);
                    }
                    else{
                         if((x>240&&x<395)&&(y>250&&y<350)){
                        SDL_BlitSurface(bg2,NULL,scr,&posb2); printf("Yes//2\n"); test = 2;
                        //SDL_Flip(scr);
                    }
                    else{
                        SDL_BlitSurface(bg,NULL,scr,&pos); printf("No\n");
                        //SDL_Flip(scr);
                    }
                    }
                    SDL_Flip(scr);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        SDL_BlitSurface(bgH,NULL,scr,&posb); Mix_PlayMusic(sfx,1);
                    }
                    else{
                        if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                        SDL_BlitSurface(bgH,NULL,scr,&posb2); Mix_PlayMusic(sfx,1);
                    }
                    else{
                        SDL_BlitSurface(bg,NULL,scr,&pos);
                    }
                    }
                    SDL_Flip(scr);
                break;
            } 
        }
    }
}