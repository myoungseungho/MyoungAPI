#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() : currentDirection(DEFAULT)
{
}


Bullet::Bullet(RECT* _initRECT) : currentDirection(DEFAULT)
{
	bulletRECT.left = _initRECT->left;
	bulletRECT.top = _initRECT->top;
	bulletRECT.right = _initRECT->right;
	bulletRECT.bottom = _initRECT->bottom;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{

}

void Bullet::SetCurrentDirection(Direction _direction)
{
	currentDirection = _direction;
}

void Bullet::SetPositionX(long _x)
{
	bulletRECT.left += _x;
	bulletRECT.right += _x;
}

void Bullet::SetPositionY(long _y)
{
	bulletRECT.top += _y;
	bulletRECT.bottom += _y;
}

void Bullet::SetRECT(RECT* _pRECT )
{
	bulletRECT = *_pRECT;
}



Direction Bullet::GetDirection()
{
	return currentDirection;
}

RECT& Bullet::GetBulletRECT()
{
	return bulletRECT;
}

