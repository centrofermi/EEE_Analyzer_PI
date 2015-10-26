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
#include "E3StripData.h" 

E3StripData::E3StripData( UInt_16b plane, UInt_16b channel) :
  m_plane(plane),
  m_channel(channel)
{
  clear();
}


void E3StripData::clear()
{
  m_edgeRawVec[0].clear();
  m_edgeRawVec[1].clear();
}


void E3StripData::addEdgeDigi(UInt_16b side, E3RawData digi)
{
  m_edgeRawVec[side].push_back(digi);
}


std::ostream& E3StripData::fillStream(std::ostream& os) 
{
  os << "Strip data (plane " << m_plane << ", channel " << m_channel << ")..."
     << std::endl;
  E3RawDataVecIter digi, begin, end;
  os << "  [+ side]: ";
  begin= m_edgeRawVec[0].begin();
  begin = m_edgeRawVec[0].begin();
  end = m_edgeRawVec[0].end();
  for (digi = begin; digi != end; digi++) {
	  os << digi->getPs();
    if (digi->isRisingEdge()) os << "[r] ps";
    else if (digi->isFallingEdge()) os << "[f] ps";
    if (digi < end - 1) os << ", ";
  }
  os << std::endl << "  [- side]: ";
  begin = m_edgeRawVec[1].begin();
  end = m_edgeRawVec[1].end();
  for (digi = begin; digi != end; digi++) {
	  os << digi->getPs();
    if (digi->isRisingEdge()) os << "[r] ps";
    else if (digi->isFallingEdge()) os << "[f] ps";
    if (digi < end - 1) os << ", ";
  }
  return os;
}
