#ifndef BOSS__E3RECOEVENT__LIBGUARD
#define BOSS__E3RECOEVENT__LIBGUARD


class E3RecoEvent:public E3Event, public E3Gps
{


public:


	E3RecoEvent(void);
	~E3RecoEvent(void);
	void clear();

	


	 /// \brief Return the number of hits in a given plane.
	UInt_16b numHits(UInt_16b plane);
	/// \brief Return the total number of hits.
	UInt_16b numHits() ;
	

	/// \brief Return the number of clusters in a given plane.
	UInt_16b numClusters(UInt_16b plane) ;
	 /// \brief Return the total number of clusters.
	UInt_16b numClusters() ;

	
	/// \brief Return the number of tracks.
	UInt_16b numTracks();
	/// \brief Return the best track if it exists, a dummy "empty" track
	/// otherwise.
	E3Track bestTrack();


	//base event reconstruction function
	UInt_16b reconstruct();

private:

	// find hits in the event
	UInt_16b findHits();

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
