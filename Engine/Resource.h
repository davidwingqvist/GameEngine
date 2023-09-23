#pragma once
#include <string>
#include "Direct2DContext.h"

class IResource
{
private:

public:

	IResource() = default;
	virtual ~IResource() = 0 {};

	virtual bool Create(const std::string& filename) = 0;
};

class Image2D : public IResource
{
private:

	ID2D1Bitmap* m_image;

public:

	Image2D();
	~Image2D();

	ID2D1Bitmap* const GetImage() const;

	// Inherited via IResource
	virtual bool Create(const std::string& filename) override;

};
