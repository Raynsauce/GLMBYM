#include "stdafx.h"
#include "Player.h"

Fire::Fire(SDL_Renderer** mainrndr,Player* player1)
{
	this->player = player1;
	props = new SDL_Rect; *props = {};

	textures.push_back(IMG_LoadTexture(*mainrndr,"assets\\player_fire.png"));
	curtex = &textures[0];
	SDL_QueryTexture(*curtex,nullptr,nullptr,&(props->w),&(props->h));

	props->y = player->props->y;
	props->x = (player->props->x + (player->props->w/2)-1);

	color = {0x44,0x44,0xFF, 0xFF};
	cState = State::DRAWABLE;
}
Fire::~Fire()
{
	for(auto& tex : textures){ SDL_DestroyTexture(tex); }
	delete props;
}
void Fire::Update()
{
	switch(player->Mov.s){
	case true: props->y -= 2; break;
	default: props->x = (player->props->x + (player->props->w/2)-1); break;
	}
	switch(props->y <= 0){
	case true: cState = DEAD; break;
	default: break;
	}
}

Player::Player(SDL_Renderer** mainrndr)
{
	///std::cout << "Sizeof mVec: " << sizeof(mVec) << std::endl;
	props = new SDL_Rect;	*props = {};
	textures.push_back(IMG_LoadTexture(*mainrndr,"assets\\player.png"));
	textures.push_back(IMG_LoadTexture(*mainrndr,"assets\\player_dead.png"));
	curtex = &(textures)[0];
	
	SDL_QueryTexture(*curtex,nullptr,nullptr,&(props->w),&(props->h));
	props->x = (WIDTH/2 - props->w/2);
	props->y = (HEIGHT-16);

	Mov = {};
	Vel = 2;
	color = {0x10,0xFF,0x10, 0xFF};
	
	cState = State::DRAWABLE;
}
Player::~Player()
{
	for(auto& tex : textures){ SDL_DestroyTexture(tex); }
	delete props;
}

void Player::Update(SDL_KeyboardEvent& key)
{
	switch(key.type){
	case SDL_KEYDOWN:
		switch(key.keysym.sym){
		case SDLK_a: Mov.l	= 1;	break;
		case SDLK_d: Mov.r	= 1;	break;
		case SDLK_SPACE: Mov.s = 1; break;
		default: break;
		} break;
	case SDL_KEYUP:
		switch(key.keysym.sym){
		case SDLK_a: Mov.l	= 0;	break;
		case SDLK_d: Mov.r	= 0;	break;
		//case SDLK_SPACE: Mov.s = 0; break;
		default: break;
		} break;
	default: break;
	}
	Moves();
}
__forceinline void Player::Moves(void) //YU VILL INLINE UND ONLY INLINE
{
	switch(cState){
	case State::DRAWABLE:
		if((props->x < 0)){ props->x = 0; }
		else if((props->x+props->w) > WIDTH){ props->x = (WIDTH-props->w); }
		else {
			switch(Mov.l){
			case true: props->x -= Vel; break;
			default: break;		/* Moved Left == 0 */
			}		
			switch(Mov.r){
			case true: props->x += Vel; break;
			default: break;		/* Moved Right == 0 */
			}
		}
		default: break;
	}
}