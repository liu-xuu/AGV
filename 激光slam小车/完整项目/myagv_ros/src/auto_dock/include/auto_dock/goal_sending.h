#ifndef GOAL_SENDING_H
#define GOAL_SENDING_H
 
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <jsoncpp/json/json.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>
#include <fstream>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> Client;
 
class GoalSending {
 private:

  ros::NodeHandle nh_;
  ros::Publisher goal_pub_;
  ros::Timer timer_;
  geometry_msgs::PoseStamped target_pose_;
  move_base_msgs::MoveBaseGoal goal_;

  Client ac_;
 
  bool initialized_;
  int count = 0;
  Json::Reader reader_;
  Json::Value root_;
  std::ifstream in_;
 

  double goal_point_[4][2];

  void goalPointPub(const ros::TimerEvent& event);

  void openFile();

  void activeCb();
  void doneCb(const actionlib::SimpleClientGoalState& state,
              const move_base_msgs::MoveBaseResultConstPtr& result);
 
 public:
  GoalSending();
  ~GoalSending();
};
 
#endif  