#ifndef _Hero_H_
#define _Hero_H_

class Hero : public Entity 
{
public:
    CLASS_IDENTIFICATION('HERO', Hero);
	CREATE_FUNC(Hero);

	void run();
	virtual bool init();
    virtual void WriteForCRC(OutputMemoryBitStream& inStream);
	int getID();
 
protected:
	virtual void onDead(int i,vector<Entity*> ETT_ptr);

};
#endif