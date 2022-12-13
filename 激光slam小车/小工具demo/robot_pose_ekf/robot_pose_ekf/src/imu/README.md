
## fdilink的imu驱动包
Deta-10-ros-v0.0.1
### 依赖：
```bash
sudo apt install ros-noetic-serial
```
./imu.sh
### 使用：    
roslaunch imu imu_driver.launch
roslaunch imu tf.launch

发布的imu话题名: /imu_data

    
发布的imu话题中的frame_id: imu_link

ubuntu改串口号
https://blog.csdn.net/xinmei4275/article/details/88620984?spm=1001.2014.3001.5506
====================================
仿真
输入 /imu
输出 /imu/data
输入    /odom
======================================



1. 串口信息查询
查看有哪些串口

python3 -m serial.tools.list_ports 
查看串口信息,测试了发现没有USB串口独立的特征信息, 唯一一个不变的3-3:1.0, 而这个实际上是代表电脑上这个USB口编号,也就是说只是连在这个USB端口上的串口都叫这个ID.

udevadm info /dev/ttyUSB0
1
2. 创建配置文件
创建规则, 文件名称随意.其中配置文件有两种方式,各有缺点

2.1 绑定USB端口号
sudo vi /etc/udev/rules.d/com_port.rules
1
内容, KERNELS表示硬件的usb接口名,不同编号,表示不同的usb接口.
下面是添加修改了三个USB端口

ACTION=="add",KERNELS=="1-1.2:1.0",SUBSYSTEMS=="usb",MODE:="0777",SYMLINK+="imu"
ACTION=="add",KERNELS=="3-3:1.0",SUBSYSTEMS=="usb",MODE:="0777",SYMLINK+="lidar"
ACTION=="add",KERNELS=="3-2:1.0",SUBSYSTEMS=="usb",MODE:="0777",SYMLINK+="my_serial3"
查看变换后的情况

ll /dev | grep ttyUSB
缺点: 只要是插到这个USB端口的串口都会被改为指定名.

2.2 绑定USB串口号
查看设备ID

lsusb
例如第四行的那个ID 10c4:ea60表示TTRS{idVendor}==10c4, ATTRS{idProduct}==ea60

sudo vi /etc/udev/rules.d/com_port.rules
1
内容, KERNELS表示硬件的usb主分类,.
下面是添加修改了两个个USB端口

KERNEL==”ttyUSB*”, ATTRS{idVendor}==”10c4”, ATTRS{idProduct}==”ea60”, MODE:=”0666”, SYMLINK+=”lidar”
KERNEL==”ttyUSB*”, ATTRS{idVendor}==”1a86”, ATTRS{idProduct}==”7523”, MODE:=”0666”, SYMLINK+=”base”
1
2
缺点: 当两个串口芯片相同时会出现ID完全相同的情况, 例如上图的两个串口芯片都为
Cygnal Integrated Products, Inc. CP210x UART Bridge / myAVR mySmartUSB light
ID也都为10c4:ea60.



```
<launch>
  <node pkg="fdilink_ahrs" name="ahrs_driver" type="ahrs_driver" output="screen" >
    <!-- 是否输出debug信息 -->
    <param name="debug"  value="false"/>
    
    <!-- 串口设备，可通过rules.d配置固定 -->
    <param name="port"  value="/dev/ttyUSB0"/>
    <!-- <param name="port"  value="/dev/ttyTHS1"/> -->

    <!-- 波特率 -->
    <param name="baud"  value="921600"/>

    <!-- 发布的imu话题名 -->
    <param name="imu_topic"  value="/imu"/>
    
    <!-- 发布的imu话题中的frame_id -->
    <param name="imu_frame"  value="imu"/>

    <!-- 地磁北的yaw角 --> # 二维指北的朝向，北为0，逆时针增加，0~2π的取值范围。
    <param name="mag_pose_2d_topic"  value="/mag_pose_2d"/>

    <!-- 发布的数据基于不同设备有不同的坐标系   -->
    <param name="device_type"  value="1"/> <!-- 0: origin_data, 1: for single imu or ucar in ROS, 2:for Xiao in ROS -->
  </node>
</launch> 
```
  其中`device_type`：
  
  0. Deta-10的原始坐标系模式
  1. 单独imu的坐标系模式

调用的ahrs_driver节点会发布`sensor_msgs/Imu`格式的imu topic。
```
std_msgs/Header header
  uint32 seq
  time stamp
  string frame_id
geometry_msgs/Quaternion orientation
  float64 x
  float64 y
  float64 z
  float64 w
float64[9] orientation_covariance
geometry_msgs/Vector3 angular_velocity
  float64 x
  float64 y
  float64 z
float64[9] angular_velocity_covariance
geometry_msgs/Vector3 linear_acceleration
  float64 x
  float64 y
  float64 z
float64[9] linear_acceleration_covariance
```
也会发布`geometry_msgs/Pose2D`格式的二维指北角话题，话题名默认为`/mag_pose_2d`。
```
float64 x
float64 y
float64 theta  # 指北角
```

### 2020-1-15
  维护了文件注释。

### 2020-10-20
  添加了`device_type`参数，可以在`ahrs_driver.launch`文件中指定设备类型，根据不同设备类型以不同的坐标系发布ROS的imu数据。
  其中：

  0. Deta-10的原始坐标系模式
  1. 单独imu的坐标系模式
