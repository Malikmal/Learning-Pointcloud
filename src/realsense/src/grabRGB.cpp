#include <librealsense2/rs.hpp>
#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv){
	ros::init(argc, argv, "grabRGB");
	ros::NodeHandle nh;

	image_transport::ImageTransport it(nh);
	image_transport::Publisher imgpub = it.advertise("camera/image", 1);

	sensor_msgs::ImagePtr imageMsg;

	cv::Mat acquiredImage;

	rs2::pipeline RSCamera;
	rs2::config RSConfig;
	rs2::frameset rs_Frameset;
	rs2::frame rs_Frame;

	RSConfig.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

	clock_t clockstart;

	RSCamera.start(RSConfig);

	// Camera warmup - dropping several first frames to let auto-exposure stabilize
	for(int i = 0; i < 30; i++){
		//Wait for all configured streams to produce a frame
		rs_Frameset = RSCamera.wait_for_frames();
	}

	while (ros::ok()) {
		clockstart = clock();
		rs_Frameset = RSCamera.wait_for_frames();
		rs_Frame = rs_Frameset.get_color_frame();
		acquiredImage = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)rs_Frame.get_data(), cv::Mat::AUTO_STEP);

		imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", acquiredImage).toImageMsg();
		imgpub.publish(imageMsg);

		std::cout << "Acquire Computation Time: " << (double)((clock()-clockstart)/CLOCKS_PER_SEC) << " ms" << std::endl;

		ros::spinOnce();
	}

	return EXIT_SUCCESS;
}