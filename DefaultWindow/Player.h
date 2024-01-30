#pragma once
#include "stdafx.h"
#include "Define.h"
#include "Bullet.h"

//�÷��̾��� ����
//�÷��̾� RECT
//�÷��̾� �߽���ǥ
//�÷��̾� BulletList
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
	void SetPositionY(long);
	void SetVecRePut(Bullet*);
public:
	RECT* GetRECT() const;
	list<Bullet*>& GetBulletList();
public:
	void ShotBullet(Direction);
	void ObjectPool();
private:
	void SaveBullet(Bullet*);

private:
	RECT* playerRECT;
	Vector2* currentPosition;
	vector<Bullet*> vecUnUsedBullet;
	list<Bullet*> listUsedBullet;
	int m_maxBullet;
};

