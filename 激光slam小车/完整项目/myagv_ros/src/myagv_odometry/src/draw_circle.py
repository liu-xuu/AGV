#!/usr/bin/python
import rospy
from geometry_msgs.msg import Twist

def cmd_vel_pub():
    rospy.init_node('draw_circle',anonymous=False)
    cmd_pub = rospy.Publisher('cmd_vel',Twist,queue_size=10)
    rate = rospy.Rate(10)
    twist = Twist()
    rospy.loginfo('Start Control Robot Draw a Circle')

    while not rospy.is_shutdown():
        twist.linear.x = 0.2
        twist.angular.z = 0.4
        cmd_pub.publish(twist)
        rate.sleep()

if  __name__ == '__main__':
    try:   cmd_vel_pub()
    except rospy.ROSInternalException:   pass

