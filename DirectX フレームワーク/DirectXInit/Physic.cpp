#include "Physic.h"

void Physic::Update()
{
	m_Velocity += m_Acceleration;
	m_Position += m_Velocity;
	Quad::Update();
}

void Physic::SetVelo(float _vx, float _vy, float _vz)
{
	m_Velocity.x = _vx;
	m_Velocity.y = _vy;
	m_Velocity.z = _vz;
}

void Physic::SetAcce(float _ax, float _ay, float _az)
{
	m_Acceleration.x = _ax;
	m_Acceleration.y = _ay;
	m_Acceleration.z = _az;
}