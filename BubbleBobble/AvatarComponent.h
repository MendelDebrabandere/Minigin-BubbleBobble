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

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;

	AvatarState GetCurrState() const;

private:
	void UpdateAnimVariablesMoving();
	void DoRespawnLogic();

	AvatarState m_CurrentState{ AvatarState::Moving };

	glm::vec2 m_LastPos{};

	float m_Timer{};

	float m_MaxRespawmTimer{ 3.f };

	//using a bool for this state since it can be active in multiple states
	bool m_Invulnerable{};
	float m_MaxInvulnerableTime{6.f};
};
