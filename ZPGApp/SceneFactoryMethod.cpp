#include "SceneFactoryMethod.h"

#include "SceneOne.h"
#include "SceneTwo.h"
#include "SceneThree.h"

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
	case 3:
		return new SceneThree();
		break;
	default:
		return nullptr;
	}
}
