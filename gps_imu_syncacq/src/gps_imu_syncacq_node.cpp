// gps_imu_syncacq_node.cpp
/* 同步gps和imu的数据，并发布同步后的gps和imu信息 */

#include <iostream>
#include <math.h>
#include <ros/ros.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>

#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/NavSatFix.h"
#include "sensor_msgs/Imu.h"

std::string img_topic = "/img_syncacq";
std::string point_topic = "/points_syncacq";    // 如果需要同步图像和点云信息，请依次添加
std::string gps_topic = "/gps_syncacq";
std::string imu_topic = "/imu_syncacq";

//rosbag::Bag bag_record;//文件直接记录


ros::Publisher gps_pub;
ros::Publisher imu_pub;
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::NavSatFix, sensor_msgs::Imu> gps_imu_SyncPolicy;   // 定义topic同步策略

//回调函数
void callback(const sensor_msgs::NavSatFixConstPtr &gps, const sensor_msgs::ImuConstPtr &imu)  // 回调中包含多个消息，用以发布同步后的topic
{
    //以实时发布的方式发布
    gps_pub.publish(*gps);
    imu_pub.publish(*imu);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "gps_imu_syncacq_node");
    ros::NodeHandle n;

    //发布的话题
    gps_pub = n.advertise<sensor_msgs::NavSatFix>(gps_topic, 1000);
    imu_pub = n.advertise<sensor_msgs::Imu>(imu_topic, 1000);

    //订阅的话题
    message_filters::Subscriber<sensor_msgs::NavSatFix> gps_sub(n, "/gps/fix", 1);    // 需要同步的topic1输入
    message_filters::Subscriber<sensor_msgs::Imu> imu_sub(n, "/imu_raw", 1);    // 需要同步的topic2输入

    message_filters::Synchronizer<gps_imu_SyncPolicy> sync(gps_imu_SyncPolicy(10), gps_sub, imu_sub);   // 同步
    sync.registerCallback(boost::bind(&callback, _1, _2));    // 同步之后才会调用回调函数

    ros::spin();
    ros::shutdown();

    return 0;
}
