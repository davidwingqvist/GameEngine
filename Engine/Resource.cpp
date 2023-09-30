#include "Header.h"
#include "Resource.h"
#include "Debugger.h"
#include "D3D11Context.h"


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

bool Model3D::CreateVertexBuffer(std::vector<model_data>& modelData)
{
    if (modelData.empty())
        return false;

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = static_cast<UINT>(sizeof(model_data) * modelData.size());
    desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = &modelData[0];
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    this->vertexCount = static_cast<UINT>(modelData.size());
    HRESULT hr = D3D11Core::Get().Device()->CreateBuffer(&desc, &data, &vertexBuffer);
    return !FAILED(hr);
}

bool Model3D::CreateIndexBuffer(std::vector<UINT>& indices)
{
    if (indices.empty())
        return false;

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
    desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = &indices[0];
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    this->indexCount = static_cast<UINT>(indices.size());
    HRESULT hr = D3D11Core::Get().Device()->CreateBuffer(&desc, &data, &indexBuffer);
    return !FAILED(hr);
}

Model3D::Model3D()
{

}

Model3D::~Model3D()
{
    if (vertexBuffer)
        vertexBuffer->Release();
    if (indexBuffer)
        indexBuffer->Release();
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

    UINT indexOffset = 0;
    UINT localMaxIndex = 0;
    std::vector<model_data> data;
    std::vector<UINT> indices;
    for (int i = 0; i < scene->mNumMeshes; i++)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        for (int j = 0; j < mesh->mNumVertices; j++)
        {
            model_data mData;
            mData.x = mesh->mVertices->x;
            mData.y = mesh->mVertices->y;
            mData.z = mesh->mVertices->z;
            data.push_back(mData);
        }

        for (unsigned int f = 0; f < mesh->mNumFaces; f++)
        {
            const aiFace face = mesh->mFaces[f];
            if (face.mNumIndices == 3)
            {
                for (unsigned int id = 0; id < 3; id++)
                {
                    UINT faceIndex = face.mIndices[id];
                    if (faceIndex > localMaxIndex)
                        localMaxIndex = faceIndex;

                    indices.push_back(face.mIndices[id] + indexOffset);
                }
            }
        }
    }

    if (!this->CreateVertexBuffer(data))
        DEBUG_ERROR("Couldnt create vertex buffer for model: '" + filename + "'\n");
    if(!this->CreateIndexBuffer(indices))
        DEBUG_ERROR("Couldnt create index buffer for model: '" + filename + "'\n");



    importer.FreeScene();

    return true;
}
