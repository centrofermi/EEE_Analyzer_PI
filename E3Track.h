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

#ifndef BOSS__E3TRACK__LIBGUARD
#define BOSS__E3TRACK__LIBGUARD

/*! \class E3Track
  \brief Class describing a reconstructed track.

  A track is essentially the result of a point (the origin or the head of the
  track) and a direction, with additional related quantities such as the
  chisquare. The class provides a method to extrapolate the track to a plane
  orthogonal to the z-y plane.

  Note that, since we have no way to distinguish between upward-going and
  downward-going particles---and the vast majority of our tracks are
  downward-going, anyway---we generally impose that m_direction.z() < 0
  when reconstructing tracks. Nonetheless we measure the polar angle from the
  zenith angle (i.e. a track with theta = 0 is a vertical downward-going one).
*/

class E3Track
{
 public:
  /// \brief Do-nothing constructor.
  E3Track();

  /// \brief Constructor.
  E3Track(E3Point origin, E3Vector direction, double chisquare);

  /// \brief Destructor. 
  ~E3Track() {}

  /// \brief Return the cluster associated with the track for a given plane.
  inline E3Cluster cluster(UInt_16b plane)
  { return m_clusters[plane]; }

  /// \brief Get the track start point.
  inline E3Point origin() 
  { return m_origin; }

  /// \brief Get the track direction.
  inline E3Vector direction() 
  { return m_direction; }

  /// \brief Get the track chi square.
  inline double chisquare() const 
  { return m_chisquare; }

  /// \brief
  void setCluster(UInt_16b plane, E3Cluster cluster);

  /// \brief Set the track start point.
  void setOrigin(E3Point origin) { m_origin = origin; }

  /// \brief Set the track direction.
  void setDirection(E3Vector direction) { m_direction = direction; }

  /// \brief Set the track chi square.
  void setChisquare(double chisquare) { m_chisquare = chisquare; }

  /// \brief 
  inline double x0()  { return m_origin.x(); }

  /// \brief 
  inline double y0()  { return m_origin.y(); }

  /// \brief 
  inline double z0()  { return m_origin.z(); }

  /// \brief 
  inline double xdir() { return m_direction.x(); }

  /// \brief 
  inline double ydir()  { return m_direction.y(); }

  /// \brief 
  inline double zdir()  { return m_direction.z(); }

  /// \brief Get the track polar angle.
  inline double theta()  { return m_direction.theta(); }

  /// \brief Get the track azimuthal angle.
  inline double phi()  { return m_direction.phi(); }

  /// \brief
  double timeOfFlight();

  /// \brief
  double length();

  /// \brief Return the extrapolated point at a given z coordinate.
  E3Point extrapolate(double z);
  
  /// \brief Define how to sort tracks.
  friend bool operator< (const E3Track &lhs, const E3Track &rhs)
  { return (lhs.chisquare() < rhs.chisquare()); }

  /// \brief Calculate the distance between the track and a point.
  friend double dist(E3Point& p, E3Track& t)
  { return cross(t.m_direction, E3Vector(t.m_origin - p)).mag(); }

  friend double dist( E3Track& t, E3Point& p)
  { return dist(p, t); }

  /// \brief Standard output.
  std::ostream& fillStream(std::ostream& os);

  /// \brief Standard output.
  friend std::ostream& operator<<(std::ostream& os, E3Track& t)
  { return t.fillStream(os); }

 private:
  
  /// \brief 
  E3Cluster m_clusters[3];

  /// \brief The track starting point.
  E3Point m_origin;

  /// \brief The track direction.
  E3Vector m_direction;
 
  /// \brief The track chi square.
  double m_chisquare;
};

typedef std::vector<E3Track> E3TrackVec;

typedef E3TrackVec::iterator E3TrackVecIter;


#endif
