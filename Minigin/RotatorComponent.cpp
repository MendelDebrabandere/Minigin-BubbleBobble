#include "RotatorComponent.h"
#include <SDL_stdinc.h>
#include "Time.h"
#include "Transform.h"

void dae::RotatorComponent::Update()
{
	const auto pTransform{ GetTransform() };

	if (!pTransform) return;

	m_CurAngle += m_RotateSpeed * Time::GetInstance().GetDelta() * static_cast<float>(M_PI) / 180.0f;

	const float x{ cosf(m_CurAngle) * m_DistanceFromPivot };
	const float y{ sinf(m_CurAngle) * m_DistanceFromPivot };

	pTransform->SetLocalPosition(x, y);
}
