#ifndef BOSS__SOURCESTRUCT__LIBGUARD
#define BOSS__SOURCESTRUCT__LIBGUARD
#include "intDef.h" 


typedef struct header
{
	UInt_32b Head_begin;
    UInt_16b version;
    UInt_32b runNumber;
	char name[128];
	UInt_64b StartTime;
	UInt_32b Head_end;
	
} t_header;

typedef struct gps
{
	char 		gpgga_str[128];
	char 		gprmc_str[128];
	UInt_8b  	quality;
	UInt_8b  	satellite;
	double		UTCdate;
	double		UTCtime;
	double		latitude;
	double		longitude;
	double		altitude;
	char 		latHem;
	char		lonHem;
	UInt_64b	pps_latency;  //ns
} t_gps;

typedef struct ws
{
	UInt_32b byte;
	UInt_32b id;
	UInt_32b year;
	UInt_32b month;
	UInt_32b day;
	UInt_32b hours;
	UInt_32b minute;
	UInt_32b inTemp;
	UInt_32b outTemp;
	UInt_32b pressure;
} t_ws;


typedef struct arch
{
	double planeDist[3];	
	UInt_16b trg_type;
	UInt_64b trg_latency;	
	UInt_32b match_window;
	UInt_32b search_window;	
	UInt_32b window_offset;	
	UInt_32b reject_offset;	
	UInt_32b detection_mode; //0 leading, 1 leading&trailing, 2 pairing
	UInt_32b resolution;     // ps
	UInt_8b machineID;
	UInt_32b NINO_map;
	UInt_8b Board_plug;
	double planeThick;
	double orientation;
	double sigSpeed;
	double stripPitch;
	double stripLength;
	double cableLength[6];	
	UInt_8b fecType[6];
	
} t_arch;

#endif
