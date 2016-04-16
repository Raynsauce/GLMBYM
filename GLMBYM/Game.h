#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Mob.h"

class Game {
protected:
	typedef enum { INTRO,PLAYING } eState;
	typedef enum {INFO,WARN,ERROR} mType;
public:
	Game();
	~Game();

	inline void DrawObj(Entity * obj);
	void Girl(); //Run

	void LemmeBe(eState nState); //State set
	eState YourMan(void); //State get

	void LoseMyMind(mType boxtype,const char* message); //msg handling
protected:
	eState cState;
	
	SDL_Event* mEvent;
	SDL_Window*	mainwin = SDL_CreateWindow("GLMBYM",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_MOUSE_CAPTURE);
	SDL_Renderer* mainrndr = SDL_CreateRenderer(mainwin,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* mainTex = SDL_CreateTexture(mainrndr,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,WIDTH,HEIGHT);
public:
	Player P1 = Player(&mainrndr);
	Fire P1_fire = Fire(&mainrndr,&P1);
	Mob alien_ufo  = Mob(&mainrndr,{1u,"ufo"});
	Mob alien_sml0 = Mob(&mainrndr,{2u,"sml"});
	Mob alien_med0 = Mob(&mainrndr,{3u,"med"});
	Mob alien_lrg0 = Mob(&mainrndr,{4u,"lrg"});
	Mob alien_sml1 = Mob(&mainrndr,{2u,"sml"});
	Mob alien_med1 = Mob(&mainrndr,{3u,"med"});
	Mob alien_lrg1 = Mob(&mainrndr,{4u,"lrg"});
};