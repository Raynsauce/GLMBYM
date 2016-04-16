#pragma once
#include "stdafx.h"
#include "Entity.h"

struct aType { aType(unsigned lnm,const char* aname){ ln = lnm; type = aname; }; unsigned ln; const char* type; };

class Mob : public Entity {
public:
	Mob(SDL_Renderer** mainrndr,aType alien_type);
	~Mob();

	void Update() override;
private:
	std::mt19937* mposRand;
	std::uniform_int_distribution<int>* mtMob;

	unsigned mDir;
	unsigned waitTime;
};