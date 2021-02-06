#pragma once

namespace HyEngine
{
	using namespace Math;

	class ENGINE_DLL Camera
	{
	public:
		explicit Camera();
		explicit Camera(const Vector3& originPos, const Quaternion& originRot, const Vector3& originScale);
		virtual ~Camera();

		virtual void Update();



		void SetProjectionMatrix(float fovy, float screenAspect, float screenNear, float screenFar);
		Vector3 GetPosition() const;
		D3DXMATRIX GetViewMatrix() const;
		D3DXMATRIX GetProjectionMatrix() const;

		void SetPosition(float x, float y, float z);
		class Transform* GetTransform();
		//void Rotate();

		// source = mosue position
		void UnProjection(_Out_ Vector3* out, Vector3 source, D3DXMATRIX world);

		
	private:
		
		float m_moveSpeed = 1; 
		float m_rotSpeed = 1; 

		D3DXMATRIX m_matProj;

		class Transform * m_pTransform;
	};
}

