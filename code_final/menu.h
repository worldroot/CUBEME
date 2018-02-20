#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 



int menu_principal(int *menu,int *sound,int *animation);

int menu_play(int *menu,int *sound);

int menu_settings(int *menu,int *sound);

int menu_singleplayer(int *menu,int *sound);

int menu_credits(int *menu,int *sound);

//int menu_credits(int *menu,int *sound);

#endif
