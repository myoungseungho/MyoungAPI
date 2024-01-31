#include "stdafx.h"
#include "Player.h"

Player::Player() : playerRECT(nullptr), currentCenterPosition(nullptr), currentRotationPosition(nullptr), m_maxBullet(100), m_Radius(0.0), m_CurrentDrgree(1) {}

Player::~Player()
{
	Safe_Delete(playerRECT);
	Safe_Delete(currentCenterPosition);
}

void Player::Initialize()
{
	playerRECT = new RECT;

	playerRECT->left = 100;
	playerRECT->top = 100;
	playerRECT->right = 200;
	playerRECT->bottom = 200;
	m_Radius = (playerRECT->right - playerRECT->left) / 2;

	currentCenterPosition = new Vector2((playerRECT->left + playerRECT->right) / 2, (playerRECT->top + playerRECT->bottom) / 2);
	currentRotationPosition = new Vector2(currentCenterPosition->x, playerRECT->top);
	vecUnUsedBullet.reserve(100);
	ObjectPool();
}

void Player::SetPositionX(long _input)
{
	playerRECT->left += _input;
	playerRECT->right += _input;
}

void Player::SetPositionUp(long _input)
{
	Vector2 newVector = Vector2::GetDirectionVector(*currentCenterPosition, *currentRotationPosition);
	playerRECT->top += _input;
	playerRECT->bottom += _input;
	currentRotationPosition->y += _input;
}

void Player::SetRotation(TimeDirection _direction)
{
	currentCenterPosition->x = (playerRECT->left + playerRECT->right) / 2;
	currentCenterPosition->y = (playerRECT->top + playerRECT->bottom) / 2;

	double radians = m_CurrentDrgree * (M_PI / 180.f);
	double x = 0.0;
	double y = 0.0;

	switch (_direction)
	{
	case TIMEDIRECTION_LEFT:
		m_CurrentDrgree++;
		x = currentCenterPosition->x - (m_Radius * sin(radians));
		y = currentCenterPosition->y - (m_Radius * cos(radians));

		currentRotationPosition->x = x;
		currentRotationPosition->y = y;
		break;
	case TIMEDIRECTION_RIGHT:
		m_CurrentDrgree--;
		x = currentCenterPosition->x - (m_Radius * sin(radians));
		y = currentCenterPosition->y - (m_Radius * cos(radians));

		currentRotationPosition->x = x;
		currentRotationPosition->y = y;
		break;
	case TIMEDIRECTION_TOP:
		break;
	case TIMEDIRECTION_BOTTOM:
		break;
	}
}

void Player::SetVecRePut(Bullet* _pBullet)
{
	vecUnUsedBullet.push_back(_pBullet);
}

RECT* Player::GetRECT() const
{
	return playerRECT;
}

Vector2* Player::GetCenterPosition()
{
	return currentCenterPosition;
}

Vector2* Player::GetCurrentRotationPosition()
{
	return currentRotationPosition;
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
