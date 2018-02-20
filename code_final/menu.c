#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"

//                                                     MENU PRINCIPAL
int menu_principal(int *menu,int *sound,int *animation)
{
//Initialisation des images
SDL_Surface *ecran = NULL,*play=NULL,*settings=NULL,*quit=NULL;
//Initialisation des surfaces
SDL_Rect positionFond;
//Initialisation de l'event
SDL_Event event;
//Initialisation de l'ecran
SDL_Init(SDL_INIT_VIDEO | SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN | SDL_RESIZABLE);
ecran = SDL_SetVideoMode(1200, 750, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
// image de l'icone
SDL_WM_SetIcon(IMG_Load("images/icone.png"), NULL);
//Nom du fenetre
SDL_WM_SetCaption("CubeMe", NULL);
//VALEUR DE BOUCLE
int continuer=1;
//POSITION
int x;


//Musique
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("damso.mp3"); //Chargement de la musique
if (*sound==1)
{
 Mix_PlayMusic(musique, -1);
}

Mix_AllocateChannels(30);
Mix_Chunk *effet ;
effet = Mix_LoadWAV("effet1.wav");
if (effet == NULL) { fprintf(stderr, "Unable to load wav file: %s\n",Mix_GetError());}
Mix_VolumeChunk(effet, MIX_MAX_VOLUME );



//POSITION DES IMAGES

    positionFond.x = 0;

    positionFond.y = 0;

//ANIMATION
/*
char anime[30];
SDL_Surface *anim[400];
int i;
if (*animation==0){
for (i=1;i<400;i++){
sprintf(anime,"anim/%d.jpg",i);
anim[i] = IMG_Load(anime);
SDL_BlitSurface(anim[i], NULL, ecran, &positionFond);
SDL_Flip(ecran);
SDL_Delay(50);
*animation=1;}}*/

// FIN DE L'ANIMATION



//AFFICHER LES IMAGES
play = IMG_Load("images/principal_play.png");
settings = IMG_Load("images/principal_settings.png");
quit = IMG_Load("images/principal_quit.png");
SDL_BlitSurface(play, NULL, ecran, &positionFond);
x=1;



//EVENEMENT (OUVERTURE DE BOUCLE ) 

while (continuer)
{


   SDL_WaitEvent(&event);


    switch(event.type)
    {



// CROIX DE SORTIE
case SDL_QUIT:
      *menu=40;
      continuer = 0;
      break;



// CLAVIER
case SDL_KEYDOWN:

        switch(event.key.keysym.sym)
               {

        case SDLK_UP:
           if (x==2)
            x=1;
           else if ((x==3)||(x==-3))
            x=2;
           else
            x=-1;   
         break;

        case SDLK_DOWN:
           if ((x==1)||(x==-1))
            x=2;
           else if (x==2)
            x=3;
           else
            x=-3; 
         break;

        case SDLK_RETURN:
           if ((x==1)||(x==-1)){
            *menu=3;
            continuer=0;}
           if ((x==3)||(x==-3)){
            *menu=40;
            continuer=0;}
           if (x==2){
            *menu=2;
            continuer=0;}
         break;}
break;






//SOURIS MOUSETION 

case SDL_MOUSEMOTION:
//PLAY
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=245) &&(event.motion.y <= 310))
               {
                 
                // x=-1;
             	x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                         *menu=3;
                         continuer=0;
                      }
                  } 

               }
//SETTINGS
        if((event.motion.x >=470) &&(event.motion.x<=730) && (event.motion.y>=325) &&(event.motion.y <= 394))
               {
                
                //  x=-2;
			x=0;
                 
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          *menu=2;
                          continuer=0;
                      }
                  } 

               }
//QUIT
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=410) &&(event.motion.y <= 475))
               {
           
             //    x=-3;
		x=0;
                
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          *menu=40;
                          continuer=0;
                      }
                  } 

               }
break; 
   }

if (x==1){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(play, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==2){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(settings, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==3){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(quit, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==-1){
SDL_BlitSurface(play, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==-2){
SDL_BlitSurface(settings, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==-3){
SDL_BlitSurface(quit, NULL, ecran, &positionFond);
SDL_Flip(ecran);}


}//FERMETURE DE BOUCLE

                                  

//LIBERATION
SDL_Flip(ecran);
//SDL_FreeSurface(*anim);
SDL_FreeSurface(play);
SDL_FreeSurface(settings);
SDL_FreeSurface(quit);


    Mix_FreeMusic(musique); //Libération de la musique
    Mix_FreeChunk(effet);
    Mix_CloseAudio(); //Fermeture de l'API

    SDL_Quit();
    return EXIT_SUCCESS;
}





//                                             MENU SETTINGS
int menu_settings(int *menu,int *sound){
//Initialisation des images
SDL_Surface *ecran=NULL,*sounds=NULL,*credits=NULL,*back=NULL;
//Initialisation des surfaces
SDL_Rect positionFond;
//Initialisation de l'event
SDL_Event event;
//Initialisation de l'ecran
SDL_Init(SDL_INIT_VIDEO | SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN | SDL_RESIZABLE);
ecran = SDL_SetVideoMode(1200, 750, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
// image de l'icone
SDL_WM_SetIcon(IMG_Load("images/icone.png"), NULL);
//Nom du fenetre
SDL_WM_SetCaption("CubeMe : Settings", NULL);
//VALEUR DE BOUCLE
int continuer=1;
//POSITION
int x;


//Musique
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("damso.mp3"); //Chargement de la musique
if (*sound==1)
{
 Mix_PlayMusic(musique, -1);
}
Mix_AllocateChannels(30);
Mix_Chunk *effet ;
effet = Mix_LoadWAV("effet1.wav");
if (effet == NULL) { fprintf(stderr, "Unable to load wav file: %s\n",Mix_GetError());}
Mix_VolumeChunk(effet, MIX_MAX_VOLUME );




//POSITION DES IMAGES

    positionFond.x = 0;

    positionFond.y = 0;



//AFFICHER LES IMAGES
sounds = IMG_Load("images/settings_sounds.png");
credits = IMG_Load("images/settings_credits.png");
back = IMG_Load("images/settings_back.png");
SDL_BlitSurface(sounds, NULL, ecran, &positionFond);
x=1;



//EVENEMENT (OUVERTURE DE BOUCLE ) 

while (continuer)
{


   SDL_WaitEvent(&event);


    switch(event.type)
    {



// CROIX DE SORTIE
case SDL_QUIT:
      *menu=40;
      continuer = 0;
      break;



// CLAVIER
case SDL_KEYDOWN:

        switch(event.key.keysym.sym)
               {

        case SDLK_UP:
           if (x==2)
            x=1;
           else if ((x==3)||(x==-3))
            x=2;
           else
            x=-1;   
         break;

        case SDLK_DOWN:
           if ((x==1)||(x==-1))
            x=2;
           else if (x==2)
            x=3;
           else
            x=-3; 
         break;

        case SDLK_RETURN:
           if ((x==1)||(x==-1)){
            if(Mix_PausedMusic() == 1)//Si la musique est en pause
                    {
                        Mix_PlayMusic(musique, -1); //Reprendre la musique
                        *sound=1;
                    }
                    else
                    {
                        Mix_PauseMusic(); //Mettre en pause la musique
                        *sound=0;
                    }          }
           if ((x==3)||(x==-3)){
            *menu=1;
            continuer=0;}
           if (x==2){
            *menu=4;
            continuer=0;}
         break;}
break;






//SOURIS MOUSETION 
case SDL_MOUSEMOTION:
//SOUND
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=245) &&(event.motion.y <= 310))
               {
                 
              //    x=1;
			x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                         if (*sound==0)
                         *sound=1;
                        else
                         *sound=0;
                      }
                  } 

               }
//CREDITS
        if((event.motion.x >=470) &&(event.motion.x<=730) && (event.motion.y>=325) &&(event.motion.y <= 394))
               {
                
                 // x=2;
		x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          *menu=4;
                          continuer=0;
                      }
                  } 

               }
//BACK
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=410) &&(event.motion.y <= 475))
               {
              
                  //x=3;
			x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          *menu=1;
                          continuer=0;
                      }
                  } 

               }
break;
   }

if (x==1){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(sounds, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==2){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(credits, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==3){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(back, NULL, ecran, &positionFond);
SDL_Flip(ecran);}


}//FERMETURE DE BOUCLE

                                  

//LIBERATION
 SDL_Flip(ecran);
//SDL_FreeSurface(*anim);
 SDL_FreeSurface(sounds);
 SDL_FreeSurface(credits);
 SDL_FreeSurface(back);


    Mix_FreeMusic(musique); //Libération de la musique
Mix_FreeChunk(effet);
    Mix_CloseAudio(); //Fermeture de l'API

    SDL_Quit();
    return EXIT_SUCCESS;
}

                                                            //MENU PLAY 
int menu_play(int *menu,int *sound){
//Initialisation des images
SDL_Surface *ecran=NULL,*single=NULL,*multi=NULL,*back=NULL;
//Initialisation des surfaces
SDL_Rect positionFond;
//Initialisation de l'event
SDL_Event event;
//Initialisation de l'ecran
SDL_Init(SDL_INIT_VIDEO | SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN | SDL_RESIZABLE);
ecran = SDL_SetVideoMode(1200, 750, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
// image de l'icone
SDL_WM_SetIcon(IMG_Load("images/icone.png"), NULL);
//Nom du fenetre
SDL_WM_SetCaption("CubeMe : Play", NULL);
//VALEUR DE BOUCLE
int continuer=1;
//POSITION
int x;


//Musique
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("damso.mp3"); //Chargement de la musique
if (*sound==1)
{
 Mix_PlayMusic(musique, -1);
}
Mix_AllocateChannels(30);
Mix_Chunk *effet ;
effet = Mix_LoadWAV("effet1.wav");
if (effet == NULL) { fprintf(stderr, "Unable to load wav file: %s\n",Mix_GetError());}
Mix_VolumeChunk(effet, MIX_MAX_VOLUME );




//POSITION DES IMAGES

    positionFond.x = 0;

    positionFond.y = 0;



//AFFICHER LES IMAGES
single = IMG_Load("images/play_singleplayer.png");
multi = IMG_Load("images/play_multiplayer.png");
back = IMG_Load("images/play_back.png");
SDL_BlitSurface(single, NULL, ecran, &positionFond);
x=1;



//EVENEMENT (OUVERTURE DE BOUCLE ) 

while (continuer)
{


   SDL_WaitEvent(&event);


    switch(event.type)
    {



// CROIX DE SORTIE
case SDL_QUIT:
      *menu=40;
      continuer = 0;
      break;



// CLAVIER
case SDL_KEYDOWN:

        switch(event.key.keysym.sym)
               {

        case SDLK_UP:
           if (x==2)
            x=1;
           else if ((x==3)||(x==-3))
            x=2;
           else
            x=-1;   
         break;

        case SDLK_DOWN:
           if ((x==1)||(x==-1))
            x=2;
           else if (x==2)
            x=3;
           else
            x=-3; 
         break;

        case SDLK_RETURN:
           if ((x==1)||(x==-1)){
            *menu=5;
            continuer=0;}
           if ((x==3)||(x==-3)){
            *menu=1;
            continuer=0;}
           if (x==2)
            continuer=0;
         break;}
break;






//SOURIS MOUSETION 
case SDL_MOUSEMOTION:
//SOUND
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=245) &&(event.motion.y <= 310))
               {
                 
                 // x=1;	
			x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                         *menu=5;
                         continuer=0;
                      }
                  } 

               }
//CREDITS
        if((event.motion.x >=470) &&(event.motion.x<=730) && (event.motion.y>=325) &&(event.motion.y <= 394))
               {
                
                 // x=2;
		x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          
                          continuer=0;
                      }
                  } 

               }
//BACK
        if((event.motion.x >=520) &&(event.motion.x<=670) && (event.motion.y>=410) &&(event.motion.y <= 475))
               {
              	
                //  x=3;
		x=0;
                  if (SDL_MOUSEBUTTONUP)
                  {
                  if (event.button.button== SDL_BUTTON_LEFT)
                      {
                          *menu=1;
                          continuer=0;
                      }
                  } 

               }
break;
   }

if (x==1){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(single, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==2){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(multi, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==3){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(back, NULL, ecran, &positionFond);
SDL_Flip(ecran);}


}//FERMETURE DE BOUCLE

                                  

//LIBERATION
 SDL_Flip(ecran);
//SDL_FreeSurface(*anim);
 SDL_FreeSurface(single);
 SDL_FreeSurface(multi);
 SDL_FreeSurface(back);


    Mix_FreeMusic(musique); //Libération de la musique
Mix_FreeChunk(effet);
    Mix_CloseAudio(); //Fermeture de l'API

    SDL_Quit();
    return EXIT_SUCCESS;
}



                                                    //MENU SINGLEPLAYER
int menu_singleplayer(int *menu,int *sound)
{
//Initialisation des images
SDL_Surface *ecran = NULL,*back=NULL,*perso1=NULL,*perso2=NULL,*perso3=NULL,*perso4=NULL;
//Initialisation des surfaces
SDL_Rect positionFond;
//Initialisation de l'event
SDL_Event event;
//Initialisation de l'ecran
SDL_Init(SDL_INIT_VIDEO | SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN | SDL_RESIZABLE);
ecran = SDL_SetVideoMode(1200, 750, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
// image de l'icone
SDL_WM_SetIcon(IMG_Load("images/icone.png"), NULL);
//Nom du fenetre
SDL_WM_SetCaption("CubeMe : SinglePlayer", NULL);
//VALEUR DE BOUCLE
int continuer=1;
//POSITION
int x;


//Musique
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("damso.mp3"); //Chargement de la musique
if (*sound==1)
{
 Mix_PlayMusic(musique, -1);
}

Mix_AllocateChannels(30);
Mix_Chunk *effet ;
effet = Mix_LoadWAV("effet1.wav");
if (effet == NULL) { fprintf(stderr, "Unable to load wav file: %s\n",Mix_GetError());}
Mix_VolumeChunk(effet, MIX_MAX_VOLUME );



//POSITION DES IMAGES

    positionFond.x = 0;
    positionFond.y = 0;

//ANIMATION
/*
char anime[30];
SDL_Surface *anim[400];
int i;
if (*animation==0){
for (i=1;i<21;i++){
sprintf(anime,"anim/%d.jpg",i);
anim[i] = IMG_Load(anime);
SDL_BlitSurface(anim[i], NULL, ecran, &positionFond);
SDL_Flip(ecran);
SDL_Delay(50);
*animation=1;}}*/

// FIN DE L'ANIMATION



//AFFICHER LES IMAGES
back = IMG_Load("images/single_back.png");
perso1 = IMG_Load("images/single_1.png");
perso2 = IMG_Load("images/single_2.png");
perso3 = IMG_Load("images/single_3.png");
perso4 = IMG_Load("images/single_4.png");
SDL_BlitSurface(perso1, NULL, ecran, &positionFond);
x=1;



//EVENEMENT (OUVERTURE DE BOUCLE ) 

while (continuer)
{


   SDL_WaitEvent(&event);


    switch(event.type)
    {



// CROIX DE SORTIE
case SDL_QUIT:
      *menu=40;
      continuer = 0;
      break;



// CLAVIER
case SDL_KEYDOWN:

        switch(event.key.keysym.sym)
               {
        case SDLK_RIGHT:
            if (x==1)
            x=2;
            else if (x==2)
            x=3;
            else if (x==3)
            x=4;
            else if (x==4)
            x=1;
          break;

        case SDLK_LEFT:
            if (x==1)
            x=4;
            else if (x==2)
            x=1;
            else if (x==3)
            x=2;
            else if (x==4)
            x=3;
          break;

        case SDLK_UP:
          if (x==0)
            x=1;
         break;

        case SDLK_DOWN:
          if (x!=0)
           x=0;
         break;

        case SDLK_RETURN:
          if (x==0){
          *menu=3;
          continuer=0;}          
         
         break;}
break;
	case SDL_MOUSEMOTION:
		x=0;	
		break;
   }
if (x==0){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(back, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==1){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(perso1, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==2){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(perso2, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==3){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(perso3, NULL, ecran, &positionFond);
SDL_Flip(ecran);}
if (x==4){
Mix_PlayChannel(1, effet,0);
SDL_BlitSurface(perso4, NULL, ecran, &positionFond);
SDL_Flip(ecran);}


}//FERMETURE DE BOUCLE

                                  

//LIBERATION
SDL_Flip(ecran);
SDL_FreeSurface(back);
SDL_FreeSurface(perso1);
SDL_FreeSurface(perso2);
SDL_FreeSurface(perso3);
SDL_FreeSurface(perso4);


    Mix_FreeMusic(musique); //Libération de la musique
    Mix_FreeChunk(effet);
    Mix_CloseAudio(); //Fermeture de l'API

    SDL_Quit();
    return EXIT_SUCCESS;
}




                                                 // CREDITS

int menu_credits(int *menu,int *sound)

{
    //INITIALISATION
    SDL_Surface *ecran = NULL,*imageDeFond = NULL;
    SDL_Rect positionFond;
    SDL_Event event;
    SDL_WM_SetCaption("SDL_Mixer", NULL);
    int continuer =1;
    SDL_Init(SDL_INIT_VIDEO | SDL_HWSURFACE | SDL_DOUBLEBUF);
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("CubeMe : Menu Principal", NULL);
    //POSITION
    positionFond.x = 0;

    positionFond.y = 0;

    //MUSIQUE

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   {
      printf("%s", Mix_GetError());

   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
if (*sound==1)
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

 
    //IMAGE
    imageDeFond = IMG_Load("images/credits.png");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

 
   //EVENEMENTS
while (continuer)

{
   SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
      *menu=30;
      continuer = 0;
      break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
           case SDLK_RETURN:
            *menu=2;
            continuer=0;
            break;
        }
       break;
    }
}
    SDL_Flip(ecran);
    SDL_FreeSurface(imageDeFond);
    Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio(); //Fermeture de l'API
    SDL_Quit();

    return EXIT_SUCCESS;

}





    
