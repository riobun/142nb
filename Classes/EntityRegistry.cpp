//GameObjectRegistry：游戏对象GameObject管理
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#include "GameHead.h"

std::unique_ptr< EntityRegistry >	EntityRegistry::sInstance = nullptr;

void EntityRegistry::StaticInit()
{
	sInstance.reset( new EntityRegistry() );

}

EntityRegistry::EntityRegistry()
{
}

void EntityRegistry::RegisterCreationFunction( uint32_t inFourCCName, EntityCreationFunc inCreationFunction )
{
	mNameToEntityCreationFunctionMap[ inFourCCName ] = inCreationFunction;
}

EntityPtr EntityRegistry::CreateEntity( uint32_t inFourCCName )
{
	//no error checking- if the name isn't there, exception!
	EntityCreationFunc creationFunc = mNameToEntityCreationFunctionMap[ inFourCCName ];

	EntityPtr gameObject = creationFunc();

	//should the registry depend on the world? this might be a little weird
	//perhaps you should ask the world to spawn things? for now it will be like this
	//World::sInstance->AddGameObject( gameObject );

	return gameObject;
}