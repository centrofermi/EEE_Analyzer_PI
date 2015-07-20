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

#include "stdafx.h"



E3Hit::E3Hit(UInt_16b plane, UInt_16b channel, double x, double y, double z, double t, double tot[2]) :
  E3Point(x, y, z),
  m_plane(plane),
  m_channel(channel),
  m_hitTime(t)
{
  m_tot[0] = tot[0];
  m_tot[1] = tot[1];
}


double E3Hit::tot() 
{
  if (m_tot[0] > 0 && m_tot[1] > 0) {
    return 0.5*(m_tot[0] + m_tot[1]);
  } else {
    return m_tot[0] + m_tot[1] + 1;
  }
}


std::ostream& E3Hit::fillStream(std::ostream& os) 
{
  os << "Hit (plane " << m_plane << ", channel " << m_channel << ")..."
     << std::endl << "  ";
  E3Point::fillStream(os);
  os << " cm @ " << m_hitTime << " ns, ToT " << m_tot[0] << "[+] ns, "
     << m_tot[1] << "[-] ns";
  return os;
}