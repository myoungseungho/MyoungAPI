#pragma once
#include "stdafx.h"

const float M_PI = 3.14f;


template <typename T>
void Safe_Delete(T& t)
{
	if (t != nullptr)
	{
		delete t;
		t = nullptr;
	}
}

template <typename T>
void Safe_ArrayDelete(T& t)
{
	if (t != nullptr)
	{
		delete[] t;
		t = nullptr;
	}
}

struct Vector2
{
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	
	double x;
	double y;
};

enum Direction
{
	DEFAULT = 0,
	LEFT,
	TOP,
	RIGHT,
	BOTTOM,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM,
	RIGHTTOP
};

enum TimeDirection
{
	TIMEDIRECTION_LEFT,
	TIMEDIRECTION_RIGHT
};
