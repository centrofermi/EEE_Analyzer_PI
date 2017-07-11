#ifndef BOSS__E3EVENT__LIBGUARD
#define BOSS__E3EVENT__LIBGUARD
#include "E3StripData.h"
#include "intDef.h"
#include "E3RawData.h"
#include <iostream>
#include <vector>



class E3Event
{

protected:

	E3RawDataVec						_rawDataVec;

	//basic event info
	UInt_32b	_orbit;
	UInt_32b	_sec;
	UInt_32b	_bunch;
	UInt_32b	_evtNum;
	UInt_32b	_trgNum;
	UInt_32b	_calib;
	UInt_32b	_ninoMap;
	double      _planeDist[3];
	double	    _cableLenght[6];
	UInt_8b     _fecType[6];

	//gps Info
	UInt_32b	_gpsTimestamp;
	//vector of strip data. one for each plane
    E3StripDataVec m_stripDataVec[3];

public:

	E3Event(void);
	~E3Event(void);
	void clear(void);

	
	// retrive general event infos
	inline UInt_32b getEvtNum()			{return _evtNum;}
	inline UInt_32b getEvtSec()			{return _sec;}
	inline UInt_32b getEvtOrbit()		{return _orbit;}
	inline UInt_32b getEvtBunch()		{return _bunch;}
	inline UInt_32b getEvtCal()			{return _calib;}
	inline UInt_32b getTrgNum()			{return _trgNum;}

	E3StripDataVec GetStripDataVec(int chamber) {return m_stripDataVec[chamber];}

	//set gps timestamp for event(sec since 1.1.207)
	inline void setGpsTimestamp(UInt_64b GpsTime)	{_gpsTimestamp=GpsTime;};
	//set arch connection map
	inline void		setNinoMap(UInt_32b NinoMap)		{_ninoMap=NinoMap;}
	inline void     setPlaneDist(double* planeDist)    { memcpy(_planeDist, planeDist, 3 * sizeof(double));};
	inline void     setCableDelay(double* cableLength) {memcpy(_cableLenght,cableLength, 3 * sizeof(double));};
	inline void     setFecType(UInt_8b* fecType) {memcpy(_fecType,fecType, 6 * sizeof(UInt_8b));};

	//add raw data to vector
	inline void addRawData(E3RawData rawData)	{_rawDataVec.push_back(rawData);};

	// Add strip data to the m_stripDataVec class member
    void addStripData(UInt_16b plane, E3StripData data);  
	/// \brief Return the number of strip data for a given plane.
	UInt_16b numStripData(UInt_16b plane);
	/// \brief Return the total number of strip data in the event.
	UInt_16b numStripData();

	inline E3StripDataVec getStripDataVector(UInt_16b plane)  {return m_stripDataVec[plane];};

	UInt_16b unpack();



};

/// \brief Temporary ad-hoc container to map the digi words within an event
/// into a representation that can be easily used to build up the E3StripData
/// structures.
/// 
/// Here we are effectively creating a structure that in python would look
/// something like:
/// digiMap[(plane, channel)] = [side, digiWord]

typedef std::pair<UInt_16b, UInt_16b> E3RawMapKey;

typedef std::vector< std::pair<UInt_16b, E3RawData> > E3RawMapValue;

typedef E3RawMapValue::iterator E3RawMapValueIter;

typedef std::map<E3RawMapKey, E3RawMapValue> E3RawMap;

typedef E3RawMap::iterator E3RawMapIter;

#endif
