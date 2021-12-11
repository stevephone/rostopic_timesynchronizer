cmake_minimum_required(VERSION 3.0.2)
project(gps_imu_syncacq)

find_package(catkin REQUIRED COMPONENTS
  message_filters
  sensor_msgs
  std_msgs
  roscpp
  rospy
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(gps_imu_syncacq_node src/gps_imu_syncacq_node.cpp)
target_link_libraries(gps_imu_syncacq_node ${catkin_LIBRARIES})