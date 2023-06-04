#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

class AvatarComponent : public dae::Component
{
public:
	enum class AvatarState
	{
		Moving,
		Hit
	};

	AvatarComponent() = default;
	virtual ~AvatarComponent() = default;

	AvatarComponent(const AvatarComponent& other) = delete;
	AvatarComponent(AvatarComponent&& other) = delete;
	AvatarComponent& operator=(const AvatarComponent& other) = delete;
	AvatarComponent& operator=(AvatarComponent&& other) = delete;

	void Update() override;
	void FixedUpdate() override;

	AvatarState GetCurrState() const;

private:
	void CheckAnimPauseWithMovement();
	void DoEnemyHitDetection();
	void DoRespawnLogic();

	AvatarState m_CurrentState{ AvatarState::Moving };

	glm::vec2 m_LastPos{};

	float m_RespawnTimer{};
	float m_MaxRespawmTimer{ 3.f };
};
