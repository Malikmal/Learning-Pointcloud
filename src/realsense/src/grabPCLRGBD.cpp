#include <librealsense2/rs.hpp>
#include <iostream>
#include <sstream>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


// PCL Headers
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <boost/thread/thread.hpp>
#include <pcl/io/io.h>
#include <pcl/visualization/cloud_viewer.h>

using namespace std;

typedef pcl::PointXYZRGB RGB_Cloud;
typedef pcl::PointCloud<RGB_Cloud> point_cloud;
typedef point_cloud::Ptr cloud_pointer;
typedef point_cloud::Ptr prevCloud;

//======================================================
// RGB Texture
// - Function is utilized to extract the RGB data from
// a single point return R, G, and B values. 
// Normals are stored as RGB components and
// correspond to the specific depth (XYZ) coordinate.
// By taking these normals and converting them to
// texture coordinates, the RGB components can be
// "mapped" to each individual point (XYZ).
//======================================================
std::tuple<int, int, int> RGB_Texture(rs2::video_frame texture, rs2::texture_coordinate Texture_XY)
{
    // Get Width and Height coordinates of texture
    int width  = texture.get_width();  // Frame width in pixels
    int height = texture.get_height(); // Frame height in pixels
    
    // Normals to Texture Coordinates conversion
    int x_value = min(max(int(Texture_XY.u * width  + .5f), 0), width - 1);
    int y_value = min(max(int(Texture_XY.v * height + .5f), 0), height - 1);

    int bytes = x_value * texture.get_bytes_per_pixel();   // Get # of bytes per pixel
    int strides = y_value * texture.get_stride_in_bytes(); // Get line width in bytes
    int Text_Index =  (bytes + strides);

    const auto New_Texture = reinterpret_cast<const uint8_t*>(texture.get_data());
    
    // RGB components to save in tuple
    int NT1 = New_Texture[Text_Index];
    int NT2 = New_Texture[Text_Index + 1];
    int NT3 = New_Texture[Text_Index + 2];

    return std::tuple<int, int, int>(NT1, NT2, NT3);
}

//===================================================
//  PCL_Conversion
// - Function is utilized to fill a point cloud
//  object with depth and RGB data from a single
//  frame captured using the Realsense.
//=================================================== 
cloud_pointer PCL_Conversion(const rs2::points& points, const rs2::video_frame& color){

    // Object Declaration (Point Cloud)
    cloud_pointer cloud(new point_cloud);

    // Declare Tuple for RGB value Storage (<t0>, <t1>, <t2>)
    std::tuple<uint8_t, uint8_t, uint8_t> RGB_Color;

    //================================
    // PCL Cloud Object Configuration
    //================================
    // Convert data captured from Realsense camera to Point Cloud
    auto sp = points.get_profile().as<rs2::video_stream_profile>();
    
    cloud->width  = static_cast<uint32_t>( sp.width()  );   
    cloud->height = static_cast<uint32_t>( sp.height() );
    cloud->is_dense = false;
    cloud->points.resize( points.size() );

    auto Texture_Coord = points.get_texture_coordinates();
    auto Vertex = points.get_vertices();

    // Iterating through all points and setting XYZ coordinates
    // and RGB values
    for (int i = 0; i < points.size(); i++)
    {   
        //===================================
        // Mapping Depth Coordinates
        // - Depth data stored as XYZ values
        //===================================
        cloud->points[i].x = Vertex[i].x;
        cloud->points[i].y = Vertex[i].y;
        cloud->points[i].z = Vertex[i].z;

        // Obtain color texture for specific point
        RGB_Color = RGB_Texture(color, Texture_Coord[i]);

        // Mapping Color (BGR due to Camera Model)
        cloud->points[i].r = get<2>(RGB_Color); // Reference tuple<2>
        cloud->points[i].g = get<1>(RGB_Color); // Reference tuple<1>
        cloud->points[i].b = get<0>(RGB_Color); // Reference tuple<0>

    }
    
   return cloud; // PCL RGB Point Cloud generated
}

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
	// / Declare pointcloud object, for calculating pointclouds and texture mappings
    rs2::pointcloud pc;

	RSConfig.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    RSConfig.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

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
		auto depth = rs_Frameset.get_depth_frame();
		auto RGB = rs_Frameset.get_color_frame();
		
		// acquiredImage = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)rs_Frame.get_data(), cv::Mat::AUTO_STEP);

		// imageMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", acquiredImage).toImageMsg();
		// imgpub.publish(imageMsg);

		// std::cout << "Acquire Computation Time: " << (double)((clock()-clockstart)/CLOCKS_PER_SEC) << " ms" << std::endl;

		// ros::spinOnce();



		// cv::imshow("test", acquiredImage);
		// if(cv::waitKey(30) == 27)
		// {
		// 	break;
		// }
		pc.map_to(RGB);
		auto points = pc.calculate(depth);

        cloud_pointer clouda = PCL_Conversion(points, RGB);


		//==========================
		// Pointcloud Visualization
		//==========================
		// Create viewer object titled "Captured Frame"
		boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Captured Frame"));

		// Set background of viewer to black
		viewer->setBackgroundColor (0, 0, 0); 
		// Add generated point cloud and identify with string "Cloud"
		viewer->addPointCloud<pcl::PointXYZRGB> (clouda, "Cloud");
		// Default size for rendered points
		viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "Cloud");
		// Viewer Properties
		viewer->initCameraParameters();  // Camera Parameters for ease of viewing

		cout << endl;
		cout << "Press [Q] in viewer to continue. " << endl;
		
		viewer->spin(); // Allow user to rotate point cloud and view it

		// Note: No method to close PC visualizer, pressing Q to continue software flow only solution.
	
	}

	return EXIT_SUCCESS;
}