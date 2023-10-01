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

class Model3D : public IResource
{
private:

	ID3D11Buffer* vertexBuffer = nullptr;
	UINT vertexCount = 0;
	ID3D11Buffer* indexBuffer = nullptr;
	UINT indexCount = 0;

	bool CreateVertexBuffer(std::vector<model_data>& modelData);

	bool CreateIndexBuffer(std::vector<UINT>& indices);

	void LoadBufferData(const aiScene* scene, const std::string& filename);

public:

	Model3D();
	~Model3D();

	void Draw();

	// Inherited via IResource
	virtual bool Create(const std::string& filename) override;
};
