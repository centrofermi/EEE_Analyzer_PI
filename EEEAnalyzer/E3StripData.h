
/*
  Copyright (C) 2012--2013 Luca Baldini (luca.baldini@pi.infn.it)

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

#ifndef BOSS__E3STRIPDATA__LIBGUARD
#define BOSS__E3STRIPDATA__LIBGUARD
#include <iostream> 
#include "intDef.h" 
#include "E3RawData.h" 


/*! \class E3StripData
  \brief Base class describing the portion of the event contribution relative
  to a single RPC strip.

  This encapsulates the identifiers of the plane and the channel, along
  with the timestamps of all the (rising and falling) edges on both
  sides of the plane.

  We have all the information, here, to extract the three-dimensional hit
  (or hits) to be passed to the clustering stage, with all the associated
  physical quantities.

  As it turns out, this class is not as trivial as one might naively think.
  The Rpc strips are read out from both sides---the difference in the arrival
  times giving the coordinate along the strips.
  
  At the digi level we keep track of the arrival times of both the raising
  and the falling edges at both sides. We might have one or more edges of
  each type at both ends (e.g., noise can cause spurious hits). We can even
  have "orphane" transitions, if the signal in a channel is already up when
  the readout starts or didn't have time to return to the baseline when the
  readout stops.

  Here we try and associate the "right" rising edges in order to have the
  longitudinal position along the strip. We might also try and extract some
  meaningful information from the time over threshold.
*/


class E3StripData
{
 public:
  /// \brief Default constructor.
	 E3StripData(UInt_16b plane, UInt_16b channel);

  /// \brief Destructor.
  ~E3StripData() {}

  /// \brief Clear the data structure.
  void clear();

  /// \brief Return the plane.
  inline UInt_16b plane()  { return m_plane; }

  /// \brief Return the channel.
  inline UInt_16b channel()  { return m_channel; }

  /// \brief Add a new digi word (of type edge).
  void addEdgeDigi(UInt_16b side, E3RawData digi);

  /// \brief Return the vector of edges for the selected plane end.
  inline E3RawDataVec edgeDigiVec(UInt_16b end) 
  { return m_edgeRawVec[end]; }

  /// \brief Return the vector of edges for the positive plane end.
  inline E3RawDataVec posEdgeDigiVec() 
  { return m_edgeRawVec[0]; }

  /// \brief Return the vector of edges for the negative plane end.
  inline E3RawDataVec negEdgeDigiVec() 
  { return m_edgeRawVec[1]; }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os) ;

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os, E3StripData& d)
  { return d.fillStream(os); }

 private:
  /// \brief The plane ID.
  UInt_16b m_plane;

  /// \brief The channel ID.
  UInt_16b m_channel;

  /// \brief The vector of edge times (for the positive and the negative side).
  E3RawDataVec m_edgeRawVec[2];
};


typedef std::vector<E3StripData> E3StripDataVec;

typedef std::vector<E3StripData>::iterator E3StripDataVecIter;

#endif
