#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void main(){

    SDL_Surface* scr = NULL; SDL_Rect pos; pos.x = 0; pos.y = 1440;
    SDL_Surface* bl = IMG_Load("media/levels/black.png");
    SDL_Surface* wt = IMG_Load("media/levels/white.png");
    SDL_Surface* lvls = NULL;

    SDL_InitSubSystem(SDL_INIT_VIDEO);

    scr = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    FILE* f = NULL; char ch[66];
    f = fopen("lvl.txt","r");
    char lvl[72][65];
    
    for(int i=0;i<72;i++){
        for(int j=0;j<64;j++){
            lvl[i][j] = '@';
        }
    }
    
    for(int i=0;i<72;i++){
        fgets(ch,66,f);
        printf("%s%d %d\n",ch,strlen(ch),i);
        for(int j=0;j<64;j++){
            lvl[i][j] = ch[j];
        }
    }

    for(int i=0;i<72;i++){
        for(int j=0;j<64;j++){
            if(lvl[i][j] == '1'){
                SDL_BlitSurface(bl,NULL,lvls,&pos);
                pos.x += 20;
            }  
            else{
                SDL_BlitSurface(wt,NULL,lvls,&pos);
                pos.x += 20;
            }
        }
        pos.x = 0;
        pos.y -= 20;
    }
    SDL_Flip(scr);
    while(pos.y > 0){
        pos.y--;
        if(pos.y == 1)
            pos.y = 1440;
    
        SDL_BlitSurface(lvls,NULL,scr,&pos);
        SDL_Flip(scr);
    }   
    getchar();
}
