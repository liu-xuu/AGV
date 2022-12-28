//.hÍ·ÎÄ¼þÖÐÏà¹Ø¶¨Òå
#include <tf/transform_listener.h>

struct state
{
    float x;
    float y;
    float yaw;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "record_pose");
    ros::NodeHandle n, turtle_node;
    tf::TransformListener listener;

    state robot_pose;
    tf::StampedTransform transform;
    while (n.ok())
    {
        try
        {
            listener.waitForTransform("map", "base_footprint", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("/map", "/base_footprint", ros::Time(0), transform);

        }
        catch (tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        double roll, pitch, yaw;
        tf::Matrix3x3(transform.getRotation()).getEulerYPR(yaw, pitch, roll);

        // tf::Quaternion quat;
        // tf::quaternionMsgToTF(odom_msg.pose.pose.orientation,quat);
        // double roll,pitch,yaw;
        // tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);

        robot_pose.x = transform.getOrigin().x();
        robot_pose.y = transform.getOrigin().y();
        robot_pose.yaw = yaw;

        ROS_INFO("robot pose x: %f", robot_pose.x);
        ROS_INFO("robot pose y: %f", robot_pose.y);
        ROS_INFO("robot pose yaw: %f", robot_pose.yaw);
        return 0;
    }
}

