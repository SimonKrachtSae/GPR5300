#pragma once
#include "Mesh.h"
#include "Light.h"
#include "resource.h"
#include "Material.h"
#include"D3D.h"
#include"Vertex.h"
#include "Window.h"

class Shape 
{
public:
	Material Material = {};
	Mesh Mesh = {};
	Light::LightData LightData = {};
	Light Light = {};

	/// <summary>
	/// Currently active texture
	/// </summary>
	int Texture = IDC_STONES;

	/// <summary>
	/// Currently active shader
	/// </summary>
	int Shader = IDC_BLINNPHONG;

	BOOL IsInitialized = FALSE;

	void init(D3D* d3d);

	void deInit();

	/// <summary>
	/// Set world position to: (0,0,0)
	/// </summary>
	void SetDefaultPos();

	/// <summary>
	/// Set world position to (x,y,z)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="z"></param>
	void SetPositionOffset(float x, float y, float z);

	/// <summary>
	/// Initialize the mesh component
	/// </summary>
	/// <param name="d3dDevice"></param>
	/// <param name="xOffset"></param>
	/// <param name="yOffset"></param>
	/// <param name="zOffset"></param>
	void InitMesh(ID3D11Device *d3dDevice, FLOAT xOffset, FLOAT yOffset, FLOAT zOffset);
    
	Vertex *vertices = nullptr;
	USHORT *indices = nullptr;

protected:
	XMFLOAT3 vertPosOffset = { 0,0,0 };

	/// <summary>
	/// Configure Light::LightData parameters
	/// </summary>
	virtual void initLightData() {};

	/// <summary>
	/// Configure custom data for vertex and indexbuffer 
	/// </summary>
	virtual void initMeshData() {};

	int indexCount;
	int vertexCount;
};

class Plane : public Shape
{
private:
	void initLightData() override;
	void initMeshData() override;
};

class Cube : public Shape
{
private:
	void initLightData() override;
	void initMeshData() override;
};

class Pyramid : public Shape
{
private:
	void initLightData() override;
	void initMeshData() override;
};