#ifndef BOSS__E3RUN__LIBGUARD
#define BOSS__E3RUN__LIBGUARD

class E3Run:public E3RecoEvent
{


private:

	//in file
	std::ifstream _sourceStream;

	//out file
	E3OutFileOUT  _outFile;
	E3OutFileSUM  _sumFile2;
	E3OutFileTIM  _timFile;
	E3OutFile2TT  _2ttFile;


	std::ofstream _sumFile;

	//run header info
	
	t_header _headerStruct;
	t_gps	 _gpsStruct;
	t_arch   _archStruct;
	t_ws	 _wsStruct;

	//run sum
	UInt_32b _analyzed;										//events correctly analyzed
	bool _headerParsed;
	UInt_32b _fileLength;

	std::vector<std::vector<UInt_32b> >  _gHitMult;	//hits multiplicity for each chamber
	std::vector<UInt_32b>  _gSumHitMult;				//hits multiplicity for each event
	UInt_32b	_gLowHitMult;							//events with AT LEAST one empty chamber
	UInt_32b	_gMediumHitMult;						//events with 1 or 2 hit/chamber
	UInt_32b	_gHighHitMult;							//events with at least one chamber with hit multiplicity > 2

	std::vector<std::vector<UInt_32b> >  _gClusterMult;		//cluster multiplicity for each chamber
	std::vector<UInt_32b>  _gSumClusterMult;				//cluster multiplicity for each event
	UInt_32b	_gLowClusterMult;							//events with AT LEAST one empty chamber
	UInt_32b	_gMediumClusterMult;						//events with 1 or 2 cluster/chamber
	UInt_32b	_gHighClusterMult;							//events with at least one chamber with cluster multiplicity > 2
	
	StatusCode createOutFile(std::string OutDir);
	UInt_16b getEvent();
	void getMultiplicity();


public:
	E3Run(void);
	~E3Run(void);

	//analyze run
	void analyzeRun(std::string Source,std::string OutDir);
	//open file and get header information
	void open(std::string Source,std::string Option="");
	//scan next event in file (if header already parsed)
	UInt_16b analyzeEvent();
	//close input file
	void	close();


	inline t_header getHeaderStruct()	{return _headerStruct;};
	inline t_arch   getArchStruct()     {return _archStruct;};
	inline t_ws		getWsStruct()	    {return _wsStruct;};


	//write info
	std::ostream&	writeRunSum(std::ostream& os=std::cout);
	std::ostream&	writeHeaderInfo(std::ostream& os=std::cout);
	std::ostream&	writeArchInfo(std::ostream& os=std::cout);
	std::ostream&	writeWsInfo(std::ostream& os=std::cout);
};

#endif