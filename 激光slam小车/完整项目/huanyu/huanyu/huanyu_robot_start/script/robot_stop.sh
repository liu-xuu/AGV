source /opt/ros/melodic/setup.bash
source /home/huike/robot_ws/devel/setup.bash
export ROS_MASTER_URI=http://192.168.12.1:11311
export ROS_HOSTNAME=192.168.12.1

LOGPATH=/home/huike/Documents/autostart_stop.log
echo '--------------stop-----------------------' >> $LOGPATH
echo `date` >> $LOGPATH

for i in $(rosnode list);do
    rosnode kill $i;
done
killall roslaunch
killall roscore
sleep 2
echo `date` >> $LOGPATH
echo 'stop end' >> $LOGPATH

exit 0 #执行完要结束进程
