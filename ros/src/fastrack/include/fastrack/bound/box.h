/*
 * Copyright (c) 2018, The Regents of the University of California (Regents).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS AS IS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Please contact the author(s) of this library if you have any questions.
 * Authors: David Fridovich-Keil   ( dfk@eecs.berkeley.edu )
 */

///////////////////////////////////////////////////////////////////////////////
//
// Box for tracking error bound. This will arise when dynamics decouple into
// 1D subsystems. Boxes are defined only by their size in each dimension.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef FASTRACK_BOUND_BOX_H
#define FASTRACK_BOUND_BOX_H

#include <fastrack/bound/tracking_bound.h>
#include <fastrack/utils/types.h>

#include <fastrack_srvs/TrackingBoundBox.h>
#include <fastrack_srvs/TrackingBoundBoxResponse.h>

namespace fastrack {
namespace bound {

struct Box : public TrackingBound<fastrack_srvs::TrackingBoundBox::Response> {
  // Size in each dimension.
  double x;
  double y;
  double z;

  // Constructors and destructor.
  ~Box() {}
  explicit Box()
    : TrackingBound() {}
  explicit Box(double xsize, double ysize, double zsize)
    : TrackingBound(),
      x(xsize), y(ysize), z(zsize) {}

  // Convert from service response type SR.
  inline void FromRos(const fastrack_srvs::TrackingBoundBox::Response& res) {
    x = res.x; y = res.y; z = res.z;
  }

  // Convert to service response.
  inline fastrack_srvs::TrackingBoundBox::Response ToRos() const {
    fastrack_srvs::TrackingBoundBox::Response res;
    res.x = x; res.y = y; res.z = z;
    return res;
  }

  // Visualize.
  inline void Visualize(const ros::Publisher& pub, const std::string& frame) const {
    visualization_msgs::Marker m;
    m.ns = "bound";
    m.header.frame_id = frame;
    m.header.stamp = ros::Time::now();
    m.id = 0;
    m.type = visualization_msgs::Marker::CUBE;
    m.action = visualization_msgs::Marker::ADD;
    m.color.a = 0.3;
    m.color.r = 0.5;
    m.color.g = 0.1;
    m.color.b = 0.5;
    m.scale.x = 2.0 * x;
    m.scale.y = 2.0 * y;
    m.scale.z = 2.0 * z;

    pub.publish(m);
  }

}; //\struct Box

} //\namespace bound
} //\namespace fastrack

#endif
