#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Screen.h"
#include "Scene.h"
#include "InputManager.h"
#include <algorithm>

map<string, vector<GameObject *>> GameObject::objects;

void GameObject::Add(GameObject* obj)
{
	if (!obj) return;

	auto it = objects.find(obj->name);
	if (it == objects.cend())
		objects[obj->name] = vector<GameObject *>();

	auto& entry = objects[obj->name];
	auto found = find_if(entry.cbegin(), entry.cend(), 
		[&](auto item) { return item->absolutePath == obj->absolutePath; } );

	if (found != entry.cend()) return;
	entry.push_back(obj);
}

void GameObject::Remove(GameObject* obj)
{
	if (obj == nullptr) return;

	try {
		auto& entry = objects[obj->name]; // NOTE: entry should not be copied from map.

		auto result = find(entry.cbegin(), entry.cend(), obj);
		if (result == entry.cend()) return;		
		
		entry.erase(result);
		
	}
	catch (int exception)
	{
		exception = 0;
	}
}

GameObject* GameObject::Find(const string& path)
{
	if (objects.empty()) return nullptr;

	// extract name part from path or from name
	string nameOnly = path;
	auto idx = path.find_last_of('/');	//만일 문자가 존재할 경우 그 위치를 리턴하고, 없다면 npos 를 리턴
	if (idx != string::npos)			
		nameOnly = path.substr(idx + 1); //뒤에서 부터 idx+1개 문자 출력 그러니까 맨뒤 / 전까지 
										 // /next/block 이면 nameOnly == block
	
	auto found = objects.find(nameOnly); //map에서 key값으로 value찾기
	if (found == objects.end()) return nullptr;
	auto& entry = found->second; 

	// if search by name only with no absolute path
	if (nameOnly == path) 
		return entry.size() > 0 ? entry[0] : nullptr;

	// search by absolute path
	auto result = find_if(entry.cbegin(), entry.cend(), [&](auto item) { return item->absolutePath == path; });
	return result != entry.cend() ? *result : nullptr;
}

void GameObject::internalStart() {
	for (auto component : components) component->start();
	for (auto child : children) child->internalStart();
}

void GameObject::internalUpdate() {
	for (auto component : components) component->update();
	for (auto child : children) child->internalUpdate();
	
	children.erase(remove_if(children.begin(), children.end(), [&](auto item) {
		if (item->isRequestingDestruction() == false) return false;
		GameObject::Remove(item);
		delete item;
		return true;
	}), children.end());
}


void GameObject::internalDraw() {
	for (auto component : components) component->draw();
	for (auto child : children) child->internalDraw();
}

GameObject* GameObject::Instantiate(const string& name, const string& tag, GameObject* parent, 
	const Position& pos, const string& shape, const Position& size )
{
	auto gameObject = new GameObject(name, tag, parent);
	gameObject->transform->setPosition(pos);
	gameObject->transform->setShape(shape);
	gameObject->transform->setSize(size);

	if (parent == nullptr) Scene::getInstance().add(gameObject);
	else parent->add(gameObject);

	GameObject::Add(gameObject);

	return gameObject;
}

void GameObject::Destroy(GameObject* obj)
{
	if (obj == nullptr) return;

	obj->setDestruction();
}

GameObject::GameObject(const string& name, 
	const string& tag,
	GameObject* parent)
	: name(name), tag(tag), parent(parent), 
	requestDestruction(false),
	hideFlag(false), 
	transform(nullptr),
	absolutePath( parent == nullptr ? "/" + name : parent->absolutePath + "/" + name),
	screen(Screen::getInstance()),
	scene(Scene::getInstance()),

	inputManager(InputManager::getInstance())
{	
	transform = getOrAddComponent<Transform>();
}

GameObject::~GameObject() {}

