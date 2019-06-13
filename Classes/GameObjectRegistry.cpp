//GameObjectRegistry：游戏对象GameObject管理
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#include "GameHead.h"

std::unique_ptr< GameObjectRegistry >	GameObjectRegistry::sInstance = nullptr;

void GameObjectRegistry::StaticInit()
{
	sInstance.reset( new GameObjectRegistry() );
}

GameObjectRegistry::GameObjectRegistry()
{
}

void GameObjectRegistry::RegisterCreationFunction( uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction )
{
	mNameToGameObjectCreationFunctionMap[ inFourCCName ] = inCreationFunction;
}

EntityPtr GameObjectRegistry::CreateGameObject( uint32_t inFourCCName )
{
	//no error checking- if the name isn't there, exception!
	GameObjectCreationFunc creationFunc = mNameToGameObjectCreationFunctionMap[ inFourCCName ];

	EntityPtr gameObject = creationFunc();

	//should the registry depend on the world? this might be a little weird
	//perhaps you should ask the world to spawn things? for now it will be like this
	//World::sInstance->AddGameObject( gameObject );

	return gameObject;
}