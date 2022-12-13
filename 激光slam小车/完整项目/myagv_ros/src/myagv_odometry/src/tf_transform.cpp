#include "tf/transform_datatypes.h"
#include <nav_msgs/Odometry.h>
#include<iostream>
#include<string>
#include<ros/ros.h>
#include <math.h>



 void toEulerAngle(const double x,const double y,const double z,const double w)
{  double roll,pitch,yaw;
// roll (x-axis rotation)
    double sinr_cosp = +2.0 * (w * x + y * z);
    double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
    roll = std::atan2(sinr_cosp, cosr_cosp);

// pitch (y-axis rotation)
    double sinp = +2.0 * (w * y - z * x);
    if (std::fabs(sinp) >= 1)
        pitch = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
    else
        pitch = std::asin(sinp);

// yaw (z-axis rotation)
    double siny_cosp = +2.0 * (w * z + x * y);
    double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
    yaw = std::atan2(siny_cosp, cosy_cosp);
//    return yaw;
   ROS_INFO("yaw %.2f ",yaw*180/3.14159);
}


int main()
{   double x,y,z,w;     
    double a[4] = {0};
	for (int i = 0; i < 4; ++i){
		std::cin >> a[i];

	}
    x=a[0];
    y=a[1];
    z=a[2];
    w=a[3];
	for (int i = 0; i < 4; ++i){
		std::cout << a[i] << std::endl;
	}
	
    toEulerAngle(x,y,z,w);

   
 return 0;


}





 /**
void odomCallback(const nav_msgs::Odometry &odom) {
 
     
      tf::Quaternion quat;
      tf::quaternionMsgToTF(odom.pose.pose.orientation, quat);
 
     
      double roll, pitch, yaw;
      tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);
       
    }
 
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    ros::Subscriber quat_subscriber = n.subscribe("/odom", 1000, odomCallback);
 
    // check for incoming quaternions untill ctrl+c is pressed
    ROS_INFO("waiting for quaternion" );
    ros::spin();
    return 0;
}
**/