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

Model3D::Model3D()
{

}

Model3D::~Model3D()
{

}

bool Model3D::Create(const std::string& filename)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile
    (
        MODELPATH + filename,
        aiProcess_Triangulate |   //Triangulate every surface
        aiProcess_JoinIdenticalVertices |   //Ignores identical veritices - memory saving  
        aiProcess_FlipWindingOrder |   //Makes it clockwise order
        aiProcess_MakeLeftHanded |	//Use a lefthanded system for the models 
        aiProcess_CalcTangentSpace |   //Fix tangents and bitangents automatic for us
        aiProcess_FlipUVs |   //Flips the textures to fit directX-style
        aiProcess_LimitBoneWeights 		    //Limits by default to 4 weights per vertex
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Debugger::Get().Print("Assimp couldnt open: '" + filename + "'\n", Debugger::COLOR_RED);
        importer.FreeScene();
        return false;
    }

    if (!scene->HasMeshes())
    {
        DEBUG_ERROR("Model has no meshes.\n");
        return false;
    }



    importer.FreeScene();

    return true;
}
