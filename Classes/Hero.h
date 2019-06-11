#ifndef _Hero_H_
#define _Hero_H_

class Hero : public Entity 
{
public:
    CLASS_IDENTIFICATION('HERO', Hero);
	CREATE_FUNC(Hero);

	virtual bool init();
    virtual void WriteForCRC(OutputMemoryBitStream& inStream);
	int getID();
 

};
#endif