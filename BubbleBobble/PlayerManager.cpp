#include "PlayerManager.h"

#include "Avatar.h"
#include "HUD.h"
#include "SceneManager.h"


using namespace dae;

PlayerManager::~PlayerManager()
{
	SceneManager::GetInstance().onSceneLoaded.RemoveObserver(this);
}

void PlayerManager::Init()
{
	SceneManager::GetInstance().onSceneLoaded.AddObserver(this);
}

void PlayerManager::HandleEvent(Scene* scene)
{
	if (scene->GetName().find("Level") == std::string::npos)
		return;

	AddPlayersToLevel(scene);
	AddHudToLevel(scene);
}

void PlayerManager::AddPlayer(bool /*useKeyboard*/, const int controllerIdx)
{
	if (m_ControllersInUse.empty() == false && std::ranges::find(m_ControllersInUse, controllerIdx) != m_ControllersInUse.end())
	{
		std::cout << "Controller has already been assigned to a character\n";
		return;
	}


	//auto& input = real::Input::GetInstance();
	//real::InputMap* pInputMap;

	//std::shared_ptr<real::Texture2D> pCharacterTexture;

	//if (m_PlayerPtrs.empty())
	//{
	//	InitHud();
	//	pCharacterTexture = real::ResourceManager::GetInstance().LoadTexture("characters/PeterPepper.png");
	//	pInputMap = input.AddInputMap(InputMaps::gameplay);
	//	real::Logger::LogInfo("Player 1 has been initialized");
	//}
	//else if (m_PlayerPtrs.size() == 1)
	//{
	//	if (useKeyboard && m_KeyboardInUse)
	//	{
	//		real::Logger::LogWarning("The keyboard is already linked to an existing player");
	//		return;
	//	}

	//	input.EnableCoOp(true);
	//	pCharacterTexture = real::ResourceManager::GetInstance().LoadTexture("characters/SallySalt.png");
	//	pInputMap = input.GetInputMap(InputMaps::gameplay);
	//	real::Logger::LogInfo("Player 2 has been initialized");
	//}
	//else
	//{
	//	real::Logger::LogWarning("There are already 2 players initialized");
	//	return;
	//}


}

void PlayerManager::AddHudToLevel(Scene* pScene)
{
	HUD::CreateHUD(pScene);
}

void PlayerManager::AddPlayersToLevel(dae::Scene* pScene)
{
	Avatar::CreateAvatar(pScene, greenSpawnPos);
}
