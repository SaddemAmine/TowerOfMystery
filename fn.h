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
	SDL_Surface* imgI[2];
	SDL_Surface* imgD[2];
	SDL_Surface* imgG[2];
	SDL_Surface* imgSD[3];
    SDL_Surface* imgSG[3];
}animation;

typedef struct{
	animation anim;
    int score;
    int frames;
    int jframes;
    int Itest;
    int rc,ic,jc,lc; //counters used for animation
    SDL_Rect posJ;

}Player;

typedef struct{
	SDL_Surface* img;
	int rep;
}puzzle;

typedef struct{
SDL_Rect  position_bat;
SDL_Surface* image_bat[2];
int ac; //animation counter
} bat;

typedef struct{
    SDL_Surface* cimg[6];
    int value,ac,r;
    SDL_Rect pos;
}coin;

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
    SDL_Surface* highlight;
}Menu;

void init_res(Menu* M,Music* m,CC* x); //Resources initialization
void free_res(Menu M,Music m); 
void free_res_cc(CC x); //Character creation
void menu(Menu M,Music m,SDL_Surface** scr,int T[],CC cc);
int settings(Menu M,Music m,SDL_Surface** scr,int T[]);
void vl_blit(Menu M,SDL_Surface** scr,int x); //Volume level bar blit
void savefile_to_array(int T[]);
void array_to_savefile(int T[]);
int cc_menu(CC cc,Music m,SDL_Surface** scr,int T[]);
void savecc(int x,int y,int z);
void init_anim_p1(Player* p);
void init_anim_p2(Player* p);
void intro(SDL_Surface** scr);
void gamelvl1(SDL_Surface** scr,int n,int s);
void credits(SDL_Surface** scr);
int collisioncheck(SDL_Surface* img,SDL_Rect pos,int z,int type);
void BlitTime(int x,SDL_Surface* T[],SDL_Surface** scr);
void init_puzzle(puzzle p[]);
void BlitScore(int x,SDL_Surface* T[],SDL_Surface** scr);
void parallax_scrolling(SDL_Surface** scr,int x,SDL_Surface* b1,SDL_Surface* b2,SDL_Surface* b3,SDL_Rect* p1,SDL_Rect* p2,SDL_Rect* p3);
void gamelvl2(SDL_Surface** scr,int n,int s);
void player_setup(Player* p,int n);
void init_numbers(SDL_Surface* T[]);
void initialiser_bat(bat* B);
int SOSO();
void deplacement_aleatoire(bat* B,SDL_Surface** scr,int x);
void displaycoins(coin C,SDL_Surface** scr);
void init_coins(coin* C);
int PEcollision(SDL_Rect pp,SDL_Rect ep);
int collisiontrigo(coin P1,coin P2);
void deathscreen(SDL_Surface** scr);
void gamelvl3(SDL_Surface** scr,int n,int s);


#endif
