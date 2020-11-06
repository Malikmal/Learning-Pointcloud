#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

cv::Mat acquiredImage;

void imageShow(const cv::Mat image){
    cv::imshow("IMG RS", image);
    cv::waitKey(30);
	// try{
	// }
	// catch (cv_bridge::Exception& e){
	// 	ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
	// }
}

void imageAcquirerReceive(const sensor_msgs::ImageConstPtr& msg){
	acquiredImage = cv::Mat(cv_bridge::toCvShare(msg, "bgr8")->image);
    cv::rotate(acquiredImage, acquiredImage, cv::ROTATE_180);
    // cv::Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    // cv::Mat rot = cv::getRotationMatrix2D(center, /*angle :*/ 90, 1.0);

    // cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
	imageShow(acquiredImage);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "ROSimgShow");
	ros::NodeHandle nh;
	cv::namedWindow("IMG RS");
	cv::startWindowThread();
	
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("/RSimgAcquisition", 1, imageAcquirerReceive);
	
	ros::spin();
	cv::destroyWindow("view");
}