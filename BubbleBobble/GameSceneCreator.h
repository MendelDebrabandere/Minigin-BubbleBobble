#pragma once
namespace dae
{
	class GameObject;
	class Scene;
	class Minigin;
}

class GameSceneCreator final
{
public:
	static void CreateGameScene(dae::Scene* pGameScene);
};
