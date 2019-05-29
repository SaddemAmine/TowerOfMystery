
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<SDL/SDL_audio.h>


void player_setup(Player* p,int n)
{
    
    if(n == 1)
        init_anim_p1(p);
    else
        init_anim_p2(p);

    p->frames = 0;
    p->jframes = 0;
    p->ic = 0;
    p->jc = 0;
    p->rc = 0;
    p->score = 100;
    p->posJ.x = 640;
    p->posJ.y = 400;
    p->posJ.h = 228;
    p->posJ.w = 139;
}
