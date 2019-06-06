//GameObjectRegistry����Ϸ����GameObject����
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

typedef GameObjectPtr ( *GameObjectCreationFunc )();

class GameObjectRegistry
{
public:

	static void StaticInit();

	static std::unique_ptr< GameObjectRegistry >		sInstance;

    //ע��ÿ���࣬���������ܵ��ö�Ӧ��create����
	void RegisterCreationFunction( uint32_t inFourCCName, GameObjectCreationFunc inCreationFunction );

	GameObjectPtr CreateGameObject( uint32_t inFourCCName );

private:

	GameObjectRegistry();

	unordered_map< uint32_t, GameObjectCreationFunc >	mNameToGameObjectCreationFunctionMap;

};
