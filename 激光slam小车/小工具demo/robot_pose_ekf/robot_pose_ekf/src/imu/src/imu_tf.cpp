#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_broadcaster.h>
#include <string>


/* 参考ROS wiki
 * http://wiki.ros.org/tf/Tutorials/Writing%20a%20tf%20broadcaster%20%28C%2B%2B%29
 * */

int position_x ;
int position_y ;
int position_z ;
ros::Time last_time;
double  x ;
double  y ;
double theta;
void ImuCallback(const sensor_msgs::ImuConstPtr& imu_data) {
    static tf::TransformBroadcaster br;//广播器
    tf::Transform transform;
    //transform.setOrigin(tf::Vector3(position_x, position_y, position_z));//设置平移部分
    transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));//设置平移部分
    //从IMU消息包中获取四元数数据
    tf::Quaternion q;
    q.setX(imu_data->orientation.x);
    q.setY(imu_data->orientation.y);
    q.setZ(imu_data->orientation.z);
    q.setW(imu_data->orientation.w);
    q.normalized();//归一化

    transform.setRotation(q);//设置旋转部分
    //广播出去
   // br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "imu"));
    //sukai
      //  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "imu_link"));
              br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "imu_link"));
}



//sukai 这里增加只求2维地图，x线速度与z角速度下的位置
void ImuCallback_me(const sensor_msgs::ImuConstPtr& imu_data) {
    static tf::TransformBroadcaster br;//广播器
    //当前的时间,算时间片 sukai
    ros::Time  current_time = ros::Time::now();





    tf::Transform transform;
   // transform.setOrigin(tf::Vector3(position_x, position_y, position_z));//设置平移部分
    //  x线速度值
    double linear_x = imu_data->linear_acceleration.x;
    //  y线速度值
    double linear_y =imu_data->linear_acceleration.y;
    //  z线速度值
    double linear_z =imu_data->linear_acceleration.z;
    //  x角速度值
    double angular_x =imu_data->angular_velocity.x ;
    //  y角速度值
    double angular_y =imu_data->angular_velocity.y ;
    //  z角速度值
    double angular_z =imu_data->angular_velocity.z ;

    //时间差
    double delta_time = current_time.toSec() - last_time.toSec();
    last_time = current_time;
    //这里只求2维地图，x线速度与z角速度下的位置
    // 计算累加的弧度
    theta = theta + angular_z * delta_time;
   // 时间片的距离, 时间差；
    double delta_x = (linear_x * cos(theta) ) * delta_time;
    double delta_y = (linear_x * sin(theta) )* delta_time;

    x = x +delta_x;
    y =y +delta_y;

    transform.setOrigin(tf::Vector3(x, y, 0.0));//设置平移部分

    //从IMU消息包中获取四元数数据
    tf::Quaternion q;
    q.setX(imu_data->orientation.x);
    q.setY(imu_data->orientation.y);
    q.setZ(imu_data->orientation.z);
    q.setW(imu_data->orientation.w);
    q.normalized();//归一化

    transform.setRotation(q);//设置旋转部分
    //广播出去
   // br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "imu"));
    //sukai
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "imu_link"));
}
int main (int argc, char ** argv) {
    ros::init(argc, argv, "imu_data_to_tf");
    
    
    ros::NodeHandle node;
    //上一次的时间,算时间片 sukai
    last_time = ros::Time::now();
    

    std::string imu_topic;
    
    node.param("/imu_tf/imu_topic", imu_topic, std::string("/imu"));
    node.param("/imu_tf/position_x", position_x, 0);
    node.param("/imu_tf/position_y", position_y, 0);
    node.param("/imu_tf/position_z", position_z, 0);
    
    ros::Subscriber sub = node.subscribe(imu_topic.c_str(), 10, &ImuCallback);

    //sukai 里程计
   //ros::Subscriber sub_me = node.subscribe(imu_topic.c_str(), 10, &ImuCallback_me);


    ros::spin();
    return 0;
}
