
/*
充电桩识别程序，可视化，标记出充电桩的位置
算法为：复现论文中提到的算法
订阅scan,得到充电桩的位置, 并添加可视化，可以在rviz中显示charge_marker
*/
#include "ros/ros.h" 
#include <iostream>                   
#include "std_msgs/Float32MultiArray.h"
#include "sensor_msgs/LaserScan.h"
#include <vector>
#include <cmath>
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/Point.h"
//可视化======================================================================
#define VISUAL 1    //调试时用1,使用时用0

#if VISUAL
visualization_msgs::Marker charge_hub_mark;
visualization_msgs::Marker point_mark;
#endif
/*=========================这里需要明确激光雷达坐标系以及详细数据格式===============

因为激光雷达朝x正方向安装，需要使用激光雷达前半部分数据，然而默认rplidar_ros的数据范围为（90-0）U（359-270），如下图2所示
这样导致数据段不连续，导致后续计算有些小麻烦，于是修改了rplidar_ros的publish_scan函数，使数据为（90-270）逆时针范围的数据，如下图1所示。

这是rplidar_ros修改之后的激光雷达坐标系以及详细数据格式,也是这里使用的
            x  ^ 180
               |
270 y  <-------|------- 90    laser_link (0-359)
               |
               | 0
               图1
这里的scan数据，每一帧360个距离数据点，对应的角度（0-359），距离数据逆时针从0度开始到359存储对应角度的距离数据，角分辨率1度，弧度：0.01745，，序号即代表角度 

这是rplidar_ros默认的激光雷达坐标系以及详细数据格式
               0
               |
               |
  270   -------|-------> 90 y laser_link (0-359)
               |
               v x
              180
               图2
这里的scan数据，每一帧360个距离数据点，对应的角度（0-359），距离数据逆时针从0度开始到359存储对应角度的距离数据，角分辨率1度，弧度：0.01745，序号即代表角度    

注意：该代码并不通用，但是如果修改了rplidar_ros的publish_scan函数，并且标志物和我要求的一致，完全可以直接使用
     若不修改rplidar_ros的publish_scan函数，依然想使用该代码，需要一点要求和更改也可以使用：
    （1）首先，检测数据范围不能出现分段，如（90-0）U（359-270）
    （2) 标志物和我要求的一致
    （3）修改可视化部分的在激光雷达坐标系下的突变点坐标计算 
============================================================================*/
#define MAX_RANGES_FROM_CHANGE 2.0 //假设充电桩只在2.0m范围内，之外的数据不考虑
#define MIN_RANGES_INDEX       90  //选择的雷达数据范围，这里没有全部使用，可以减少不必要的计算
#define MAX_RANGES_INDEX       270 //显然这里是 90-270 逆时针的数据，如图1所示

std_msgs::Float32MultiArray charge_info;//发布话题信息的对象
std::vector<float> laser_ranges;        //存储激光雷达，扫描数据
std::vector<bool>  mutation_point;      //存储充电桩突变点

//输出的四个数据ranges_left_charge、angle_left_charge、ranges_right_charge、angle_right_charge

float ranges_left_charge  =0;
int    angle_left_charge  =0;
float ranges_right_charge =0;
int    angle_right_charge =0;
float ranges_centre_charge=0;
int    angle_centre_charge=0;

//回调函数
void laserScanCallback(const sensor_msgs::LaserScan &msg)
{
    // std::cout << "laser_ok" << std::endl;
    char mutation_point_count(0);
    std::vector<int> mutation_point_index;
    mutation_point_index.resize(4);    
#if VISUAL
    static geometry_msgs::Point point1,point2,point3;
    std::vector<geometry_msgs::Point> point;//显示突变点
#endif
    laser_ranges.resize(MAX_RANGES_INDEX - MIN_RANGES_INDEX);

    //1.数据筛选
    for(size_t i = MIN_RANGES_INDEX ; i < MAX_RANGES_INDEX; i++) //在指定范围内筛选数据
    {
        if(std::isinf(msg.ranges[i]) || msg.ranges[i] > MAX_RANGES_FROM_CHANGE) 
            laser_ranges[i - MIN_RANGES_INDEX] = 0;
        else
            laser_ranges[i - MIN_RANGES_INDEX] = msg.ranges[i];
    }
    // std::cout<<"1.ok"<<std::endl;
    
    //2.数据补全
    for(size_t i = 1; i < laser_ranges.size()-2; i++) 
    {
        if(laser_ranges[i] < 0.0000001 && (fabs(laser_ranges[i+1] - laser_ranges[i-1]) < 0.02))//注意使用fabs，这里不要用abs
            laser_ranges[i] = (laser_ranges[i+1] + laser_ranges[i-1]) / 2.0;
        else if(laser_ranges[i] < 0.0000001 && laser_ranges[i+1] < 0.0000001 && (fabs(laser_ranges[i+2] - laser_ranges[i-1]) < 0.02))
            laser_ranges[i] = laser_ranges[i+1] = (laser_ranges[i+2] + laser_ranges[i-1]) / 2.0;
    }
    // std::cout<<"2.ok"<<std::endl;

    //3.突变点标定，寻找突变点
    int mutation_point_num = 0;
    mutation_point.resize(laser_ranges.size());
    for(size_t i = 0; i < laser_ranges.size()-2; i++) 
    {
        if((fabs(laser_ranges[i] - laser_ranges[i+1]) > 0.025) && (fabs(laser_ranges[i] - laser_ranges[i+1]) < 0.065)) //和自己标志物的形状有关
        {
            mutation_point_num++;
            mutation_point[i] = 1;
        }
        else
        {
            mutation_point[i] = 0;
        }
    }
    // std::cout<<"突变点个数："<<mutation_point_num<<std::endl;
#if VISUAL
    //所有突变点可视化
    point.clear();
    for (size_t i = 0; i < mutation_point.size(); i++)
    {
        if(mutation_point[i] == 1)
        {
            geometry_msgs::Point temp_point;
            temp_point.x = -laser_ranges[i]*cosf((i+MIN_RANGES_INDEX)*msg.angle_increment);
            temp_point.y = -laser_ranges[i]*sinf((i+MIN_RANGES_INDEX)*msg.angle_increment);
            temp_point.z = 0.0;  
            point.push_back(temp_point);
        }
    }
#endif
    // std::cout<<"3.ok"<<std::endl;
    //4.确定充电桩中心位置
    //先找到前四个突变点
    for(size_t i = 0; i < mutation_point.size(); i++) 
    {
        if(mutation_point[i] == 1)
        {
            mutation_point_index[mutation_point_count] = i;//把突变点代表的序号，放入
            mutation_point_count++;
        }
        if(mutation_point_count == 4) break;
    }

    //依次遍历，直到找到符合要求的连续四个突变点
    if(mutation_point_count == 4)//前提是至少有四个突变点，否则没有继续计算的必要
    {
        static bool find_mutation_flag = 0;
        for(size_t i = 0; i < mutation_point.size(); i++)
        {
            //特征点的距离大小特征                    
            if(laser_ranges[mutation_point_index[0]] < laser_ranges[mutation_point_index[1]] &&
                laser_ranges[mutation_point_index[2]] < laser_ranges[mutation_point_index[3]] )                   
            {
                // std::cout<<" 满足特征限制0 "<<std::endl;
                //特征点的距离大小特征 
                if(laser_ranges[mutation_point_index[0]] < laser_ranges[mutation_point_index[0] - 5] &&
                    laser_ranges[mutation_point_index[3]] < laser_ranges[mutation_point_index[3] + 5] )
                {
                    // std::cout<<" 满足特征限制1 "<<std::endl;
                    //特征点的间隔特征
                    if(abs(mutation_point_index[0] - mutation_point_index[1]) < 7 &&
                        abs(mutation_point_index[2] - mutation_point_index[3]) < 7 )
                    {
                        // std::cout<<" 满足特征限制2 "<<std::endl;
                        //特征点距离相差特征
                        if( fabs(laser_ranges[mutation_point_index[0]] - laser_ranges[mutation_point_index[1]]) < 0.08 &&
                            fabs(laser_ranges[mutation_point_index[2]] - laser_ranges[mutation_point_index[3]]) < 0.08 )
                        {
                            // std::cout<<" 满足特征限制3 "<<std::endl;  
                            find_mutation_flag  = 1;//找到突变点

                            angle_left_charge   = MIN_RANGES_INDEX + mutation_point_index[3];
                            angle_right_charge  = MIN_RANGES_INDEX + mutation_point_index[0];

                            ranges_left_charge  = laser_ranges[mutation_point_index[3]];
                            ranges_right_charge = laser_ranges[mutation_point_index[0]] + 0.06;//因为突变点的厚度0.06m

                            //虽然理论上不在中间，但是可以这样简单的用
                            angle_centre_charge = (int)(0.5 + (angle_left_charge + angle_right_charge)/ 2.0);
                            ranges_centre_charge= msg.ranges[angle_centre_charge];
                            
                            charge_info.data.resize(6);
                            charge_info.data[0]=angle_left_charge;
                            charge_info.data[1]=ranges_left_charge;
                            charge_info.data[2]=angle_right_charge;
                            charge_info.data[3]=ranges_right_charge;
                            charge_info.data[4]=angle_centre_charge;
                            charge_info.data[5]=ranges_centre_charge;
#if VISUAL
                            //在激光雷达坐标系下，突变点的坐标计算，这里坐标系使用的图1所示，如果使用图2,注意修改
                            point1.x = -ranges_left_charge*cosf(angle_left_charge*msg.angle_increment);
                            point1.y = -ranges_left_charge*sinf(angle_left_charge*msg.angle_increment);
                            point1.z = 0.0;

                            point2.x = -ranges_right_charge*cosf(angle_right_charge*msg.angle_increment);
                            point2.y = -ranges_right_charge*sinf(angle_right_charge*msg.angle_increment);
                            point2.z = 0.0;
                            
                            point3.x = -ranges_centre_charge*cosf(angle_centre_charge*msg.angle_increment);
                            point3.y = -ranges_centre_charge*sinf(angle_centre_charge*msg.angle_increment);
                            point3.z = 0.0;
#endif
                            break;
                        }
                    }
                }
            }
            
            //更新突变点序号
            mutation_point_index[0]=mutation_point_index[1];
            mutation_point_index[1]=mutation_point_index[2];
            mutation_point_index[2]=mutation_point_index[3];

            for(size_t j = mutation_point_index[3] + 1; j < mutation_point.size(); j++)//这里要从下一个开始，而不是当前
            {
                if(mutation_point[j] == 1)
                {
                    mutation_point_index[3] = j;
                    break;
                }
            }
        }
        //找到突变点
        if(find_mutation_flag == 1)
        {
            find_mutation_flag = 0;
        }
        else
        {
            //不满足情况数据清零
            charge_info.data.clear();
#if VISUAL
            point1.x = 0;
            point1.y = 0;
            point1.z = 0.0;

            point2.x = 0;
            point2.y = 0;
            point2.z = 0.0;
            
            point3.x = 0;
            point3.y = 0;
            point3.z = 0.0;             
#endif              
        }
    }
    else
    {  
        //不满足情况数据清零
        charge_info.data.clear();
#if VISUAL
        point1.x = 0;
        point1.y = 0;
        point1.z = 0.0;

        point2.x = 0;
        point2.y = 0;
        point2.z = 0.0;
        
        point3.x = 0;
        point3.y = 0;
        point3.z = 0.0;    
#endif                      
    }

    // std::cout<<"4.ok"<<std::endl;
    //5.可视化操作
#if VISUAL
    //充电桩标志
    charge_hub_mark.points.resize(3);
    charge_hub_mark.header.stamp = msg.header.stamp;
    charge_hub_mark.header.frame_id = msg.header.frame_id;
    charge_hub_mark.lifetime = ros::Duration();
    charge_hub_mark.points.at(0)=point1;
    charge_hub_mark.points.at(1)=point2;
    charge_hub_mark.points.at(2)=point3;
    
    //突变点
    point_mark.points.resize(point.size());
    point_mark.header.stamp = msg.header.stamp;
    point_mark.header.frame_id = msg.header.frame_id;
    point_mark.lifetime = ros::Duration();
    point_mark.points = point;
#endif  
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"charge_hub");  
	ros::NodeHandle nh;   
    ros::Subscriber sub  = nh.subscribe("scan",1000,laserScanCallback);
    ros::Publisher  pub  = nh.advertise<std_msgs::Float32MultiArray>("charge",1000);
#if VISUAL    
    ros::Publisher  pub_charge_marker = nh.advertise<visualization_msgs::Marker>("charge_marker", 100);
    ros::Publisher  pub_point_marker  = nh.advertise<visualization_msgs::Marker>("point_marker", 100);
#endif
	ros::Rate loop_rate(5);  

//============================================可视化====================================
#if VISUAL
    charge_hub_mark.action =charge_hub_mark.MODIFY;
    charge_hub_mark.ns = "markers";
    charge_hub_mark.id = 0;
    charge_hub_mark.type = charge_hub_mark.POINTS;
    charge_hub_mark.pose.orientation.w =1.0;
    charge_hub_mark.scale.x = 0.04; 
    charge_hub_mark.scale.y = 0.04; 	
    charge_hub_mark.color.r = 154.0/255.0;	
    charge_hub_mark.color.g = 50.0/255.0;
    charge_hub_mark.color.b = 205.0/255.0;
    charge_hub_mark.color.a=1.0;

    point_mark.action =point_mark.MODIFY;
    point_mark.ns = "markers";
    point_mark.id = 0;
    point_mark.type = point_mark.POINTS;
    point_mark.pose.orientation.w =1.0;
    point_mark.scale.x = 0.04; 
    point_mark.scale.y = 0.04; 	
    point_mark.color.r = 50.0/255.0;	
    point_mark.color.g = 200.0/255.0;
    point_mark.color.b = 150.0/255.0;
    point_mark.color.a = 1.0;    
#endif  
//=====================================================================================

	while(ros::ok())
	{
        //pub
        if(!charge_info.data.empty())
        {
            pub.publish(charge_info);
        }
#if VISUAL        
//        pub_point_marker.publish(point_mark);
        pub_charge_marker.publish(charge_hub_mark);
#endif
        ros::spinOnce();
		loop_rate.sleep();             //按照循环速率延时
	}
	return 0;

}