#include "Scene.h"
#include "GameObject.h"
#include "PanelScript.h"
#include "RotateScript.h"
#include "GridScript.h"
#include <algorithm>

Scene::Scene() {
}

Scene& Scene::getInstance() {
	static Scene instance;
	return instance;
}

void Scene::start() {
	auto mainPanel = GameObject::Instantiate("mainPanel", "panel", nullptr,
		Position{ 4, 3 }, "", Position{ 16, 16 });
	mainPanel->addComponent<GridScript>();

	auto nextPanel = GameObject::Instantiate("Time", "panel", nullptr,
		Position{ 30, 3 }, "", Position{ 10, 5 });
	nextPanel->addComponent<PanelScript>();

	auto scorePanel = GameObject::Instantiate("Mine", "panel", nullptr,
		Position{ 30, 15 }, "", Position{ 10, 4 });
	scorePanel->addComponent<PanelScript>();

	//auto found = GameObject::Find("block");				//block
	//auto found2 = GameObject::Find("/next/block");		//block
	//auto found3 = GameObject::Find("/next/block/block");//NULL
	//auto found4 = GameObject::Find("main");				//main
	//auto found5 = GameObject::Find("/main");			//main
	//auto found6 = GameObject::Find("/main/another");	//NULL
	//auto found7 = GameObject::Find("another");			//another
	//auto found8 = GameObject::Find("");					//NULL
	//
	//GameObject::Remove(found7);							//remove another

	//auto found10 = GameObject::Find("/next/another");	//NULL

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
