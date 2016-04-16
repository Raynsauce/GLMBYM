#pragma once
#include "stdafx.h"

class Entity {
protected:
	typedef enum { DRAWABLE = 0, DEAD = 1 } State;
public:
	State cState;
	SDL_Rect* props;
	std::vector<SDL_Texture*> textures;
	SDL_Texture** curtex;
	SDL_Color color;

	virtual void Update(){};
};