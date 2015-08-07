#ifndef BOSS__E3CALIB__LIBGUARD
#define BOSS__E3CALIB__LIBGUARD




typedef std::vector<TH1D>  histo_vector;
typedef std::vector<histo_vector>  histo_matrix;


typedef std::vector<double>  mean_vector;
typedef std::vector<mean_vector>  mean_matrix;


class E3Calib:public E3RecoEvent
{

private:
	
	//Histo matrix
	histo_matrix _rawYMatrix;
	histo_matrix _rawTMatrix;
	
	//Mean matrix
	mean_matrix _meanYMatrix;
	mean_matrix _meanTMatrix;

	//Correction matrix
	corr_matrix _corrMatrix;


	//in file
	std::ifstream _sourceStream;

	//out file
	E3OutFileCAL	_calFile;
	TFile*			_rootFile;
	t_header		_headerStruct;
	t_gps			_gpsStruct;

	bool			_debug;


	//Create output files
	StatusCode createOutFiles(std::string OutDir);
	//close output files
	void closeOutFiles();
	//get event from source file
	UInt_16b getEvent();
	//retrive mean value from calibration histograms
	void getMean();
	//fill histograms with event data
	void fillHisto();
	// initilaize histogram matrix
	void initHisto();

	//compute calibration
	void computeCorrections();



public:
	E3Calib(void);
	E3Calib(bool debug);
	~E3Calib(void);

	corr_matrix runCalibration(std::string Source,std::string OutDir,bool debug=true);
};

#endif
