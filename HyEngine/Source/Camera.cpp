#include "StandardEngineFramework.h"
#include "Camera.h"

using namespace HyEngine;

HyEngine::Camera::Camera()
{
	m_pTransform = new Transform();
}

HyEngine::Camera::Camera(const Vector3 & originPos, const Quaternion & originRot, const Vector3 & originScale)
{
	m_pTransform = new Transform(originPos, originRot, originScale);
}


HyEngine::Camera::~Camera()
{
	delete m_pTransform;
}

void HyEngine::Camera::SetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar)
{
	D3DXMatrixPerspectiveFovLH(
		&m_matProj,
		fovy,
		screenAspect,
		screenNear,
		screenFar
	);
}

void HyEngine::Camera::Update()
{

}

Vector3 HyEngine::Camera::GetPosition() const
{
	return m_pTransform->m_position;
}

D3DXMATRIX HyEngine::Camera::GetViewMatrix() const
{
	D3DXMATRIX viewMat;
	D3DXMatrixLookAtLH
	(
		&viewMat,
		&m_pTransform->m_position.operator D3DXVECTOR3(),
		&m_pTransform->Forward().operator D3DXVECTOR3(),
		&m_pTransform->Up().operator D3DXVECTOR3()
	);

	return viewMat;
}

D3DXMATRIX HyEngine::Camera::GetProjectionMatrix() const
{
	return m_matProj;
}


void HyEngine::Camera::SetPosition(float x, float y, float z)
{
	m_pTransform->SetPosition(x, y, z);
}

Transform * HyEngine::Camera::GetTransform()
{
	return m_pTransform;
}

void HyEngine::Camera::UnProjection(Vector3 * out, Vector3 source, D3DXMATRIX world)
{
	Vector3 position = source;

	out->x() = (position.x() * 2.0f / WinMaxWidth) - 1.0f;
	out->y() = (position.y() * 2.0f / WinMaxHeight) - 1.0f;
	out->z() = position.z();

	D3DXMATRIX wvp = world * GetViewMatrix() * GetProjectionMatrix();
	D3DXMatrixInverse(&wvp, nullptr, &wvp);

	D3DXVec3TransformCoord(&out->operator D3DXVECTOR3(), &out->operator D3DXVECTOR3(), &wvp);
}
