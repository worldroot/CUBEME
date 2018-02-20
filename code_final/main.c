#include <stdlib.h>

#include <stdio.h>

#include <SDL/SDL.h>

#include <SDL/SDL_image.h> /* Inclusion du header de SDL_image (adapter le dossier au besoin) */
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include"menu.h"


 

int main()

{
    int menu,animation=0;
   int x,y;
   int sound=1;
   menu=1;
while (menu<20) {
if (menu==1){
        x=menu_principal(&menu,&sound,&animation);}
if(menu==2){
  	x=menu_settings(&menu,&sound);}
if (menu==3){
        x=menu_play(&menu,&sound);}
if(menu==4){
  	x=menu_credits(&menu,&sound);}
if(menu==5){
  	x=menu_singleplayer(&menu,&sound);}

   
    
  }
       
    
    
 return 0;
}
