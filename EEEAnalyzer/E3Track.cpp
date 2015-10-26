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
#include "E3Track.h" 


E3Track::E3Track() :
  m_origin(E3Point(0., 0., 0.)),
  m_direction(E3Vector(0., 0., -1.)),
  m_chisquare(-1)
{
m_clusters[0]=E3Cluster(0);
m_clusters[1]=E3Cluster(1);
m_clusters[2]=E3Cluster(2);
}


E3Track::E3Track(E3Point origin, E3Vector direction, double chisquare) :
  m_origin(origin),
  m_direction(direction),
  m_chisquare(chisquare)
{
m_clusters[0]=E3Cluster(0);
m_clusters[1]=E3Cluster(1);
m_clusters[2]=E3Cluster(2);
}


void E3Track::setCluster(UInt_16b plane, E3Cluster cluster)
{
  m_clusters[plane] = cluster;
}


double E3Track::timeOfFlight()  
{
  return (m_clusters[kBotPlane].hitTime() -
          m_clusters[kTopPlane].hitTime());
}


double E3Track::length()  
{
  E3Point p1 = extrapolate(m_clusters[kTopPlane].z()); 
  E3Point p2 = extrapolate(m_clusters[kBotPlane].z());
  return E3Vector(p1 - p2).mag();
}


E3Point E3Track::extrapolate(double z)  
{
  double x = m_origin.x() + (z - m_origin.z())*m_direction.x()/m_direction.z();
  double y = m_origin.y() + (z - m_origin.z())*m_direction.y()/m_direction.z();;
  return E3Point(x, y, z);
}


std::ostream& E3Track::fillStream(std::ostream& os)  
{
  os << "Track " << m_origin << " -- " << m_direction << "..." << std::endl;
  os << "  theta = " << theta() << ", phi = " << phi() << ", chisquare = "
     << m_chisquare << ".";
  return os;
}
