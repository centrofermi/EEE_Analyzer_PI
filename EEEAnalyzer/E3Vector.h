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

#ifndef BOSS__E3VECTOR__LIBGUARD
#define BOSS__E3VECTOR__LIBGUARD
#include "E3Point.h" 


/// \brief Conversion from and to radians/degrees.
#define degrees(rad) rad*180./3.141592653589793
#define radians(deg) deg*3.141592653589793/180.


/*! \class E3Vector
  \brief Small class representing a three-dimensional vector.
*/

class E3Vector : public E3Point
{
 public:
  /// \brief Do-nothing constructor.
  E3Vector();

  /// \brief Full constructor from the three components.
  E3Vector(double x, double y, double z);

  /// \brief Copy constructor from an E3Point object.
  E3Vector( const E3Point &p);

  /// \brief Destructor.
  ~E3Vector() {}

  /// \brief Return the norm squared of the vector.
  double mag2()  ;

  /// \brief Return the norm of the vector.
  double mag()  ;

  /// \brief Return the normalized versor corresponding to the vector.
  E3Vector unit()  ;

  /// \brief Return the theta angle.
  double theta()  ;

  /// \brief Return the phi angle.
  double phi()  ;

  /// \brief Multiplication by a constant.
  friend E3Vector operator*(E3Vector vec, double factor)
    { vec.scale(factor); return vec; }

  /// \brief Multiplication by a constant.
  friend E3Vector operator*(double factor, E3Vector vec)
    { vec.scale(factor); return vec; }

  /// \brief Division by a constant.
  ///
  /// \todo We need to do something here to protect the code from zero
  /// division.
  friend E3Vector operator/(E3Vector vec, double factor)
    { vec.scale(1./factor); return vec; }  

  /// \brief Scalar product.
  friend double dot(const  E3Vector &v1, const  E3Vector &v2)
  { return (v1.m_x*v2.m_x + v1.m_y*v2.m_y + v1.m_z*v2.m_z); }

  /// \brief Vector product.
  friend E3Vector cross(const  E3Vector &v1,const  E3Vector &v2)
  { double x = v1.m_y*v2.m_z - v1.m_z*v2.m_y;
    double y = v1.m_z*v2.m_x - v1.m_x*v2.m_z;
    double z = v1.m_x*v2.m_y - v1.m_y*v2.m_x;
    return E3Vector(x, y, z); }

  /// \brief Angle between two vectors.
  friend double angle(  E3Vector &v1,   E3Vector &v2)
  { return degrees(acos(dot(v1.unit(), v2.unit()))); }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os)  ;

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os,   E3Vector& v)
    { return v.fillStream(os); }
};

#endif
