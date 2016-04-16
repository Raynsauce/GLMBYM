#include "stdafx.h"
#include "Game.h"

Game::Game() : mEvent(new SDL_Event)
{
	SDL_PollEvent(mEvent);
	LemmeBe(eState::INTRO);
}
Game::~Game()
{
	SDL_DestroyTexture(mainTex);
	SDL_DestroyRenderer(mainrndr);
	SDL_DestroyWindow(mainwin);
	
	delete mEvent;
}

#define OBJCOL(X) obj->color.X
inline void Game::DrawObj(Entity* obj)
{
	if(obj != nullptr){
		if(obj->cState == 0){
			obj->Update();
			SDL_SetRenderTarget(mainrndr,mainTex);
			SDL_SetTextureColorMod(*(obj->curtex),OBJCOL(r),OBJCOL(g),OBJCOL(b));

			SDL_RenderCopy(mainrndr,*(obj->curtex),nullptr,obj->props);
		}
	}
}

void Game::Girl() /* Running */
{
	for(; mEvent->quit.type != SDL_QUIT; SDL_PollEvent(mEvent))
	{
		switch(cState){
		case eState::INTRO:
			std::cout << "Welcome to Space!" << std::endl;
			LemmeBe(PLAYING);
			break;
		case eState::PLAYING:
			P1.Update(mEvent->key);
			//P1_fire.Update();
			DrawObj(&P1);
			DrawObj(&P1_fire);

			DrawObj(&alien_sml0);
			DrawObj(&alien_med0);
			DrawObj(&alien_lrg0);
			DrawObj(&alien_sml1);
			DrawObj(&alien_med1);
			DrawObj(&alien_lrg1);
			break;
		}

		SDL_SetRenderTarget(mainrndr,nullptr); /* present frame */
		SDL_RenderCopy(mainrndr,mainTex,nullptr,nullptr);
		SDL_RenderPresent(mainrndr);

		SDL_SetRenderTarget(mainrndr,mainTex);
		SDL_SetRenderDrawColor(mainrndr,0,0,0,255);
		SDL_RenderClear(mainrndr);
	}
}

void Game::LemmeBe(eState nState){ cState = nState; };
Game::eState Game::YourMan(void) {  return cState;  };

//void Game::TakeMyHand(){};
//void Game::Babe(){};

void Game::LoseMyMind(mType msgtype,const char* message)
{
	switch(msgtype){
	case mType::ERROR:SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,		"Engine: ERROR",  message,nullptr); break;
	case mType::WARN: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,		"Engine: WARNING",message,nullptr); break;
	case mType::INFO: SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,	"Engine: INFO",   message,nullptr); break;
	}
}; //For error/msg boxes
