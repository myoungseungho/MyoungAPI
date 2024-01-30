#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Player.h"

//발사 방향
//발사 시작 좌표
class Bullet
{
public:
	Bullet();
	Bullet(RECT* _initRECT);
	~Bullet();
public:
	void Update();

public:
	void SetCurrentDirection(Direction);
	void SetPositionX(long);
	void SetPositionY(long);
	void SetRECT(RECT*);
public:
	RECT& GetBulletRECT();
	Direction GetDirection();
private:
	RECT bulletRECT;
	Direction currentDirection;
};

