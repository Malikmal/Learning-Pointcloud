#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


#include <pcl/common/common_headers.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl_conversions/pcl_conversions.h>

using namespace std;

cv::Mat acquiredImage, acquiredImageRotated;

typedef pcl::PointXYZRGB XYZRGB;
typedef pcl::PointCloud<XYZRGB> pclXYZRGB;
typedef pcl::PointCloud<XYZRGB>::Ptr pclXYZRGBptr;
typedef pcl::PointCloud<XYZRGB>::ConstPtr pclXYZRGBcptr;

ros::Publisher pclpub;
ros::Subscriber pclsub;
ros::Subscriber strsub;

pclXYZRGBptr acquiredCloud (new pclXYZRGB());


inline float PackRGB(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color_uint = ((uint32_t)r << 16 | (uint32_t) g << 8 | (uint32_t)b);
  return *reinterpret_cast<float*>(&color_uint);
}

std::shared_ptr<pcl::visualization::PCLVisualizer> createXYZRGBVisualizer(pclXYZRGBcptr cloud) {
  std::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("PCL ZED 3D Viewer"));
  viewer->setBackgroundColor(0.12, 0.12, 0.12);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB>(cloud, rgb);
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.5);
  viewer->addCoordinateSystem(1.0);
  viewer->initCameraParameters();
  return (viewer);
}

std::shared_ptr<pcl::visualization::PCLVisualizer> viewer = createXYZRGBVisualizer(acquiredCloud);


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
    cv::rotate(acquiredImage, acquiredImageRotated, cv::ROTATE_180);
	// imageShow(acquiredImage);
}

void cloudAcquirerReceive(const sensor_msgs::PointCloud2ConstPtr& cloudInMsg){
  pcl::fromROSMsg(*cloudInMsg, *acquiredCloud);
    // cv::Mat img = cv::imread("lenna.png");
    // std::vector<cv::Mat> three_channels ; 
    // cv::split(acquiredImage, three_channels);
    // cout << three_channels[0].at<uchar>(1,1) << endl;
    int i = 640, j = 480, k;
    // i = j = k = 0;

    // cv::rotate(acquiredImage, acquiredImage, cv::ROTATE_180);


  for (auto& it : acquiredCloud->points){
        it.x = it.x;
        it.y = it.y;
        it.z = it.z;
        // it.b = acquiredImageRotated.at<cv::Vec3b>(j,i)[0];
        // it.g = acquiredImageRotated.at<cv::Vec3b>(j,i)[1];
        // it.r = acquiredImageRotated.at<cv::Vec3b>(j,i)[2];

        it.rgb = PackRGB(
            acquiredImageRotated.at<cv::Vec3b>(j,i)[2],  //r
            acquiredImageRotated.at<cv::Vec3b>(j,i)[1], // g
            acquiredImageRotated.at<cv::Vec3b>(j,i)[0]  //b
        ); //acquiredImage explode
        i--;
        if(i <= 0) 
        {
            i=640;
            j--;
        }
        if(j < 0)
        {
            break;
        }
        // cout <<
        //  << (uint8_t)acquiredImage.at<cv::Vec3b>(it.y,it.x)[2]  
        //  << (uint8_t)acquiredImage.at<cv::Vec3b>(it.y,it.x)[1]  
        //  << (uint8_t)acquiredImage.at<cv::Vec3b>(it.y,it.x)[0] 
        //  << endl;
    }
  viewer->updatePointCloud(acquiredCloud);
  viewer->spinOnce();
}



int main(int argc, char **argv){
	ros::init(argc, argv, "ROSimgShow");
    ros::NodeHandlePtr nhp(new ros::NodeHandle());
	ros::NodeHandle nh;
	cv::namedWindow("IMG RS");
	cv::startWindowThread();
	
	image_transport::ImageTransport it(nh);
	image_transport::Subscriber sub = it.subscribe("/RSimgAcquisition", 1, imageAcquirerReceive);
    ros::Subscriber pclsubAcquirer = nhp->subscribe("/RSpclAcquisition", 1, cloudAcquirerReceive);
	
	ros::spin();
	cv::destroyWindow("view");
}