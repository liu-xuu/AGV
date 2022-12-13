robot_pose_ekf [![Build Status](https://travis-ci.com/ros-planning/robot_pose_ekf.svg?branch=master)](https://travis-ci.org/ros-planning/robot_pose_ekf)
========================================================================================================================================================
odom_estimation_node.cpp imu_data

rosservice call /robot_pose_efk/get_status 查看是否启动成功
查看Odometry sensor和IMU sensor 是否is used ，is active来确保ekf包的是否正确使用
rosrun rqt_tf_tree rqt_tf_tree
=============================================================================================
解决编译“robot_pose_ekf”package时遇到的问题:No package 'orocos-bfl' found 

https://www.jianshu.com/p/0c300b8a6a44#comments

https://salsa.debian.org/science-team/orocos-bfl

git clone https://salsa.debian.org/science-team/orocos-bfl.git

# 2. 解压源代码后，编译安装
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
# 拷贝头文件到/usr/local/include/ocl
# 拷贝库文件到/usr/local/lib/
# 拷贝orocos-bfl.pc到usr/local/lib/pkgconfig/orocos-bfl.pc

3.编译robot_pose_ekf
# 进入catkin_ws文件夹之后，运行
$ catkin_make


请问为什么要做这3步，我不做这3步也编译过了
暂时不做以下3步配置
# 拷贝头文件到/usr/local/include/ocl
# 拷贝库文件到/usr/local/lib/
# 拷贝orocos-bfl.pc到usr/local/lib/pkgconfig/orocos-bfl.pc
---------------------------------------------

ERROR
-- Looking for Cppunit - not found
-- You will not be able to build tests. To build tests, first set the path where cppunit can be found using CMAKE_INCLUDE_PATH and CMAKE_LIBRARY_PATH.
svn: E155007: “/home/iimt/3rdparty/orocos-bfl”不是工作副本

有两种办法
1. 安装libcppunit-dev （sudo apt-get install libcppunit-dev 或者类似的包)
2. 调用cmake时使用参数，cmake -DENABLE_TESTS=OFF
然后，需要安装fmod,嘿嘿，自己去http://www.fmod.org/index.php/download找一个对应版本，解压后读读README或者INSTALL，看看怎么装的。我不知道ubuntu可不可以用apt-get装这个。
ps: 从楼主的问题看，主要问题就是解决依赖性问题。这个在Unix下是很常见，不过对新手来说是有点麻烦了，建议仔细阅读你要安装的软件下的README或者INSTALL，或者官网的faq，以解决一般性问题，长此以往碰得多了，也就不成问题了。
所以，ubuntu才会推出具有超级牛力的apt，一般的软件，还是直接apt-get吧，它会自动帮你解决依耐性问题的。

