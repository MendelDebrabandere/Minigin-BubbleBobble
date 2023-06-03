#pragma once
#include <glm/vec2.hpp>

#include "Component.h"

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

private:
	glm::vec2 m_LastPos{};
};
