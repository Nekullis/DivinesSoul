#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	_mEntity = new MapEntity();
}

ObjectManager::~ObjectManager() {
	delete _mEntity;
}

void ObjectManager::Initialize(stage global) {

	_mEntity->Initialize(global);

}

void ObjectManager::Process() {

}

void ObjectManager::Render() {

	_mEntity->Render();

}
