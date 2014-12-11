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

#ifndef BOSS__E3POINT__LIBGUARD
#define BOSS__E3POINT__LIBGUARD


/*! \class E3Point
  \brief Small class representing a three-dimensional point.
*/

class E3Point
{
 public:
  /// \brief Do-nothing constructor.
  E3Point();

  /// \brief Full constructor from the three components.
  E3Point(double x, double y, double z);

  /// \brief Destructor.
  ~E3Point() {}

  /// \brief Return the x-coordinate.
  double x() const { return m_x; } 

  /// \brief Return the x-coordinate.
  double y() const { return m_y; }

  /// \brief Return the x-coordinate.
  double z() const { return m_z; }

  /// \brief Scale the components of the vector by a multiplicative factor.
  void scale(double factor);

  /// \brief Vector sum.
  E3Point& operator+=( E3Point& rhs);

  /// \brief Vector sum.
  friend E3Point operator+(E3Point lhs,  E3Point& rhs)
  { lhs += rhs; return lhs; }

  /// \brief Vector difference.
  E3Point& operator-=( E3Point& rhs);

  /// \brief Vector sum.
  friend E3Point operator-(E3Point lhs,  E3Point& rhs)
  { lhs -= rhs; return lhs; }  

  /// \brief Multiplication by a constant.
  friend E3Point operator*(E3Point point, double factor)
    { point.scale(factor); return point; }

  /// \brief Multiplication by a constant.
  friend E3Point operator*(double factor, E3Point point)
    { point.scale(factor); return point; }

  /// \brief Division by a constant.
  ///
  /// \todo We need to do something here to protect the code from zero
  /// division.
  friend E3Point operator/(E3Point point, double factor)
    { point.scale(1./factor); return point; }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os) ;

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os,  E3Point& p)
    { return p.fillStream(os); }

 protected:
  /// \brief The x-coordinate.
  double m_x;
  /// \brief The y-coordinate.
  double m_y;
  /// \brief The z-coordinate.
  double m_z;
};


typedef std::vector<E3Point> E3PointVec;

typedef E3PointVec::iterator E3PointVecIter;

#endif
