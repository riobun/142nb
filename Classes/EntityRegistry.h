//GameObjectRegistry����Ϸ����GameObject����
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

#ifndef _GAME_OBJECT_REGISTRY_H_
#define _GAME_OBJECT_REGISTRY_H_

typedef std::shared_ptr< Entity >(*EntityCreationFunc)();

class EntityRegistry
{
public:

	static void StaticInit();

	static std::unique_ptr< EntityRegistry >		sInstance;

    //ע��ÿ���࣬���������ܵ��ö�Ӧ��create����
	void RegisterCreationFunction( uint32_t inFourCCName, EntityCreationFunc inCreationFunction );

	EntityPtr CreateEntity( uint32_t inFourCCName );

private:

	EntityRegistry();

	unordered_map< uint32_t, EntityCreationFunc >	mNameToEntityCreationFunctionMap;

};
#endif //_GAME_OBJECT_TEGISTRY_H_