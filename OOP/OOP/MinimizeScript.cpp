#include "MinimizeScript.h"
#include "GameObject.h"
#include "RestoreScript.h"

MinimizeScript::MinimizeScript(GameObject * gameObjcet)
	:ClickableScript(gameObjcet)
{
}

void MinimizeScript::onClick()
{
	if (gameObject == nullptr) return;
	gameObject->setHiddenflag(true);

	//for (auto obj : restores) {
	//	auto restore = dynamic_cast<RestoreScript*>(obj);
	//	if (restore == nullptr) continue;
	//	if (restore->isMatching(gameObject)) {
	//		restore->show();
	//	}
	//}
}
