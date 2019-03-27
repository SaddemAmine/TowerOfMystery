#ifndef FN_H_INCLUDED
#define FN_H_INCLUDED 

typedef struct{
    SDL_Surface* h1;
    SDL_Surface* h2;
    SDL_Surface* h3;
}struct_head;

typedef struct{
    SDL_Surface* b1;
    SDL_Surface* b2;
    SDL_Surface* b3;
}struct_body;

typedef struct{
    SDL_Surface* f1;
    SDL_Surface* f2;
    SDL_Surface* f3;
}struct_feet;

typedef struct{
    SDL_Surface* ccbg;
    SDL_Surface* hl;
    SDL_Surface* buffer;
    struct_head head;
    struct_body body;
    struct_feet feet;
}CC;

typedef struct{
    Mix_Music* sfx;
    Mix_Music* mm;
}Music;

typedef struct{
    SDL_Surface* MBG; //menu background
    SDL_Surface* B1; //button 1
    SDL_Surface* B2; //button 2
    SDL_Surface* B3; //button 3
    SDL_Surface* B1C; //b1 when clicked on
    SDL_Surface* B2C; //b2 when clicked on
    SDL_Surface* B3C; //b3 when clicked on
    SDL_Surface* SBG; //settings menu background
    SDL_Surface* S1H;
    SDL_Surface* S2;
    SDL_Surface* S3;
    SDL_Surface* S4;
}Menu;

void init_res(Menu* M,Music* m,CC* x);
void free_res(Menu M,Music m);
void free_res_cc(CC x);
void menu(Menu M,Music m,SDL_Surface** scr,int T[],CC cc);
int settings(Menu M,Music m,SDL_Surface** scr,int T[]);
void vl_blit(Menu M,SDL_Surface** scr,int x);
void savefile_to_array(int T[]);
void array_to_savefile(int T[]);
int cc_menu(CC cc,Music m,SDL_Surface** scr,int T[]);
void savecc(int x,int y,int z);

#endif