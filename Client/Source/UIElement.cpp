#include "StandardEngineFramework.h"
#include "UIElement.h"
#include "Transform.h"

UIElement::UIElement(std::string filePath, const Vector3 & position, const Quaternion & rotation, const Vector3 & scale)
{
	m_pTransform = new Transform(position, rotation, scale);
}

HRESULT UIElement::Initialize()
{
	// UI 이미지 로드
	HyEngine::IO::Loader loader;
	if(FAILED(loader.LoadFile(filePath)))
		return E_FAIL;
}

void UIElement::Update()
{
}

void UIElement::Render()
{
// 	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
// 		wstrFilePath.c_str(),
// 		m_tTexInfo.tImageInfo.Width,
// 		m_tTexInfo.tImageInfo.Height,
// 		m_tTexInfo.tImageInfo.MipLevels,
// 		0,
// 		m_tTexInfo.tImageInfo.Format,
// 		D3DPOOL_MANAGED,
// 		D3DX_DEFAULT,
// 		D3DX_DEFAULT,
// 		0,
// 		nullptr,
// 		nullptr,
// 		&m_tTexInfo.pTexture)))
// 	{
// 		return;
// 	}
}

void UIElement::OnMouseDown()
{
}

void UIElement::OnMouseUp()
{
}

void UIElement::OnMoisePress()
{
}

UIElement * UIElement::Create()
{
	UIElement* pInstance = new UIElement();
	if (FAILED(pInstance->Initialize()))
		SAFE_DELETE(pInstance);
	return pInstance;
}

void UIElement::Free()
{
	SAFE_DELETE(m_pTransform);
}
