#pragma once
#include "Observer.h"
#include "Scene.h"
#include "Singleton.h"

//==================================
//	This is based on Michiel Dewachtere's SpriteComponent
//	Github: https://github.com/MichielDewachtere/GameEngine/blob/main/BurgerTime/PlayerManager.h
//==================================


class PlayerManager final
	: public dae::Singleton<PlayerManager>
	, public dae::Observer<dae::Scene*>
{
public:
	~PlayerManager() override;
	PlayerManager(const PlayerManager& other) = delete;
	PlayerManager operator=(const PlayerManager& rhs) = delete;
	PlayerManager(PlayerManager&& other) = delete;
	PlayerManager operator=(PlayerManager&& rhs) = delete;

	void Init();

	void HandleEvent(dae::Scene*) override;
	void OnSubjectDestroy() override {}

	void AddPlayer(bool useKeyboard = true, const int controllerIdx = -1);
	int GetAmountOfPlayers() const { return static_cast<int>(m_PlayerPtrs.size()); }

private:
	friend class Singleton<PlayerManager>;
	PlayerManager() = default;

	std::vector<std::shared_ptr<dae::GameObject>> m_PlayerPtrs{};

	bool m_KeyboardInUse{};
	std::vector<int> m_ControllersInUse{};

	void AddHudToLevel(dae::Scene* pScene);
	void AddPlayersToLevel(dae::Scene* pScene);

	//AVATAR DATA
	glm::vec2 greenSpawnPos{ 100,700 };

	//HUD DATA
};


