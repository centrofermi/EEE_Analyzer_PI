#ifndef BOSS__E3OUTFILEOUT__LIBGUARD
#define BOSS__E3OUTFILEOUT__LIBGUARD
#include "E3OutFileBase.h" 


class E3OutFileOUT:public E3OutFileBase
{
public:
	E3OutFileOUT(void);
	~E3OutFileOUT(void);

	void WriteHeader();
	void WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt);
};

#endif
