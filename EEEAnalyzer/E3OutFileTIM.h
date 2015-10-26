#ifndef BOSS__E3OUTFILETIM__LIBGUARD
#define BOSS__E3OUTFILETIM__LIBGUARD
#include "E3OutFileBase.h" 


class E3OutFileTIM:public E3OutFileBase
{
public:
	E3OutFileTIM(void);
	~E3OutFileTIM(void);

	void WriteHeader();
	void WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt);
};

#endif
