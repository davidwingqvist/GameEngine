#include "Header.h"
#include "Resource.h"
#include "Debugger.h"


Image2D::Image2D()
{
    m_image = nullptr;
}

Image2D::~Image2D()
{
    if (m_image)
        m_image->Release();
}

ID2D1Bitmap* const Image2D::GetImage() const
{
    return m_image;
}

bool Image2D::Create(const std::string& filename)
{
    return D2D1Core::Get().CreateImage(filename, &m_image);
}
