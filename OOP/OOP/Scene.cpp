#include "Scene.h"
#include "GameObject.h"
#include "PanelScript.h"
#include "RotateScript.h"
#include "GridScript.h"
#include "mineScript.h"
#include "TimeScript.h"
#include "EndingScript.h"
#include "RestartScript.h"
#include "ExitScript.h"
#include <algorithm>

Scene::Scene() {
}

Scene& Scene::getInstance() {
	static Scene instance;
	return instance;
}

void Scene::start() {
	auto mainPanel = GameObject::Instantiate("Grid", "panel", nullptr,
		Position{ 0, 0 }, "", Position{ 16, 16 });
	mainPanel->addComponent<GridScript>();

	auto timePanel = GameObject::Instantiate("Time", "panel", nullptr,
		Position{ 18, 2 }, "", Position{ 10, 5 });
	timePanel->addComponent<PanelScript>();
	auto timeText = GameObject::Instantiate("timeText", "time", timePanel,
		Position{ 20, 4 }, "0.0", Position{ 10, 4 });
	timeText->addComponent<TimeScript>();

	auto minePanel = GameObject::Instantiate("Mine", "panel", nullptr,
		Position{ 18, 10 }, "", Position{ 10, 4 });
	minePanel->addComponent<PanelScript>();
	auto mineText = GameObject::Instantiate("MineText", "mine", minePanel,
		Position{ 20, 12 }, "0", Position{ 10, 4 });
	mineText->addComponent<mineScript>();

	auto endPanel = GameObject::Instantiate("Ending", "panel", nullptr,
		Position{ 1, 18 }, "", Position{ 27, 5 });
	endPanel->addComponent<EndingScript>();
	auto restartbutton = GameObject::Instantiate("Restart", "button", endPanel,
		Position{ 4, 20 }, "", Position{ 8, 2 });
	restartbutton->addComponent<RestartScript>();
	auto exittbutton = GameObject::Instantiate("Exit", "button", endPanel,
		Position{ 17, 20 }, "", Position{ 8, 2 });
	exittbutton->addComponent<ExitScript>();

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

	// erase remove idiom
	gameObjects.erase( remove_if(gameObjects.begin(), gameObjects.end(),
		[&](auto item) { if (item->isRequestingDestruction() == false) return false;
				GameObject::Remove(item);
				delete item;				
				return true;
		} ),
		gameObjects.cend());
}

void Scene::draw() {
	for (auto gameObject : gameObjects) gameObject->internalDraw();
}
