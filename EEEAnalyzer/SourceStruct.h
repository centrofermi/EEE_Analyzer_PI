#ifndef BOSS__SOURCESTRUCT__LIBGUARD
#define BOSS__SOURCESTRUCT__LIBGUARD

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
	UInt_32b	hH,hT;        //header header and trailer
	UInt_16b	hVersion;		//DAQ Version
	UInt_64b	hStartTime;    //DAQ PC unix timestamp of run start
	UInt_8b		hTrgMask;		//trigger mask
	UInt_16b	hRunNameL;		//run name byte lenght
	char		hRunName[128];	//run name
	UInt_8b		hMachineID;	//identifier of the telescope ID
	UInt_32b	hRunNumber;	//proggressive run number for the telescope
	UInt_32b	hNinoMap;		//nino map
	
} t_header;

typedef struct gps
{
	char 		gpgga_str[128];
	char 		gprmc_str[128];
	UInt_8b  	quality;
	double 		UTCdate;
	double		UTCtime;
	double 		latitude;
	double		longitude;
	char 		latHem;
	char		lonHem;
} t_gps;






#endif