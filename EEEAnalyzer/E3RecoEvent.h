#ifndef BOSS__E3RECOEVENT__LIBGUARD
#define BOSS__E3RECOEVENT__LIBGUARD


typedef std::vector<std::pair<double, double>>  corr_vector;
typedef std::vector<corr_vector>  corr_matrix;

class E3RecoEvent:public E3Event, public E3Gps
{


public:


	E3RecoEvent(void);
	~E3RecoEvent(void);
	void clear();

	
	//get calibration costant
	void importCalibration(corr_matrix matrix)  {_corrMatrix=matrix;};

	 /// \brief Return the number of hits in a given plane.
	UInt_16b numHits(UInt_16b plane);
	/// \brief Return the total number of hits.
	UInt_16b numHits() ;
	
	/// \brief Return the hit vector.
	E3HitVec getHits(UInt_16b plane)	{return _hitVec[plane];};
	

	/// \brief Return the number of clusters in a given plane.
	UInt_16b numClusters(UInt_16b plane) ;
	 /// \brief Return the total number of clusters.
	UInt_16b numClusters() ;

	
	/// \brief Return the number of tracks.
	UInt_16b numTracks();
	/// \brief Return the number of tracks with chi2 below CHI2THR constant.
	UInt_16b numGoodTracks();

	/// \brief Return the best track if it exists, a dummy "empty" track
	/// otherwise.
	E3Track bestTrack();


	//base event reconstruction function
	UInt_16b reconstruct();

	// find hits in the event
	UInt_16b findHits();

private:

	
	//time correction matrix(Ps)
	corr_matrix _corrMatrix;


	// find clusters in the event
	UInt_16b findClusters();

	// find tracs in the event
	UInt_16b findTracks();

	/// \brief The vector of hits.
	E3HitVec _hitVec[3];

	/// \brief The vector of clusters.
	E3ClusterVec _clusterVec[3];

	/// \brief The vector of reconstructed tracks.
	E3TrackVec _trackVec;
};

#endif
