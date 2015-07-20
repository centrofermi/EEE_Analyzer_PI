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


E3FittingTool::E3FittingTool()
{
  clear();
}


void E3FittingTool::clear()
{
  m_track.setOrigin(E3Point(0., 0., 0.));
  m_track.setDirection(E3Vector(0., 0., 1.));
  m_track.setChisquare(-1.);
}


UInt_16b E3FittingTool::run(std::vector<E3Point>& pointVec)
{
  clear();
  if (pointVec.size() < 2) return 1;

  // Initialize some variables for the fit.
  int n = 0;
  double sx = 0., sx_z = 0., sx_zz = 0., sx_x = 0., sx_zx = 0.;
  double sy = 0., sy_z = 0., sy_zz = 0., sy_y = 0., sy_zy = 0.;
  double weight;

  // Loop over the points.
  // Note that, since the weights correspond to errors in the x and y
  // directions, the two views are fitted in the z-x and z-y (as opposed to
  // x-z and y-z) planes (i.e. z acts as the abscissa in both cases). This
  // also turns out to be handy since we measure the theta angle (i.e. zdir)
  // from the z axis, rather than the x-y plane.
  for (std::vector<E3Point>::const_iterator p = pointVec.begin();
       p != pointVec.end(); p++) {
    E3Point position = *p;
    // Take all the weights equal for the time being.
    weight = 1.;
    n += 1;
    sy += weight;
    sy_z += position.z()*weight;
    sy_zz += position.z()*position.z()*weight;
    sy_y += position.y()*weight;
    sy_zy += position.z()*position.y()*weight;
    sx += weight;
    sx_z += position.z()*weight;
    sx_zz += position.z()*position.z()*weight;
    sx_x += position.x()*weight;
    sx_zx += position.z()*position.x()*weight;
  }

  // Go ahead with the fit parameters, i.e. the slopes in the two views.
  double zxslope = (sx_zx*sx - sx_z*sx_x)/(sx_zz*sx - sx_z*sx_z);
  double zyslope = (sy_zy*sy - sy_z*sy_y)/(sy_zz*sy - sy_z*sy_z);
  double zxintercept = (sx_x*sx_zz - sx_zx*sx_z)/(sx_zz*sx - sx_z*sx_z);
  double zyintercept = (sy_y*sy_zz - sy_zy*sy_z)/(sy_zz*sy - sy_z*sy_z);

  // Convert from the slope/intercept representation to the director cosines.
  double denom = sqrt(1 + zxslope*zxslope + zyslope*zyslope);
  double xdir  = zxslope/denom;
  double ydir  = zyslope/denom;
  double zdir  = 1./denom;
  m_track.setDirection(E3Vector(xdir, ydir, zdir));

  // Refer the centroid to a common z0 value (e.g., the z of the first hit).
  double z0 = pointVec.at(0).z();
  double x0 = zxintercept + z0*zxslope;
  double y0 = zyintercept + z0*zyslope; 
  m_track.setOrigin(E3Point(x0, y0, z0));

  // Need a final loop to calculate the chisquare, here.
  double chisquare = 0.;
  /// \todo This should be set to a reasonable value.
  double err = 2.5; 
  for (std::vector<E3Point>::iterator p = pointVec.begin();
       p != pointVec.end(); p++) {
    double d = dist(*p, m_track)/err;
    chisquare += d*d;
  }
  //chisquare /= pointVec.size();
  m_track.setChisquare(chisquare);

  return 0;
}
