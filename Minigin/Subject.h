#pragma once
#include <vector>
#include <memory>
#include "Singleton.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class Observer;
	//TODO: Shouldnt own Observers
	//TODO: Not a singleton
	class Subject final : public Singleton<Subject>
	{
	public:
		template <class T>
		T* AddObserver();

		void UpdateCleanup();

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

