#ifndef BOSS__E3CALIB__LIBGUARD
#define BOSS__E3CALIB__LIBGUARD
#include "TGraph.h"
#include "E3RecoEvent.h"
#include "E3StatusCode.h"



typedef std::vector<TGraph>  graph_vector;

typedef std::vector<TH1D>  histo_vector;
typedef std::vector<histo_vector>  histo_matrix;


typedef std::vector<double>  mean_vector;
typedef std::vector<mean_vector>  mean_matrix;


class E3Calib:public E3RecoEvent
{

private:
	//variable for the RawHits Tree
	
	TTree  _rawHitsTree;

	uint32_t _rawHit_plane;
	uint32_t _rawHit_strip;
	uint64_t _rawHit_time;
	uint32_t _rawHit_side;
	uint32_t _rawHit_edge;

	//variable for the hits tree

	TTree  _hitsTree;
	
	uint32_t  _hits_sec;
	uint32_t  _hits_ns;
	uint32_t  _hits_en;
	double  _hits_x;
	double  _hits_y;
	double  _hits_z;
	double  _hits_THit;
	double  _hits_TOT_l;
	double  _hits_TOT_r;

	//Histo matrix
	histo_matrix _rawYMatrix;
	histo_matrix _rawTMatrix;

	graph_vector _YTrend;
	graph_vector _TTrend;

	
	//Mean matrix
	mean_matrix _meanYMatrix;
	mean_matrix _meanTMatrix;

	//Correction matrix
	corr_matrix _corrMatrix;


	//in file
	std::ifstream _sourceStream;

	//out file
	TFile*			_rootFile;
	t_header		_headerStruct;
	t_gps			_gpsStruct;
	t_arch			_archStruct;
	t_ws			_wsStruct;

	bool			_debug;


	//Create output files
	StatusCode createOutFile(std::string OutDir);
	//close output files
	void closeOutFile();
	//get event from source file
	UInt_16b getEvent();
	//retrive mean value from calibration histograms
	void getMean();
	//fill histograms an tree with event data
	void fill();
	// initilaize histogram matrix and tree
	void init();

	//compute calibration
	void computeCorrections();



public:
	E3Calib(void);
	E3Calib(bool debug);
	~E3Calib(void);

	corr_matrix runCalibration(std::string Source,std::string OutDir,bool debug=true);
};

#endif

