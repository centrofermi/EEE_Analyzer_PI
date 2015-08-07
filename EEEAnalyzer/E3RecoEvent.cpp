#include "stdafx.h"




E3RecoEvent::E3RecoEvent(void):_corrMatrix(3,corr_vector(24,std::make_pair(0,0)))
{
	clear();
}


E3RecoEvent::~E3RecoEvent(void)
{
}

void E3RecoEvent::clear()
{
  E3Event::clear();
  for (UInt_32b plane = 0; plane < 3; plane++) {
    _hitVec[plane].clear();
    _clusterVec[plane].clear();
  }
  _trackVec.clear();

}


UInt_16b E3RecoEvent::findHits()
{
	//to be fixed CONFIGURATION FILE
	UInt_32b cableDelay[3][2]={{0,0},{4250,0},{0,0}};

			double planeDist[3]={149,96,43};



  // Initialize some variables.
  E3StripDataVecIter stripData;
  E3RawDataVecIter posEdge, negEdge;
  E3RawDataVec posVec, negVec;
  int32_t posPs, negPs;
  int32_t dPs;
  double x, y, z, t;
  double tot[2];

  // Loop over the telescope planes...
  for (UInt_16b plane = 0; plane < 3; plane++) {
    // Loop over the full strip data in the plane... 
    for (stripData = m_stripDataVec[plane].begin();
         stripData != m_stripDataVec[plane].end(); stripData++) {
      // Double loop over the edges on the two plane end for the strip data.
      posVec = stripData->posEdgeDigiVec();
      negVec = stripData->negEdgeDigiVec();
      for (posEdge = posVec.begin(); posEdge != posVec.end(); posEdge++){
        for (negEdge = negVec.begin(); negEdge != negVec.end(); negEdge++){
          if (posEdge->isRisingEdge() && negEdge->isRisingEdge()) {
            // At this point we're testing all the possible pairs of rising
            // edges on the opposite end of each strip with data.
            // 
            // Correct the timing of the rising edges so that the difference
            // in the cable length is compensated for.
			  posPs = (posEdge->getPs()) + cableDelay[plane][0] + _corrMatrix[plane][stripData->channel()].second;
			negPs = (negEdge->getPs()) + cableDelay[plane][1]+ _corrMatrix[plane][stripData->channel()].first;
            // Calculate the time difference of the rising edges and
            // convert it into the coordinate along the strip.
            dPs = posPs - negPs;
            y = ((double)dPs)*0.5*PROP_SPEED/1000.0;

            // Is the y coordinate within the physical range?
			if (abs(dPs) < DPSMAX) 
			{
				x = (stripData->channel() - XOFFSET)*STRIP_PITCH;
				z = planeDist[plane];
				t = 0.001*(posPs + negPs)/2.;
				// Calculate the TOT (this is done between pairs in the same
				// plane ends so that the cable length is irrelevant).
				if ((posEdge + 1)->isFallingEdge()) {
				  tot[0] = 0.001*((posEdge + 1)->getPs() - posEdge->getPs());
				} else {
				  tot[0] = -1;
				}
				if ((negEdge + 1)->isFallingEdge()) {
				  tot[1] = 0.001*((negEdge + 1)->getPs() - negEdge->getPs());
				} else {
				  tot[1] = -1;
				}
				E3Hit hit(stripData->plane(), stripData->channel(), x, y, z, t,
                        tot);
				/*std::cout<<"EVENT "<<_evtNum<<std::endl;
				hit.fillStream(std::cout);
				std::cout<<std::endl;*/
				_hitVec[plane].push_back(hit);

			}
          }
        }
      }
    }
  }
  return 0;
}

UInt_16b E3RecoEvent::numHits(UInt_16b plane)
{
  return _hitVec[plane].size();
}


UInt_16b E3RecoEvent::numHits()
{
  unsigned short n = 0;
  for (UInt_16b plane = 0; plane < 3; plane++) {
    n += numHits(plane);
  }
  return n;
}

UInt_16b E3RecoEvent::findClusters()
{

	E3HitVecIter hit, hitBegin, hitEnd;		//create iterator to hit vector
	E3ClusterVecIter	cluster;
	for (UInt_16b plane = 0; plane < 3; plane++) //loop on planes
	{  
		hitBegin = _hitVec[plane].begin();
		hitEnd = _hitVec[plane].end();

		for (hit=hitBegin; hit != hitEnd; hit++) //loop on the hits of the plane
		{
			bool newCluster=true;
			for(cluster=_clusterVec[plane].begin();cluster!=_clusterVec[plane].end();cluster++) //loop sui cluster già creati
			{
				if(close(*cluster,*hit))
				{
					cluster->addHit(*hit);
					newCluster=false;
					break;
				}
			}
			if(newCluster)
			{
				_clusterVec[plane].push_back(E3Cluster(plane));
				_clusterVec[plane].back().addHit(*hit);
			}
		}
		/*std::cout<<"EVENT NUMBER"<< _evtNum<<std::endl;
			for(cluster=_clusterVec[plane].begin();cluster!=_clusterVec[plane].end();cluster++) //loop sui cluster già creati
			{
				cluster->fillStream(std::cout);
				std::cout<<std::endl;
			}*/

	}
	return 0;

}

UInt_16b E3RecoEvent::numClusters(UInt_16b plane) 
{
  return _clusterVec[plane].size();
}


UInt_16b E3RecoEvent::numClusters() 
{
  unsigned short n = 0;
  for (UInt_16b plane = 0; plane < 3; plane++) {
    n += numClusters(plane);
  }
  return n;
}


UInt_16b E3RecoEvent::findTracks()
{
	
	E3FittingTool fitTool;
	E3ClusterVecIter topCluster, topBegin, topEnd, midCluster, midBegin, midEnd,
	  botCluster, botBegin, botEnd;														//create cluster iterator

	topBegin = _clusterVec[kTopPlane].begin();
	topEnd = _clusterVec[kTopPlane].end();
	midBegin = _clusterVec[kMidPlane].begin();
	midEnd = _clusterVec[kMidPlane].end();
	botBegin = _clusterVec[kBotPlane].begin();
	botEnd = _clusterVec[kBotPlane].end();

	
	for (topCluster = topBegin; topCluster != topEnd; topCluster ++) 
	{
	  for (midCluster = midBegin; midCluster != midEnd; midCluster ++) 
	  {
	    for (botCluster = botBegin; botCluster != botEnd; botCluster ++) //loop on all clusters triplets
		{
			E3PointVec pointVec;
			pointVec.push_back((E3Point)*topCluster);  //bello questo cast tra class ereditate!
			pointVec.push_back((E3Point)*midCluster);
			pointVec.push_back((E3Point)*botCluster);
			fitTool.run(pointVec);
			E3Track track = fitTool.track();
			track.setCluster(kTopPlane, *topCluster);
			track.setCluster(kMidPlane, *midCluster);
			track.setCluster(kBotPlane, *botCluster);
			_trackVec.push_back(track);
	    }
	  }
	}
	std::sort(_trackVec.begin(), _trackVec.end()); 
	return 0; 
}

UInt_16b E3RecoEvent::numTracks()
{
	return _trackVec.size();
}

UInt_16b E3RecoEvent::numGoodTracks()
{

	UInt_16b idx=0;

	for (idx=0; idx<_trackVec.size(); idx++)
		if (_trackVec.at(idx).chisquare() > CHI2THR) break;

	return idx;
}


E3Track E3RecoEvent::bestTrack() 
{
  if (numTracks()) return _trackVec.front();
  else return E3Track();
}
UInt_16b E3RecoEvent::reconstruct()
{
	findHits();
	findClusters();
	findTracks();
	return 0;
}


