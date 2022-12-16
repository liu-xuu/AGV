#ifndef MYAGV_H
#define MYAGV_H

#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/transform_broadcaster.h>
#include <boost/asio.hpp>
#include <sensor_msgs/Imu.h>


//#define sampleFreq	20.5f				// sample frequency in Hz
#define twoKpDef	1.0f				// (2.0f * 0.5f)	// 2 * proportional gain
#define twoKiDef	0.0f				// (2.0f * 0.0f)	// 2 * integral gain



class MyAGV
{
public:
	MyAGV();
	~MyAGV();
	bool init();
	float invSqrt(float number);
	bool execute(double linearX, double linearY, double angularZ);
    void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	void publisherOdom();
	void publisherImuSensor();

private:
	bool readSpeed();
	void writeSpeed(double movex, double movey, double rot);
	void restore();
	void restoreRun();

	ros::Time currentTime, lastTime;

	double x;
	double y;
	double theta;

	double vx;
	double vy;
	double vtheta;

	double ax;
	double ay;
	double az;

	double wx;
	double wy;
	double wz;

	float sampleFreq;
    sensor_msgs::Imu imu_data;
	ros::NodeHandle n;
	ros::Publisher pub_odom,pub_v,pub_imu,pub;
	tf::TransformBroadcaster odomBroadcaster;
};


#endif // !MYAGV_H
