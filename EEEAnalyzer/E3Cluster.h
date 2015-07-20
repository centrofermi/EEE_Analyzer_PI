/*
  Copyright (C) 2012 Luca Baldini (luca.baldini@pi.infn.it)

  For the license terms see the file LICENSE, distributed along with this
  software.

  This program is free software; you can redistribute it and/or modify it under
  the terms of the GNU General Public License as published by the Free Software
  Foundation; either version 3 of the License, or (at your option) any later
  version.
  
  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef BOSS__E3CLUSTER__LIBGUARD
#define BOSS__E3CLUSTER__LIBGUARD

/*! \class E3Cluster
  \brief Class describing a cluster in the detector.

*/

class E3Cluster : public E3Point
{
 public:
	 
  /// \brief Default constructor.
	 E3Cluster(UInt_16b plane);

  /// \brief Default constructor.
	 E3Cluster();

  /// \brief Destructor.
  ~E3Cluster() {}

  /// \brief 
  void clear();

  /// \brief Return the plane.
  inline UInt_16b plane()  { return m_plane; }

  /// \brief 
  inline UInt_16b numHits()  { return m_channelVec.size(); }

  /// \brief
  inline double hitTime()  { return m_hitTime; }

  /// \brief add hit to cluster
  void addHit( E3Hit& hit);
  
  friend bool close( E3Cluster &h1,  E3Hit &h2)
  { return (h1.plane() == h2.plane() &&
				std::abs(h1.y() - h2.y() <= CLUSTERYSIZE) && 
            fabs(h1.x() - h2.x()) <= CLUSTERXSIZE); }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os) ;

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os,  E3Cluster& c)
  { return c.fillStream(os); }

 private:
  
  /// \brief The identifier of the RPC plane.
  UInt_16b m_plane;

  /// \brief The list of channels in the cluster.
  std::vector<UInt_16b> m_channelVec;

  /// \brief The average hit time.
  double m_hitTime;
};


typedef std::vector<E3Cluster> E3ClusterVec;

typedef E3ClusterVec::iterator E3ClusterVecIter;

#endif