#pragma once
#include <vector>
#include <memory>
#include "Singleton.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class Observer;

	class Subject final : public Singleton<Subject>
	{
	public:
		template <class T>
		void AddObserver();

		void Notify(const GameObject* actor, Observer::Event event);

	private:
		std::vector<std::unique_ptr<Observer>> m_Observers{};

	};


	template<class T>
	inline void Subject::AddObserver()
	{
		m_Observers.push_back(std::make_unique<T>());
	}
}

