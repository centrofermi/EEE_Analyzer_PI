#ifndef BOSS__E3GPS__LIBGUARD
#define BOSS__E3GPS__LIBGUARD


class E3Gps
{

private:

	t_gps		_gpsStruct;
	UInt_64b	_gpsE3Timestamp;
	
	UInt_64b			makeGpsTimestamp();


public:
	E3Gps(void);
	E3Gps(t_gps gps_s);
	~E3Gps(void);

	//gps inline

	inline UInt_64b		getGpsE3Timestamp()						{return _gpsE3Timestamp;};
	inline t_gps		getGpsStruct()							{return _gpsStruct;};
	
	//gps function
	void				setGpsStruct(t_gps gps_s);	
	std::ostream& 		writeGpsInfo(std::ostream& os);
};

#endif