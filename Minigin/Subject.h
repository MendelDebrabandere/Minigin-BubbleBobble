#pragma once
#include <vector>

namespace dae
{
	class Observer;

	class Subject
	{
	public:
		explicit Subject() = default;
		virtual ~Subject() = default;
		Subject(const Subject&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator=(const Subject&) = delete;
		Subject& operator=(Subject&&) = delete;

		void Notify(size_t subject, int event, int value);
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	private:
		std::vector<Observer*> mpObservers;
	};

}

