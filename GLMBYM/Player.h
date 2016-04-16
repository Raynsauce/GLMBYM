#pragma once
#include "stdafx.h"
#include "Entity.h"

class Player : public Entity {
protected:
	struct mVec { bool l:1; bool r:1; bool s:1; }; //bitfield reduces size 3x
public:
	mVec Mov;
	Player(SDL_Renderer** mainrndr);
	~Player();

	void Update(SDL_KeyboardEvent& key);
	__forceinline void Moves(void);
private:
	Uint8 Vel;
};


class Fire : public Entity {
public:
	Fire() = delete;
	Fire(SDL_Renderer** mainrndr,Player* player1);
	~Fire();
	void Update() override;
	Player* player;
};