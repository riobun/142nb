#ifndef _Hero_H_
#define _Hero_H_

class Hero : public Entity 
{
public:
    CLASS_IDENTIFICATION('HERO', Hero);
	CREATE_FUNC(Hero);

	void run();
    //void Q();
	virtual bool init();
    virtual void WriteForCRC(OutputMemoryBitStream& inStream);
	int getID();
 
protected:
	virtual void onDead(int i,vector<Entity*> ETT_ptr);
	virtual void mHero_onDead(int i, vector<Entity*> ETT_ptr);

};
#endif