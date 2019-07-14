/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Include SDL functions and datatypes
#include "SDL2/SDL.h"

int main( int argc, char* args[] )
{
    //The images
    SDL_Surface  *hello = NULL;
    SDL_Window   *window = NULL;
    SDL_Texture  *texture =NULL;
    SDL_Renderer * renderer = NULL;

    // Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    // Set up screen
    // window = SDL_CreateWindow("这是我的第一个SDL程序",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,0,0,SDL_WINDOW_FULLSCREEN_DESKTOP); // 全屏显示
    window = SDL_CreateWindow("这是我的第一个SDL程序",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,0);

    // Load image
    hello = SDL_LoadBMP( "hello.bmp" );

    // 渲染层
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    // 载入的图片生成SDL贴图材质
    texture  = SDL_CreateTextureFromSurface(renderer, hello);
    
    //如果指定显示位置使用下面注释起来的两句
    SDL_Rect dstrect = { 5, 5, 320, 240 };
 
    // 把贴图材质复制到渲染器
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    
    // 显示出来  
    SDL_RenderPresent(renderer);
    
    // update Screen
    // SDL_Flip( screen );

    // Pause
    SDL_Delay( 2000 );

    // Free the loaded image
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface( hello );
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}
