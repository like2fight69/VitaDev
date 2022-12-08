#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};

#define TN_FLAG_IMAGE_PATH "assets/bg.png"

SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;

SDL_Rect fillRect = { SCREEN_WIDTH  / 4, 
		      SCREEN_HEIGHT / 4, 
		      SCREEN_WIDTH  / 2, 
		      SCREEN_HEIGHT / 2 
};

SceCtrlData ctrl;
int speed = 300;

int main(int argc, char *argv[]) 
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
      return -1;
  //test
  int flags = IMG_INIT_PNG; // Can be: IMG_INIT_JPG | IMG_INIT_PNG
    if((IMG_Init(flags) & flags) != flags) {
        printf("SDL2_image could not be initialized with PNG support!\n"
               "SDL2_image Error: %s\n", IMG_GetError());
        return 0;
    }



  //test
  if ((gWindow = SDL_CreateWindow( "RedRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    return -1;

  if ((gRenderer = SDL_CreateRenderer( gWindow, -1, 0)) == NULL)
      return -1;

  SDL_Texture *flag = IMG_LoadTexture(gRenderer, TN_FLAG_IMAGE_PATH);
  //test
  int w, h;
            SDL_QueryTexture(flag, NULL, NULL, &w, &h);

            // Flag dimensions/position
            SDL_Rect flagRect;

            // Scale the flag dimensions to fit the screen
            if(w > h) {
                flagRect.w = SCREEN_WIDTH * 0.6;
                flagRect.h = h * flagRect.w / w;
            } else {
                flagRect.h = SCREEN_HEIGHT * 0.6;
                flagRect.w = w * flagRect.h / h;
            }

            // Flag position: In the middle of the screen
            flagRect.x = SCREEN_WIDTH / 2 - flagRect.w / 2;
            flagRect.y = SCREEN_HEIGHT / 2 - flagRect.h / 2;

            // Set the border size
            const int flagBorderSize = 5;

            // Declare rect of square
            SDL_Rect squareRect;

            // Square dimensions
            squareRect.w = flagRect.w + flagBorderSize * 2;
            squareRect.h = flagRect.h + flagBorderSize * 2;

            // Square position:
            squareRect.x = flagRect.x - flagBorderSize;
            squareRect.y = flagRect.y - flagBorderSize;


            // Event loop exit flag
//            bool quit = false;
   int a = 1;
   

  //test
  if(ctrl.up){
     printf("you pressed right");
     squareRect.y -= speed / 30;
  }
  //test
  while(a)
   { 

  SDL_SetRenderDrawColor( gRenderer, 255,0,0,255);
  SDL_RenderFillRect( gRenderer, &squareRect );
  SDL_RenderCopy(gRenderer, flag, NULL, &flagRect);
  SDL_RenderPresent( gRenderer );
  SDL_Delay(4000);
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
}
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
  sceKernelExitProcess(0);
  return 0;
}
