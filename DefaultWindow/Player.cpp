#include "stdafx.h"
#include "Player.h"

Player::Player() : playerRECT(nullptr), currentPosition(nullptr), m_maxBullet(100) {}

Player::~Player()
{
	Safe_Delete(playerRECT);
	Safe_Delete(currentPosition);
}

void Player::Initialize()
{
	playerRECT = new RECT;

	playerRECT->left = 100;
	playerRECT->top = 100;
	playerRECT->right = 200;
	playerRECT->bottom = 200;

	currentPosition = new Vector2;
	currentPosition->x = (playerRECT->left + playerRECT->right) / 2;
	currentPosition->y = (playerRECT->top + playerRECT->bottom) / 2;

	vecUnUsedBullet.reserve(100);
	ObjectPool();
}

void Player::SetPositionX(long _input)
{
	playerRECT->left += _input;
	playerRECT->right += _input;
}

void Player::SetPositionY(long _input)
{
	playerRECT->top += _input;
	playerRECT->bottom += _input;
}

void Player::SetVecRePut(Bullet* _pBullet)
{
	vecUnUsedBullet.push_back(_pBullet);
}

RECT* Player::GetRECT() const
{
	return playerRECT;
}


list<Bullet*>& Player::GetBulletList()
{
	return listUsedBullet;
}

void Player::ShotBullet(Direction _direction)
{
	if (vecUnUsedBullet.size() != 0)
	{
		Bullet* pBullet = vecUnUsedBullet.back();
		pBullet->SetCurrentDirection(_direction);
		pBullet->SetRECT(playerRECT);
		SaveBullet(pBullet);
  		vecUnUsedBullet.pop_back();
	}
	else
		return;
}



void Player::ObjectPool()
{
	for (size_t i = 0; i < m_maxBullet; i++)
	{
		vecUnUsedBullet.push_back(new Bullet(playerRECT));
	}
}

void Player::SaveBullet(Bullet* _pUsedBullet)
{
	if (_pUsedBullet != nullptr)
	{
		listUsedBullet.push_back(_pUsedBullet);
	}
	else
		return;
}
