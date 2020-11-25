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
	mainPanel->addComponent<MinimizeScript>();
	mainPanel->addComponent<RestoreScript>();

	auto movingBlock = GameObject::Instantiate("tetris block", "block", mainPanel,
		Position{ 4, 2 }, "\xdb \xdb \xdb\xdb", Position{ 2, 3 } );
	movingBlock->addComponent<RotateScript>();

	auto nextPanel = GameObject::Instantiate("nextPanel", "panel", nullptr,
		Position{ 30, 3 }, "", Position{ 10, 5 });
	nextPanel->addComponent<PanelScript>();
	nextPanel->addComponent<MinimizeScript>();

	auto staticBlock = GameObject::Instantiate("next block", "block", nextPanel,
		Position{ 35, 4 }, "\xdb  \xdb\xdb\xdb  \xdb", Position{ 3, 3 } );

	auto scorePanel = GameObject::Instantiate("scorePanel", "panel", nullptr,
		Position{ 30, 15 }, "", Position{ 10, 4 });
	scorePanel->addComponent<PanelScript>();
	scorePanel->addComponent<MinimizeScript>();

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
