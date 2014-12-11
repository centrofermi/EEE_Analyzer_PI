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


E3Vector::E3Vector() :
  E3Point()
{}


E3Vector::E3Vector(double x, double y, double z) :
  E3Point(x, y, z)
{}


E3Vector::E3Vector(const  E3Point &p) :
  E3Point(p.x(), p.y(), p.z())
{}


double E3Vector::mag2()  
{
  return (m_x*m_x + m_y*m_y + m_z*m_z);
}


double E3Vector::mag()  
{
  return sqrt(mag2());
}


E3Vector E3Vector::unit()  
{
  return (*this)/mag();
}


double E3Vector::theta()  
{
  return degrees(acos(m_z/mag()));
}


double E3Vector::phi()  
{
  return degrees(atan2(m_y, m_x));
}


std::ostream& E3Vector::fillStream(std::ostream& os)  
{
  os << "V(" << m_x << ", " << m_y << ", " << m_z << ")";
  return os;
}
