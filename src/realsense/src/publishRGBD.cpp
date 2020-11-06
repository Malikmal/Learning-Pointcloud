#include <librealsense2/rs.hpp>
#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointXYZRGB XYZRGB;
typedef pcl::PointCloud<XYZRGB> pclXYZRGB;
typedef pcl::PointCloud<XYZRGB>::Ptr pclXYZRGBptr;

inline float PackRGB(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color_uint = ((uint32_t)r << 16 | (uint32_t) g << 8 | (uint32_t)b);
  return *reinterpret_cast<float*>(&color_uint);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "ROSgrabRGB");
	ros::NodeHandle nh;
	ros::Publisher pclpub = nh.advertise<sensor_msgs::PointCloud2>("/RSpclAcquisition", 1);

	image_transport::ImageTransport it(nh);
	image_transport::Publisher imgpub = it.advertise("/RSimgAcquisition", 1);
	
	sensor_msgs::PointCloud2Ptr cloudMsg (new sensor_msgs::PointCloud2());
	sensor_msgs::ImagePtr imageMsg;

	pclXYZRGBptr acquiredCloud(new pclXYZRGB);
	cv::Mat acquiredImage;

	rs2::pipeline RSCamera;
	rs2::config RSConfig;
	rs2::pointcloud rs_MatCloud;
	rs2::points rs_Points;
	rs2::frame rs_Frame;

	RSConfig.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
    RSConfig.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

	clock_t clockstart;

	RSCamera.start(RSConfig);

	// Camera warmup - dropping several first frames to let auto-exposure stabilize
	for(int i = 0; i < 30; i++){
		//Wait for all configured streams to produce a frame
		RSCamera.wait_for_frames();
	}
	
	acquiredCloud->width = 640;
	acquiredCloud->height = 480;
	acquiredCloud->points.resize(acquiredCloud->width * acquiredCloud->height);
	acquiredCloud->is_dense = false;
	
	while (ros::ok()) {
		clockstart = clock();
		
		acquiredImage = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)RSCamera.wait_for_frames().get_color_frame().get_data(), cv::Mat::AUTO_STEP);
		
		auto ptr = rs_MatCloud.calculate(RSCamera.wait_for_frames().get_depth_frame()).get_vertices();
		for (auto& it : acquiredCloud->points){
			it.x = ptr->x;
			it.y = ptr->y;
			it.z = ptr->z;
			it.rgb = PackRGB(127, 127, 127);
			ptr++;
		}
		
		pcl::toROSMsg(*acquiredCloud, *cloudMsg);
		imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", acquiredImage).toImageMsg();
		pclpub.publish(cloudMsg);
		imgpub.publish(imageMsg);

		std::cout << "Acquire Computation Time: " << (double)(clock()-clockstart)/CLOCKS_PER_SEC << " ms" << std::endl;

		ros::spinOnce();
	}

	return EXIT_SUCCESS;
}