#pragma once

#include <memory>
#include <geometry_msgs/Pose.h>
#include <octomap/math/Vector3.h>
#include <octomap/OcTree.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/tf.h>
#include <urdf/model.h>
#include <vfh3d/utils.h>
#include <vfh3d/vehicle_state.h>
#include <vfh3d/polar_histogram.h>

using namespace octomap;

namespace vfh3d {

class VFH3DPlanner 
{
public:
  VFH3DPlanner();
  ~VFH3DPlanner() {}

  void update();

  // callbacks
  void poseCb(const geometry_msgs::PoseStampedConstPtr& pose_msg);
  void goalCb(const geometry_msgs::PoseConstPtr& goal_msg);
  void octomapCb(const octomap_msgs::OctomapConstPtr& octomap_msg);

private:
  // ros
  ros::NodeHandle nh_;
  tf::Pose goal_;

  // publishers
  ros::Publisher histogram_pub_, planned_target_pub_;
  ros::Publisher bbx_cells_pub_;

  // subscribers
  ros::Subscriber vehicle_pose_sub_, octomap_sub_, goal_sub_;

  // params
  double hist_resolution_;
  double max_plan_range_;
  double map_resolution_;
  
  // planning
  std::shared_ptr<OcTree> oc_tree_;
  std::shared_ptr<VehicleState> vehicle_state_;
  std::unique_ptr<PolarHistogram> polar_histogram_;
};

}