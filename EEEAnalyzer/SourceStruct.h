#ifndef BOSS__SOURCESTRUCT__LIBGUARD
#define BOSS__SOURCESTRUCT__LIBGUARD
#include "intDef.h" 

typedef struct daq
{
    UInt_16b version;
	UInt_32b Head_begin;
	UInt_32b Head_end;
	char status[20];
	char name[128];
	char runTag[64];
	char dataPath[256];
    UInt_32b runNumber;
	UInt_16b fatalError;
	UInt_16b write;
	UInt_16b Globwrite;
	UInt_16b stopRq;
	UInt_16b resynch;
	UInt_64b StartTime;
	UInt_64b LastMonitor;	
	UInt_16b SysInfoLock;
	UInt_64b GlobMaxEvt;
	UInt_64b GlobEvtNum;
	UInt_32b EvtNum;
	UInt_32b runSize;
	FILE *NewFormatFile;
	FILE *BinStatusFile;
	FILE *BinDataFile;
	FILE *ArchFile;
	
} t_daq;

typedef struct header
{
	UInt_32b Head_begin;
    UInt_16b version;
    UInt_32b runNumber;
	char name[128];
	UInt_8b trigger;
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
