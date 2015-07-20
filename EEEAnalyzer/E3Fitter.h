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

#ifndef BOSS__E3FITTER__LIBGUARD
#define BOSS__E3FITTER__LIBGUARD


/*! \class E3FittingTool
  \brief Track fitting tool.
*/

class E3FittingTool
{
 public:
  /// \brief Do-nothing constructor.
  E3FittingTool();

  /// \brief Destructor.
  ~E3FittingTool() {}

  /// \brief Clear the parameters stored in the underlying track object.
  void clear();

  /// \brief Return the track.
  E3Track track()  { return m_track; }

  /// \brief Run the actual fit on a series of points.
  UInt_16b run(std::vector<E3Point>& pointVec);

 private:
  /// \btief The underlying track object being fitted.
  E3Track m_track;
};

#endif

