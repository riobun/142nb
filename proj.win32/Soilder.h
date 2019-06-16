#ifndef _Soilder_H_
#define _Soilder_H_

class Soilder : public Entity
{
public:
	CLASS_IDENTIFICATION('SOIL', Soilder);
	CREATE_FUNC(Soilder);

	//void run();
	//void Q();
	virtual bool init();
	virtual void WriteForCRC(OutputMemoryBitStream& inStream);
	int getID();
protected:
	virtual void onDead(int i);

};
#endif