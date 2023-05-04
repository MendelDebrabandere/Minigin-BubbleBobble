#include "Subject.h"
#include "Observer.h"

using namespace dae;

void Subject::Notify(size_t subject, int event, int value)
{
	for (auto pObserver : mpObservers)
		pObserver->OnNotify(subject, event, value);
}

void Subject::AddObserver(Observer* pObserver)
{
	mpObservers.push_back(pObserver);
}

void Subject::RemoveObserver(Observer* pObserver)
{
	mpObservers.erase(
		std::remove_if(mpObservers.begin(), mpObservers.end(),
			[pObserver](Observer* pObs) { return pObs == pObserver; }
		),
		mpObservers.end()
	);
}
