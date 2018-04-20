#ifndef GAME_HIDING_LAYER_H_
#define GAME_HIDING_LAYER_H_
#include <ros/ros.h>
#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>
#include <boost/thread.hpp>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Point.h"

namespace game_navigation_layers
{
	class HidingGameLayer : public costmap_2d::Layer
	{
		public:
			HidingGameLayer() { layered_costmap_ = NULL; }
			virtual void onInitialize();
			virtual void updateBounds(double origin_x, double origin_y, double origin_yaw, double* min_x, double* min_y, double* max_x, double* max_y);
			virtual void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j) = 0;
			virtual void updateBoundsFromSeeker(double* min_x, double* min_y, double* max_x, double* max_y) = 0;
			bool isDiscretized() { return false; }

		protected:
			void poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);
			void velocityCallback(const geometry_msgs::Point::ConstPtr& msg);
			ros::Subscriber pose_sub_;
			ros::Subscriber vel_sub_;
			geometry_msgs::PoseWithCovarianceStamped seeker_pose;
			geometry_msgs::Point seeker_position;
			geometry_msgs::Point seeker_velocity;
			ros::Duration seeker_keep_time_;
			boost::recursive_mutex lock_;
			tf::TransformListener tf_;
			bool first_time_;
			bool initialized_seeker_;
			double last_min_x_, last_min_y_, last_max_x_, last_max_y_;
	};
};

#endif

