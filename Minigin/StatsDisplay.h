#pragma once
#include "Observer.h"

namespace dae
{
	class StatsDisplay final : public Observer
	{
	public:
		void Notify(const GameObject* actor, Event event) override;

		void SetPlayerObject(GameObject* actor);
		void SetTextObject(GameObject* actor);
	private:
		GameObject* m_pPlayerObj{};
		GameObject* m_pTextObject{};
	};
}

