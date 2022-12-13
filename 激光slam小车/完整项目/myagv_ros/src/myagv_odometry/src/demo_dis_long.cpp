#include<ros/ros.h>
#include<string>
#include<iostream>
#include<geometry_msgs/Pose.h>
#include<nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>
#include<time.h>

double r_dis_long;
double ix, iy, px, py;//initation & pose x,y

double dis_long;//the distance need to move
double robot_v;//the linear_velocity with the robot
//double robot_w;//the angular_velcity eith the robot

//ros::Time last_time, current_time;



void poseCallback(const nav_msgs::Odometry &p_msg){
    px = p_msg.pose.pose.position.x;
    py = p_msg.pose.pose.position.y;
   // ROS_INFO("Robot walked %.2f m",px);
    ROS_INFO("Robot walked %.2f m",py);
}

int main(int argc,char** argv){
    ros::init(argc, argv, "command_publisher");
    ros::NodeHandle nh;
    ros::Publisher command_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    // ros::Publisher  init_data_pub = nh.advertise<nav_msgs::Odometry>("/odom", 10);
    ros::Subscriber pose_sub = nh.subscribe("/odom", 10, poseCallback);
    
    std::cout << "Please Input distance(m) :"<< std::endl;
    std::cin >> dis_long;
    std::cout << "Please Input velocity(m/s) :"<< std::endl;
    std::cin >> robot_v;
    // std::cout << "Please Input radius(rad/s) :"<< std::endl;
    // std::cin >> robot_w;

    
    bool is_start = true;
    
    double count = 0;
    while(ros::ok()){
        ros::spinOnce();
        if(is_start)
        {
          //  ix = px;
              iy = py;
            is_start =false;
        }

        if(count < dis_long){
            ros::spinOnce();

            geometry_msgs::Twist com_msg;
            if( count > dis_long * 3 / 5){
                //com_msg.linear.x = robot_v / 3;
                com_msg.linear.y = robot_v / 4;
            }
            else{
               // com_msg.linear.x = robot_v;
               com_msg.linear.y = robot_v;
            }
           // ROS_INFO("Publish turtle velocity command[%.2f m/s,%.2f rad/s] distance: %.2f", com_msg.linear.x, com_msg.angular.z, count);
           ROS_INFO("Publish turtle velocity command[%.2f m/s,%.2f rad/s] distance: %.2f", com_msg.linear.y, com_msg.angular.z, count);
            command_pub.publish(com_msg);
            //count = px - ix;
             count = py - iy;
        }
        if(count >= dis_long)
        {   
           command_pub.publish(geometry_msgs::Twist());
        };
        
    }

    return 0;
}   
