sukai 2022-08-29 
我用的系统环境ros-noetic，其它环境可以自己测一下，应该没问题；
我用的imu是轮趣科技提供的一款imu 型号N100
项目里面有这款imu的驱动
这个扩展滤波器是我已经魔改好的，把topic对上就直接使用 具体看robot_pose_ekf.launch
  <param name="output_frame" value="odom"/> <!--里程计坐标 -->
  <param name="base_footprint_frame" value="base_link"/> <!-- 小车坐标 -->
   <param name="odom_data" value="odom_to_ekf"/> <!-- 订阅 /odom_to_ekf 程计数据 -->
    <param name="imu_data" value="imu_data"/><!-- 订阅 /imu_data 数据  -->
 <remap from="/robot_pose_ekf/odom_combined" to="/odom" /><!-- 发布融合后的 /odom 里程计 数据  -->
=============================================================================================
一.改里程计代码
	1.把里程计发布的坐标注释掉
            //todo sukai 做imu与扩展卡尔曼滤波器融合时历程计计算的代码中要把发布tf坐标的代码需要注释掉
            //odomBroadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));
	2.改topic名
	    //导航用 sukai
            pubOdom = nh.advertise<nav_msgs::Odometry>("/odom_to_ekf", 5);
	  不改代码中topic名的话就在launch中加入以下语句：
		<remap from="odom" to="odom_to_ekf"/>

二.imu中的发布imu数据的topic名知否与扩展卡尔曼滤波器订阅的一致
    <param name="imu_data" value="imu_data"/><!-- 订阅 /imu_data 数据  -->
三.imu 的安装坐标 【这一部份在视频讲解里漏了】
   （下面2选1）
   3.1可以配置在urdf里
		  <link name="imu_link">
		    <visual>
		      <geometry>
			<cylinder length="0.0625" radius="0.04" />
		      </geometry>
		      <material name="gray" />
		    </visual>
		  </link>

		  <joint name="imu_link_joint" type="fixed">
		    <parent link="base_link" /> 
		    <child link="imu_link" />
		    <origin xyz="0.0 0.0 0.15 " rpy="0.0 0.0 0"/>   
		 </joint>
   3.2也可以发布静态坐标的方式
      
	  <!-- ros tf -->
	  <node pkg="tf2_ros" type="static_transform_publisher" name="imu_to_base_link" args="-0.185 0.017 0 -1.571 0 0  /base_link /imu_link"/>

=================================================================================================
编译 
编译扩展卡尔曼滤波器 robot_pose_ekf
# 1.进入 robot_pose_ekf 文件夹之后，运行
 catkin_make
解决编译“robot_pose_ekf”package时遇到的问题:No package 'orocos-bfl' found 

git clone https://salsa.debian.org/science-team/orocos-bfl.git  【代码中已有克隆好的包】

# 2. 解压源代码后，编译安装
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install


# 3.启动：
3.1启动里程计
   roslaunch ***** ****.launch
3.2启动imu
   roslaunch imu imu_driver.launch
3.3启动 扩展卡尔曼滤波器
   roslaunch robot_pose_ekf robot_pose_ekf.launch
3.4 查看是否启动成功
    rosservice call /robot_pose_efk/get_status 
3.5 查看Odometry sensor和IMU sensor 是否is used ，is active来确保ekf包的是否正确使用
    rosrun rqt_tf_tree rqt_tf_tree


---------------------------------------------

ERROR
-- Looking for Cppunit - not found
-- You will not be able to build tests. To build tests, first set the path where cppunit can be found using CMAKE_INCLUDE_PATH and CMAKE_LIBRARY_PATH.
svn: E155007: “/home/sukai/3rdparty/orocos-bfl”不是工作副本
1. 安装libcppunit-dev （sudo apt-get install libcppunit-dev 或者类似的包)


