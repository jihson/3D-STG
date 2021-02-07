#pragma once
#include "Camera.h"
class SampleCamera : public Camera
{
public:
	SampleCamera();
	~SampleCamera();


public :
	void SetOffset(const Vector3& offset);
	void SetTarget(class Transform* targetTr);
	class Transform* GetTarget();

	virtual void Initialize() override;
	virtual void Update() override;



private :
	Vector3 m_tempVec;
private: 
	float m_lerpSpd = 10;
	Vector3 m_offset;
	class Transform* m_pTarget;
};

