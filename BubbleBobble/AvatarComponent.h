#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

enum class AvatarState
{
	Moving,
	Respawning
};

class AvatarComponent : public dae::Component
{
public:
	AvatarComponent() = default;
	virtual ~AvatarComponent() = default;

	AvatarComponent(const AvatarComponent& other) = delete;
	AvatarComponent(AvatarComponent&& other) = delete;
	AvatarComponent& operator=(const AvatarComponent& other) = delete;
	AvatarComponent& operator=(AvatarComponent&& other) = delete;

	void Update() override;

	AvatarState GetCurrState() const;

private:
	AvatarState m_CurrentState{ AvatarState::Moving };


	glm::vec2 m_LastPos{};
};
