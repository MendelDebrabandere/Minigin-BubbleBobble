#include "ShootBubbleCommand.h"

#include "Bubble.h"
#include "SceneManager.h"
#include "Timer.h"

void ShootBubbleCommand::Execute()
{
	dae::Scene* scene = dae::SceneManager::GetInstance().GetActiveScene();

	Bubble::CreateBubble(scene, m_pGo->GetTransform()->GetWorldPosition());
	std::cout << "Shooting bubble\n";
}