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

#ifndef BOSS__E3HIT__LIBGUARD
#define BOSS__E3HIT__LIBGUARD

/*! \class E3Hit
  \brief Class describing a hit in the detector.

*/

class E3Hit : public E3Point
{
 public:
  /// \brief Default constructor.
	 E3Hit(UInt_16b plane, UInt_16b channel,
        double x, double y, double z, double t, double tot[2]);

  /// \brief Destructor.
  ~E3Hit() {}

  /// \brief Return the plane.
  inline UInt_16b plane()  { return m_plane; }

  /// \brief Return the channel.
  inline UInt_16b channel()  { return m_channel; }

  /// \brief
  inline double hitTime()  { return m_hitTime; }

  /// \brief Return the time over threshold for either of the strip ends.
  inline double tot(UInt_16b end)  { return m_tot[end]; }

  /// \brief Return the average time over threshold for the hit.
  double tot() ;

  /// \brief
  /// 
  /// @TODO 5 Should be an external reconstruction parameter.
  friend bool close( E3Hit &h1,  E3Hit &h2)
  { return (h1.plane() == h2.plane() &&
            std::abs(h1.channel() - h2.channel() <= 1) && 
            fabs(h1.x() - h2.x()) <= 5.); }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os) ;

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os,  E3Hit& h)
  { return h.fillStream(os); }

 private:
  /// \brief The identifier of the RPC plane.
  UInt_16b m_plane;

  /// \brief The strip ID.
  UInt_16b m_channel;

  /// \brief
  double m_hitTime;
 
  /// \brief The time over threshold (in ns) for the two strip ends.
  double m_tot[2];
};


typedef std::vector<E3Hit> E3HitVec;

typedef E3HitVec::iterator E3HitVecIter;

#endif