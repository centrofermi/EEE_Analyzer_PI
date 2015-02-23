#ifndef BOSS__E3OUTFILESUM__LIBGUARD
#define BOSS__E3OUTFILESUM__LIBGUARD


class E3OutFileSUM:public E3OutFileBase
{
public:
	E3OutFileSUM(void);
	~E3OutFileSUM(void);

	void WriteSummary();
};

#endif
