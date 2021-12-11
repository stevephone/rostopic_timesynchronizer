# rostopic_timesynchronizer
在自动驾驶中，经常遇到不同传感器数据需要时间同步的问题，在此记录。

本文主要参考了http://wiki.ros.org/message_filters（官方教程yyds）

本文主要实现了gps和imu的数据时间同步，要实现图像和lidar的同步，只需修改「同步策略」即可，使用如下：

(1)编译源码
mkdir -p ~/catkin_ws/src

cd ~/mkdir_ws/

catkin_make

cd ~/catkin_ws/src

git clone https://github.com/stevephone/rostopic_timesynchronizer

cd ~/catkin_ws/

catkin_make

(2)启动同步节点

rosrun gps_imu_syncacq gps_imu_syncacq_node

同步后的topic分别是：/gps_syncacq和/imu_syncacq

(3)可使rosbag record -o test.bag /gps_syncacq /imu_syncacq录制bag数据，通过rqt_bag查看同步结果。

