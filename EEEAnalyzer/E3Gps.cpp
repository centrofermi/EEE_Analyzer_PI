#include "stdafx.h"
#include "E3Gps.h"
#include <iostream>
#include "E3Track.h"


UInt_64b datetime2seconds(int year, int month, int day,
                           int hour = 0, int min = 0, int sec = 0)
{
  struct tm timestruct = { 0 };
  timestruct.tm_sec   = sec;
  timestruct.tm_min   = min;
  timestruct.tm_hour  = hour;
  timestruct.tm_mday  = day;
  timestruct.tm_mon   = month - 1;
  timestruct.tm_year  = year - 1900;
  timestruct.tm_isdst = -1;
  return mktime(&timestruct);
}

static const UInt_64b kTimeOffset = datetime2seconds(2007, 1, 1);


E3Gps::E3Gps(void):_gpsStruct(),_gpsE3Timestamp(0)
{
}

E3Gps::E3Gps(t_gps gps_s):_gpsStruct(gps_s),_gpsE3Timestamp(0)
{
	this->makeGpsTimestamp();
}


E3Gps::~E3Gps(void)
{
}

void E3Gps::setGpsStruct(t_gps gps_s)
{
	_gpsStruct=gps_s;
	this->makeGpsTimestamp();


}

//make timestamp to 2007.01.01
UInt_64b E3Gps::makeGpsTimestamp()
{
	//check if any gps struct has benn read
	if (_gpsStruct.UTCdate==0) 
	{
		std::cout<<"GPS not read or not valid"<<std::endl;
		return 0;
	}

	//recover time parameter (work with cast)
	
	int day = int(_gpsStruct.UTCdate)/10000;
	int month = (int(_gpsStruct.UTCdate) - day*10000)/100;
	int year = 2000 + int(_gpsStruct.UTCdate) - day*10000 - month*100;
	int hour = int(_gpsStruct.UTCtime)/10000;
	int min = (int(_gpsStruct.UTCtime) - hour*10000)/100;
	int sec = int(_gpsStruct.UTCtime) - hour*10000 - min*100;
	
	//make gps_timestamp for the run (remove offset from 1970 to 2007..)

	_gpsE3Timestamp = datetime2seconds(year, month, day, hour, min, sec) -  kTimeOffset;

	return _gpsE3Timestamp;
}

std::ostream&  E3Gps::writeGpsInfo(std::ostream& os)
{
	os<<"******************* GPS INFO *******************"<<std::endl<<std::endl;

	os 	<< "Quality		= " <<std::dec<< (int)_gpsStruct.quality<<std::endl
		<< "Satellite	= " << (UInt_32b)_gpsStruct.satellite<<std::endl
		<< "UTC Date	= " << _gpsStruct.UTCdate<<std::endl
		<< "UTC Time	= " << _gpsStruct.UTCtime <<std::endl
		<< "Latitude	= " << (UInt_32b)(_gpsStruct.latitude/100) + ((fmod(_gpsStruct.latitude,100)/60)) 
				<<"  "<<_gpsStruct.latHem<< std::endl
		<< "Longitude	= " << (UInt_32b)(_gpsStruct.longitude/100) + ((fmod(_gpsStruct.longitude,100)/60)) 
				<<"  "<<_gpsStruct.lonHem<< std::endl
		<< "Altitude	= " << (UInt_32b) _gpsStruct.altitude<<std::endl
		<< "EEE time	= " << _gpsE3Timestamp<<std::endl
	 	<< "GPGGA		= " << _gpsStruct.gpgga_str<<std::endl
		<< "GPRMC		= " << _gpsStruct.gprmc_str<<std::endl<<std::endl;

  return os;
}
