#pragma once
#include "Observer.h"

namespace dae
{
	class StatsDisplay final : public Observer
	{
	public:
		void Notify(const GameObject* actor, Event event) override;

		void SetPlayerObject(GameObject* actor);
		void SetHealthTextObject(GameObject* actor);
		void SetScoreTextObject(GameObject* actor);
	private:
		GameObject* m_pPlayerObj{};
		GameObject* m_pHealthTextObject{};
		GameObject* m_pScoreTextObject{};
	};
}

