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
#include "E3Point.h" 


E3Point::E3Point() :
  m_x(0.),
  m_y(0.),
  m_z(0.)
{}


E3Point::E3Point(double x, double y, double z) :
  m_x(x),
  m_y(y),
  m_z(z)
{}


E3Point& E3Point::operator+=( E3Point& rhs)
{
  m_x += rhs.x();
  m_y += rhs.y();
  m_z += rhs.z();
  return *this;
}


E3Point& E3Point::operator-=( E3Point& rhs)
{
  m_x -= rhs.x();
  m_y -= rhs.y();
  m_z -= rhs.z();
  return *this;
}


void E3Point::scale(double factor)
{
  m_x *= factor;
  m_y *= factor;
  m_z *= factor;
}


std::ostream& E3Point::fillStream(std::ostream& os) 
{
  os << "P(" << m_x << ", " << m_y << ", " << m_z << ")";
  return os;
}
