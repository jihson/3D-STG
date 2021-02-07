#pragma once
#include "GameObject.h"
#include "ObjLoader.h"

using namespace HyEngine;

class UIElement
{
private:
	explicit UIElement(std::string filePath, const Vector3 & position, const Quaternion & rotation, const Vector3 & scale);
	virtual ~UIElement() = default;

private:
	virtual HRESULT Initialize();
	virtual void Update();
	virtual void Render();

protected:
	virtual void	OnMouseDown()PURE;
	virtual void	OnMouseUp()PURE;
	virtual void	OnMoisePress()PURE;

public:
	static	 UIElement* Create();
	virtual void	Free();

protected:
	class Transform* m_pTransform = nullptr;



};

