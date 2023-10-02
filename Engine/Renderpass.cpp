#include "Header.h"
#include "Renderpass.h"

void IRenderpass::SetActive(const bool& tog)
{
    m_isActive = tog;
}

const bool& IRenderpass::IsActive() const
{
    return m_isActive;
}
