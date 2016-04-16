#include "stdafx.h"
#include "Mob.h"


Mob::Mob(SDL_Renderer** mainrndr,aType alienType)
{
	std::random_device mpSeed;
	mposRand = new std::mt19937;

	std::mt19937 m_mpRand(mpSeed());
	*mposRand = m_mpRand;

	mtMob = new std::uniform_int_distribution<int>;
	std::uniform_int_distribution<int>	m_mtMob(0,127);
	*mtMob = m_mtMob;

	mDir = static_cast<unsigned>((*mtMob)(*mposRand));
	waitTime = 0;

	props = new SDL_Rect;	*props = {};
	char file0[22];
	char file1[22];
	snprintf(file0,22, "assets\\alien_%s0.png", alienType.type);
	snprintf(file0,22, "assets\\alien_%s1.png", alienType.type);

	textures.push_back(IMG_LoadTexture(*mainrndr,file0));
	textures.push_back(IMG_LoadTexture(*mainrndr,file1));
	curtex = &textures[0];

	SDL_QueryTexture(*curtex,nullptr,nullptr,&(props->w),&(props->h));
	props->x = (WIDTH/2 - props->w/2);

	props->y = (6 * (alienType.ln * 2));

	color = {0xFF,0xFF,0xFF, 0xFF};
	cState = State::DRAWABLE;
}
Mob::~Mob()
{
	for(auto& tex : textures){ SDL_DestroyTexture(tex); }
	delete mposRand;
	delete mtMob;

	delete props;
}

void Mob::Update()
{
	mDir = static_cast<unsigned>((*mtMob)(*mposRand));	//Must be set every Update
	if(waitTime >= 16){
		switch(static_cast<bool>(mDir >= 64)){
		case 1:
			if(props->x+props->w > WIDTH){ props->x -= 8; } else { props->x += 8; }
			break;
		case 0:
			if(props->x < 0){ props->x += 8; } else { props->x -= 8; }
			break;
		}
		waitTime = 0;
	} else { waitTime++; }
}
