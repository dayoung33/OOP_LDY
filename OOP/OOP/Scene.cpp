#include "Scene.h"
#include "GameObject.h"
#include "PanelScript.h"
#include "RotateScript.h"
#include "MinimizeScript.h"
#include "RestoreScript.h"

Scene::Scene() {
}

Scene& Scene::getInstance() {
	static Scene instance;
	return instance;
}

void Scene::start() {
	auto mainPanel = GameObject::Instantiate("mainPanel", "panel", nullptr,
		Position{ 2, 2 }, "", Position{ 20, 20 });
	mainPanel->addComponent<PanelScript>();	
	auto mainPanelRestore = GameObject::Instantiate("mainRestore", "restore", nullptr,
		Position{ 50,20 }, "", Position{ 17, 2 });
	mainPanelRestore->addComponent<RestoreScript>();
	mainPanelRestore->getComponent<RestoreScript>()->setObject(mainPanel);
	auto mainPanelMinimaize = GameObject::Instantiate("mainMinimize", "minimize", mainPanel,
		Position{ 23, 1 }, "", Position{ 4, 2 });
	mainPanelMinimaize->addComponent<MinimizeScript>();
	mainPanelMinimaize->getComponent<MinimizeScript>()->setRestore(mainPanelRestore);

	auto movingBlock = GameObject::Instantiate("tetris block", "block", mainPanel,
		Position{ 4, 2 }, "\xdb \xdb \xdb\xdb", Position{ 2, 3 } );
	movingBlock->addComponent<RotateScript>();

	auto nextPanel = GameObject::Instantiate("nextPanel", "panel", nullptr,
		Position{ 30, 3 }, "", Position{ 10, 5 });
	nextPanel->addComponent<PanelScript>();
	auto nextPanelRestore = GameObject::Instantiate("nextRestore", "restore", nullptr,
		Position{ 50,18 }, "", Position{ 17, 2 });
	nextPanelRestore->addComponent<RestoreScript>();
	nextPanelRestore->getComponent<RestoreScript>()->setObject(nextPanel);
	auto nextPanelMinimaize = GameObject::Instantiate("nextMinimize", "minimize", nextPanel,
		Position{ 41, 2 }, "", Position{ 4, 2 });
	nextPanelMinimaize->addComponent<MinimizeScript>();
	nextPanelMinimaize->getComponent<MinimizeScript>()->setRestore(nextPanelRestore);


	auto staticBlock = GameObject::Instantiate("next block", "block", nextPanel,
		Position{ 35, 4 }, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3 } );

	auto scorePanel = GameObject::Instantiate("scorePanel", "panel", nullptr,
		Position{ 30, 15 }, "", Position{ 10, 4 });
	scorePanel->addComponent<PanelScript>();
	auto scorePanelRestore = GameObject::Instantiate("scoreRestore", "restore", nullptr,
		Position{ 50, 16 }, "", Position{ 17, 2 });
	scorePanelRestore->addComponent<RestoreScript>();
	scorePanelRestore->getComponent<RestoreScript>()->setObject(scorePanel);
	auto scorePanelMinimaize = GameObject::Instantiate("scoreMinimize", "minimize", scorePanel,
		Position{ 41, 14 }, "", Position{ 4, 2 });
	scorePanelMinimaize->addComponent<MinimizeScript>();
	scorePanelMinimaize->getComponent<MinimizeScript>()->setRestore(scorePanelRestore);

	for (auto gameObject : gameObjects) gameObject->internalStart();
}

void Scene::add(GameObject* go) {
	if (go == nullptr) return;
	gameObjects.push_back(go);
}

void Scene::remove(GameObject* go) {
	if (go == nullptr) return;
	for (auto it = gameObjects.begin(); it != gameObjects.end();)
	{
		auto obj = *it;
		if (obj == go) {
			it = gameObjects.erase(it);
			delete obj;
		}
		else			it++;
	}
}

void Scene::update() {
	for (auto gameObject : gameObjects) gameObject->internalUpdate();
}

void Scene::draw() {
	for (auto gameObject : gameObjects) gameObject->internalDraw();
}
