#ifndef BOSS__E3OUTFILEDEB__LIBGUARD
#define BOSS__E3OUTFILEDEB__LIBGUARD


class E3OutFileDEB:public E3OutFileBase
{
public:
	E3OutFileDEB(void);
	~E3OutFileDEB(void);

	void WriteHeader();
	void WriteEntry(E3RecoEvent evt);
};

#endif