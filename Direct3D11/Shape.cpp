#include "Shape.h"

void Shape::init(D3D* d3d)
{
	if (!IsInitialized)
	{
		initLightData();
		initMeshData();
	}

	Material.init(d3d->getDevice(), Texture, Shader);
	Light.init(d3d->getDevice(), LightData);
	
	IsInitialized = TRUE;
}

void Shape::deInit()
{
	SetDefaultPos();
	Material.deInit();
	Mesh.deInit();
	Light.deInit();
	delete(vertices);
	delete(indices);
	IsInitialized = FALSE;
}

void Shape::SetDefaultPos()
{
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].position.x -= vertPosOffset.x;
		vertices[i].position.y -= vertPosOffset.y;
		vertices[i].position.z -= vertPosOffset.z;
	}
	vertPosOffset = XMFLOAT3(0, 0, 0);
}

void Shape::SetPositionOffset(float x, float y, float z)
{
	vertPosOffset = XMFLOAT3(vertPosOffset.x + x, vertPosOffset.y + y, vertPosOffset.z + z);
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].position.x += x;
		vertices[i].position.y += y;
		vertices[i].position.z += z;
	}
}

void Shape::InitMesh(ID3D11Device* d3dDevice, FLOAT xOffset, FLOAT yOffset, FLOAT zOffset)
{
	SetPositionOffset(xOffset, yOffset, zOffset);
	Mesh.init(d3dDevice, indexCount, vertexCount, &indices, &vertices);
}

void Plane::initLightData()
{
	Texture = IDC_STONES;
	Shader = IDC_LAMBERTIAN;

	LightData.lightPosition = { 0.0f, 0.0f, -1.0f };
	LightData.lightIntensity = 0.7f;
	LightData.surrLightIntensity = 0.7f;
	LightData.matAmbient = { 0.1f,0.1f,0.1f, 1.0f };
	LightData.matDiffuse = { 0.1f,0.2f,0.3f,1.0f };
	LightData.matSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };
	LightData.surfaceTex = 30.0f;
}

void Plane::initMeshData()
{
	vertexCount = 8;
	indexCount = 12;
	vertices = new Vertex[vertexCount] {

		//Top
		Vertex(-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		//Bottom
		Vertex(-0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f)
	};
	indices = new USHORT[indexCount] {
		0,1,2,
		0,2,3,
		4,5,6,
		4,6,7
	};
}

void Cube::initLightData()
{
	Texture = IDC_WOOD;
	Shader = IDC_BLINNPHONG;

	LightData.lightPosition = { 0.0f, 0.0f, -1.0f };
	LightData.lightIntensity = 1.0f;
	LightData.surrLightIntensity = 1.0f;
	LightData.matAmbient = { 0.1f,0.1f,0.1f, 1.0f };
	LightData.matDiffuse = { 0.1f,0.2f,0.3f,1.0f };
	LightData.matSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };
	LightData.surfaceTex = 2.0f;
}

void Cube::initMeshData()
{
	vertexCount = 24;
	indexCount = 36;
	vertices = new Vertex[vertexCount]
	{
		//front
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
		//right 
		Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
		//top
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		//bottom
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 1.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f),
		//back
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f),
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f),
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f),
		//left
		Vertex(-0.5f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
		Vertex(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f)
	};
	indices = new USHORT[indexCount] 
	{
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23
	};
}

void Pyramid::initLightData()
{
	Texture = IDC_ALUMINIUM;
	Shader = IDC_PHONG;

	LightData.lightPosition = { 0.0f, 0.0f, -1.0f };
	LightData.lightIntensity = 0.7f;
	LightData.surrLightIntensity = 1.0f;
	LightData.matAmbient = { 0.1f,0.1f,0.1f, 1.0f };
	LightData.matDiffuse = { 0.1f,0.2f,0.3f,1.0f };
	LightData.matSpecular = { 0.8f, 0.8f, 0.8f, 1.0f };
	LightData.surfaceTex = 10.0f;
}

void Pyramid::initMeshData()
{
	vertexCount = 16;
	indexCount = 18;

	vertices = new Vertex[vertexCount] {
		//FrontFace
		Vertex(-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.75f, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 1.0f),
		Vertex(0.5f, 0.0f, -0.5f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f),
		//BackFace
		Vertex(0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.75f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f),
		Vertex(-0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		//LeftFace
		Vertex(-0.5f, 0.0f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.75f, 0.0f, -1.0f, 1.0f, 0.0f, 0.5f, 1.0f),
		Vertex(-0.5f, 0.0f, -0.5f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		//RightFace
		Vertex(0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(0.0f, 0.75f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f),
		Vertex(0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f),
		//BottomQuad
		Vertex(-0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
		Vertex(0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f)
	};
	indices = new USHORT[indexCount]  
	{
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		12,14,15
	};
}
