#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Player.h"

//�߻� ����
//�߻� ���� ��ǥ
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

