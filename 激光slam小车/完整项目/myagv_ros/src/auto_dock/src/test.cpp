/**
 * @file goalsengding.cpp
 * @author sifan
 * @brief
 * Ñ­»··¢²¼Ä¿±êµã³ÌÐò£¬´ÓjsonÎÄ¼þ¶ÁÈ¡Ä¿±êµã½øÐÐ·¢²¼,´Ómove_base·´À¡×´Ì¬ÅÐ¶Ï»úÆ÷ÈËÊÇ·ñ´ïµ½Ä¿±êµã£¬ËÄ¸öµãµÄÄ¿±êÑ­»·£¬ÈçÐèÔö¼Óµã£¬ÔòÐÞ¸Ägoal_pointµÄÎ¬¶È´óÐ¡¡£
 *         »òÕß½«´æ·ÅÄ¿±êµãµÄÊý×é¸ÄÎªvector´¢´æµÄÐÎÊ½£¬¿ÉÒÔ²»ÏÞÖÆµãÊýÁ¿¡£
 * @version 0.1
 * @date 2022-08-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "move_base_goalsending.h"
#include <iostream>
 
GoalSending::GoalSending() : ac_("move_base", true), initialized_(false) {
  //´ÓjsonÎÄ¼þÖÐ¶ÁÈ¡Ä¿±êµã
  this->openFile();
  //¹¹½¨¶¨Ê±Æ÷£¬¶¨Ê±ÅÐ¶ÏÊÇ·ñ´ïµ½Ä¿±êµã£¬ÒÔ·¢ËÍÏÂÒ»¸öÄ¿±ê
  timer_ =
      nh_.createTimer(ros::Duration(0.3), &GoalSending::goalPointPub, this);
 
  ROS_INFO("Starting success");
}
 
void GoalSending::openFile() {
  //Ê¹ÓÃÊ±ÐèÒª½«¸ÃÂ·¾¶Ìæ»»Îª×Ô¼ºjsonÎÄ¼þ¶ÔÓ¦µÄÂ·¾¶
  in_.open(
      "/home/robint01/robintros_ws/src/RobintROS/move_base_send_goal/json/"
      "goal.json",
      std::ios::binary);
  if (!in_.is_open()) {
    std::cout << "Error opening file\n";
    return;
  }
  if (reader_.parse(in_, root_)) {
    for (int i = 0; i < 4; i++) {
      goal_point_[i][0] = root_["goalname"][i]["location"][0].asDouble();
      goal_point_[i][1] = root_["goalname"][i]["location"][1].asDouble();
    }
  }
}
void GoalSending::doneCb(const actionlib::SimpleClientGoalState& state,
                         const move_base_msgs::MoveBaseResultConstPtr& result) {
  if (state == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("SUCCEEDED");
  }
}
void GoalSending::activeCb() {
  ROS_INFO("Goal Received");
}
 
void GoalSending::goalPointPub(const ros::TimerEvent& event) {
  //·¢ËÍ³õÊ¼µãÎ»
  if (!initialized_) {
    target_pose_.header.seq = 1;
    target_pose_.header.frame_id = "map";
    target_pose_.header.stamp = ros::Time::now();
    target_pose_.pose.position.x = goal_point_[0][0];
    target_pose_.pose.position.y = goal_point_[0][1];
    target_pose_.pose.orientation.z = 0.01;
    target_pose_.pose.orientation.w = 0.01;
    goal_.target_pose = target_pose_;
    initialized_ = true;
    if (!ac_.waitForServer(ros::Duration(60))) {
      ROS_INFO("Can't connected to move base server");
    }
    ac_.sendGoal(goal_, boost::bind(&GoalSending::doneCb, this, _1, _2),
                 boost::bind(&GoalSending::activeCb, this),
                 Client::SimpleFeedbackCallback());
  }
  //ÅÐ¶ÏÊÇ·ñ´æÔÚÇÀÕ¼£¬Èç¹ûÓÐÇÀÕ¼£¬ÔòÁ¢¼´ÖØÐÂ·¢²¼Ä¿±ê£¨¼´²»ÔÊÐíÇÀÕ¼Çé¿ö³öÏÖ£¬ÈçÏë¿ÉÒÔ·¢ÉúÇÀÕ¼,×¢ÊÍµôÕâ¸öifÓï¾ä£©
  if (ac_.getState() == actionlib::SimpleClientGoalState::PREEMPTED) {
    ac_.sendGoal(goal_, boost::bind(&GoalSending::doneCb, this, _1, _2),
                 boost::bind(&GoalSending::activeCb, this),
                 Client::SimpleFeedbackCallback());
    ROS_WARN("No preemption");
  }
  //ÅÐ¶ÏÊÇ·ñµ½´ïÄ¿±êµã£¬Èç¹û³É¹¦£¬Ôò·¢²¼ÏÂÒ»¸öµã
  if (ac_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    count++;
    target_pose_.header.seq = count + 1;
    target_pose_.header.frame_id = "map";
    target_pose_.header.stamp = ros::Time::now();
    target_pose_.pose.position.x = goal_point_[count][0];
    target_pose_.pose.position.y = goal_point_[count][1];
    target_pose_.pose.orientation.z = 0.01;
    target_pose_.pose.orientation.w = 0.01;
    goal_.target_pose = target_pose_;
    if (!ac_.waitForServer(ros::Duration(60))) {
      ROS_INFO("Can't connected to move base server");
    }
    ac_.sendGoal(goal_, boost::bind(&GoalSending::doneCb, this, _1, _2),
                 boost::bind(&GoalSending::activeCb, this),
                 Client::SimpleFeedbackCallback());
  }
  //Èç¹ûÒÑ¾­µ½´ïµÚËÄ¸öµã£¬Ôò³õÊ¼»¯£¬»Øµ½µÚÒ»¸öµã£¬Ñ­»·ÔË¶¯
  if (count == 4) {
    initialized_ = false;
    count = 0;
  }
}
 
GoalSending::~GoalSending() {
  in_.close();
}
int main(int argc, char** argv) {
  ros::init(argc, argv, "goalsending");
  GoalSending gs;
  ros::spin();
  return 0;
}