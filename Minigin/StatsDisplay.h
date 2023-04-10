#pragma once
#include "Observer.h"

namespace dae
{
	class StatsDisplay final : public Observer
	{
	public:
		void Notify(const GameObject* actor, Event event) override;

	private:

	};
}

