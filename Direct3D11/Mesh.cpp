#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include <xutility>
#include "resource.h"

INT Mesh::init(ID3D11Device* pD3DDevice, int indexCount, int vertexCount, USHORT** indices, Vertex** vertices)
{
	INT error = initVertexBuffer(pD3DDevice, vertexCount, vertices);
	CheckError(error);

	error = initIndexBuffer(pD3DDevice, indexCount, indices);
	CheckError(error);

	// initialize world transformation matrix
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());
	IsInitialized = TRUE;

	return 0;
}

void Mesh::update(FLOAT dt)
{
	static FLOAT posX = 0.0f;
	static FLOAT posY = 0.0f;
	static FLOAT posZ = 0.0f;
	static FLOAT rotY = 0.0f;
	static FLOAT rotX = 0.0f;

	FLOAT move = 5.0f * dt;

	if ((GetAsyncKeyState(VK_SHIFT) & 0x8000))
	{
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			rotY -= XM_PI / 3.0f * dt;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			rotY += XM_PI / 3.0f * dt;
		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			rotX += XM_PI / 3.0f * dt;
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			rotX -= XM_PI / 3.0f * dt;
	}
	else
	{
		if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000) && posZLimit <= 2.0f)
		{
			posZ += move;
			posZLimit += move;
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000) && posZLimit >= -2.0f)
		{
			posZ -= move;
			posZLimit -= move;
		}
	}

	XMMATRIX translation = XMMatrixTranslation(posX, posY, posZ);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(rotX, rotY, 0.0f);
	XMMATRIX localScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	XMStoreFloat4x4(&_worldMatrix, localScale * rotation * translation);
}

void Mesh::render(ID3D11DeviceContext* pD3DDeviceContext)
{
	// set mesh data
	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R16_UINT, offset);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw with index buffer
	pD3DDeviceContext->DrawIndexed(_indexCount, 0, 0);
}

void Mesh::deInit()
{
	IsInitialized = false;
	safeRelease<ID3D11Buffer>(_pVertexBuffer);
	safeRelease<ID3D11Buffer>(_pIndexBuffer);
}

void Mesh::ResetWorldTransform()
{
	_worldMatrix = XMFLOAT4X4();
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());
}

INT Mesh::initVertexBuffer(ID3D11Device* pD3DDevice, int vertexCount, Vertex** vertices)
{
	_vertexCount = vertexCount;

	_vertexStride = sizeof(Vertex);

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _vertexCount * _vertexStride;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // buffer type
	desc.Usage = D3D11_USAGE_IMMUTABLE; // who has which access

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = vertices[0];

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &initialData, &_pVertexBuffer);
	CheckFailed(hr, 30);

	return 0;
}

INT Mesh::initIndexBuffer(ID3D11Device* pD3DDevice, int indexCount, USHORT** indices)
{
	_indexCount = indexCount;

	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = _indexCount * sizeof(USHORT);
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA initialData = {};
	initialData.pSysMem = indices[0];

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, &initialData, &_pIndexBuffer);
	CheckFailed(hr, 32);

	return 0;
}
