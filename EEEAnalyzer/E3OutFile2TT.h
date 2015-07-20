#ifndef BOSS__E3OUTFILE2TT__LIBGUARD
#define BOSS__E3OUTFILE2TT__LIBGUARD


class E3OutFile2TT:public E3OutFileBase
{
public:
	E3OutFile2TT(void);
	~E3OutFile2TT(void);

	void WriteHeader();
	void WriteEntry(UInt_32b runNumber, E3Gps Gps, E3RecoEvent evt);
};

#endif

