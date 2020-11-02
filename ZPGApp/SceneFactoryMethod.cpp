#include "SceneFactoryMethod.h"

#include "SceneOne.h"
#include "SceneTwo.h"

Scene* SceneFactoryMethod::makeScene(int choice)
{
	switch (choice)
	{
	case 1:
		return new SceneOne();
		break;
	case 2:
		return new SceneTwo();
		break;
	default:
		return nullptr;
	}
}
