#pragma once
#include "Quad.h"
class Physic : public Quad
{
protected:
	DirectX::SimpleMath::Vector3 m_Velocity;
	DirectX::SimpleMath::Vector3 m_Acceleration;

public:
	void Update();

	void SetVelo(float _vx, float _vy, float _vz);
	void SetAcce(float _ax, float _ay, float _az);
};