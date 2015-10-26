#ifndef BOSS__E3OUTFILEDEB__LIBGUARD
#define BOSS__E3OUTFILEDEB__LIBGUARD
#include "E3OutFileBase.h" 


class E3OutFileDEB:public E3OutFileBase
{
public:
	E3OutFileDEB(void);
	~E3OutFileDEB(void);

	void WriteHeader();
	void WriteEntry(E3RecoEvent evt);
};

#endif
