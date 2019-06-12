//GameObjectRegistry：游戏对象GameObject管理
//  参考：Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  更改：杜玫， 2019.06.05

#ifndef _GAME_OBJECT_REGISTRY_H_
#define _GAME_OBJECT_REGISTRY_H_

typedef std::shared_ptr< Entity >(*EntityCreationFunc)();

class EntityRegistry
{
public:

	static void StaticInit();

	static std::unique_ptr< EntityRegistry >		sInstance;

    //注册每个类，给类名就能调用对应的create函数
	void RegisterCreationFunction( uint32_t inFourCCName, EntityCreationFunc inCreationFunction );

	EntityPtr CreateEntity( uint32_t inFourCCName );

private:

	EntityRegistry();

	unordered_map< uint32_t, EntityCreationFunc >	mNameToEntityCreationFunctionMap;

};
#endif //_GAME_OBJECT_TEGISTRY_H_