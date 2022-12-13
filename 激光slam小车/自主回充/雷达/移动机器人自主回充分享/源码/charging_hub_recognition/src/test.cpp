
#include "ros/ros.h" 
#include <iostream>                   
#include "std_msgs/Float32MultiArray.h"

double sensorX_ = 1.5;//默认1500mm
double angle_increment = 0.0174532923847;

//测试用
void chargeCallback(const std_msgs::Float32MultiArray &msg)
{
	static float tempvalue = 0;
	static int count = 0;
	
	if(!std::isinf(msg.data.at(5)))
	{
		tempvalue = msg.data.at(5)*sinf(msg.data.at(4)*angle_increment) + 0.02;
		count++;
	}
	if(count==1)//除了这一次数据正确，其他情况，sensorX_，发送的时候乘以1000换算成mm
	{
		sensorX_  = tempvalue;//取平均
        std::cout<< (int)(sensorX_*1000) <<std::endl;
		tempvalue = 0;
		count     = 0;
	}
	else
	{
		sensorX_  = 1.5;
	}	
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"charge_sub");  
	ros::NodeHandle nh;   
    ros::Subscriber sub =nh.subscribe("charge",1000,chargeCallback);

    ros::spin();

	return 0;
}