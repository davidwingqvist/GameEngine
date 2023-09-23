#pragma once

class IDrawObject
{
public:

	IDrawObject();

	virtual ~IDrawObject() = 0 {};

	virtual void Draw() = 0;

};