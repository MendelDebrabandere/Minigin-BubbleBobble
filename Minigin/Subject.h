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
		T* AddObserver();

		void RemoveObeserver(Observer* observer);

		void Notify(const GameObject* actor, Observer::Event event);

	private:
		std::vector<std::unique_ptr<Observer>> m_Observers{};

	};


	template<class T>
	inline T* Subject::AddObserver()
	{
		auto uniquePtr = std::make_unique<T>();
		const auto rawPtr = uniquePtr.get();

		m_Observers.push_back(std::move(uniquePtr));
		return rawPtr;
	}
}

