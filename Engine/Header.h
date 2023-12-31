#pragma once
#include "../recs_base.h"

// DirectXTK
#include <SimpleMath.h>
#include <BufferHelpers.h>
#include <Keyboard.h>
#include <Mouse.h>

// STANDARD LIBRARY
#include <memory>
#include <time.h>
#include <string>
#include <functional>
#include <chrono>

// DirectX
#include <d3d11.h>
#include <d2d1.h>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace dx = DirectX;
namespace sm = DirectX::SimpleMath;

#include "Structs.h"


const std::string UIPATH = "Content/Graphics2D/";
const std::string MODELPATH = "Content/Models/";