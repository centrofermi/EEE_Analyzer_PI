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

#include "stdafx.h"

E3Cluster::E3Cluster() :
  m_plane(0)
{
  clear();
}

E3Cluster::E3Cluster(UInt_16b plane) :
  m_plane(plane)
{
  clear();
}


void E3Cluster::clear()
{
  m_x = 0.;
  m_y = 0.;
  m_z = 0.;
  m_hitTime = -1;
  m_channelVec.clear(); 
}


void E3Cluster::addHit( E3Hit& hit)
{
  double n = double(numHits());
  m_x = (m_x*n + hit.x())/(n + 1);
  m_y = (m_y*n + hit.y())/(n + 1);
  m_z = (m_z*n + hit.z())/(n + 1);
  m_hitTime = (m_hitTime*n + hit.hitTime())/(n + 1);
  m_channelVec.push_back(hit.channel());
}


std::ostream& E3Cluster::fillStream(std::ostream& os) 
{
  os << "Cluster (plane " << m_plane << ", channels [";
  std::vector<UInt_16b>::const_iterator chan;
  for (chan = m_channelVec.begin(); chan != m_channelVec.end(); chan++) {
    os << *chan;
    if (chan < m_channelVec.end() - 1) {
      os  << ", ";
    }
  }
  os << "])..." << std::endl << "  ";
  E3Point::fillStream(os);
  os << " cm @ " << m_hitTime << " ns";
  return os;
}
