#pragma once

struct object2D
{
	float x;
	float y;
	float width;
	float height;

	object2D()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	object2D(const float& x, const float& y, const float& width, const float& height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	object2D(const std::string& filename)
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
};

struct object3D
{
	sm::Vector3 position;
};

struct model
{
	sm::Matrix worldMatrix;
};
