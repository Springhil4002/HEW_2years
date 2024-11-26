#include "Player.h"

void Player::Walk() {
	if (input.GetKeyPress(VK_D))
	{
		m_Position.x += 0.5f;
	}
	if (input.GetKeyPress(VK_A))
	{
		m_Position.x -= 0.5f;
	}
}

