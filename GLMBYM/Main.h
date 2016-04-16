#pragma once
#include "stdafx.h"


#ifndef MAIN_H
#define MAIN_H
auto InitSDL = []{	//Automatically embedded, wont need to be called, obfuscation yay!
	std::ios::sync_with_stdio( false );
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0){ std::cerr << "SDL_Init failure! Error: " << SDL_GetError() << std::endl; }
	if(IMG_Init(IMG_InitFlags::IMG_INIT_PNG)?0:1){ std::cerr << "IMG_Init failure! Error: " << IMG_GetError() << std::endl; } //IMG_Init returns 0 on failure..
	atexit(SDL_Quit);
	atexit(IMG_Quit);	//Last func specified with atexit is the first to be executed upon exit
};
#endif	//MAIN_H