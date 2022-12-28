#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>   
#include <actionlib/client/simple_action_client.h>   
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <signal.h>  
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void DoShutdown(int sig)
{
	ROS_INFO("shutting down!");
	ros::shutdown(); 
    exit(sig); 
}


viod openfile()
{
    Json::Reader reader_;
    Json::Value root_;
    std::ifstream in_;

      in_.open( "/home/ubuntu/myagv_ros/src/auto_dock/data/0.json",std::ios::binary);
      if (!in_.is_open())
       {
       std::cout << "Error opening file\n";
       return;
       }
      if (reader_.parse(in_, root_)) 
      {
           goal_point[0] = root_["pos_x"].asDouble();
           goal_point[1] = root_["pos_y"].asDouble();
           goal_point[2] = root_["pos_z"].asDouble();
           goal_point[3] = root_["ori_x"].asDouble();
           goal_point[4] = root_["ori_y"].asDouble();
           goal_point[5] = root_["ori_z"].asDouble();
           goal_point[6] = root_["ori_w"].asDouble();     
      }

}


int main(int argc, char** argv){
    ros::init(argc, argv, "a_goals_sender"); 

    MoveBaseClient ac("move_base", true);
    double goal_point[6];

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    move_base_msgs::MoveBaseGoal goal;
 
    signal(SIGINT, DoShutdown);
    
    ros::NodeHandle n;
    ros::Rate loop_rate(100); 
    openfile();
    while (ros::ok())
    {
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = goal_point[0];
        goal.target_pose.pose.position.y = goal_point[1];
        goal.target_pose.pose.position.z = goal_point[2];
        goal.target_pose.pose.orientation.x=goal_point[3];
        goal.target_pose.pose.orientation.y=goal_point[4];
        goal.target_pose.pose.orientation.z=goal_point[5];  
        goal.target_pose.pose.orientation.w = goal_point[6];

        ROS_INFO("Sending goal");

        std::cout <<  goal.target_pose.pose.position.x << " "
                  <<  goal.target_pose.pose.position.y << " "
                  <<  goal.target_pose.pose.position.z << " "
                  <<  goal.target_pose.pose.orientation.z << " "
                  <<  goal.target_pose.pose.orientation.w <<  std::endl;
                

        ac.sendGoal(goal);

        ac.waitForResult();
   
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
          ROS_INFO("ok, the base moved to the goal");
        else
          ROS_ERROR("The base failed to move for some reason");
      
        ros::spinOnce();

        loop_rate.sleep();
    }
    return 0;
}

