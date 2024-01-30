#pragma once
#include "stdafx.h"

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
	int x;
	int y;
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
