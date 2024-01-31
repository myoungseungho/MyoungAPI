#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Bullet.h"

//플레이어의 정보
//플레이어 RECT
//플레이어 중심좌표
//플레이어 BulletList
class Bullet;

class Player
{
public:
	Player();
	~Player();
public:
	void Initialize();
public:
	void SetPositionX(long);
	void SetPositionUp(long);
	void SetRotation(TimeDirection);

	void SetVecRePut(Bullet*);
public:
	RECT* GetRECT() const;
	Vector2* GetCenterPosition();
	Vector2* GetCurrentRotationPosition();
	list<Bullet*>& GetBulletList();
public:
	void ShotBullet(Direction);
	void ObjectPool();
private:
	void SaveBullet(Bullet*);

private:
	RECT* playerRECT;
	Vector2* currentCenterPosition;
	Vector2* currentRotationPosition;
	vector<Bullet*> vecUnUsedBullet;
	list<Bullet*> listUsedBullet;
	int m_maxBullet;
	double m_Radius;
	int m_CurrentDrgree;

};

