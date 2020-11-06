#include <librealsense2/rs.hpp>
#include <iostream>
#include <sstream>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointXYZRGB XYZRGB;
typedef pcl::PointCloud<XYZRGB> pclXYZRGB;
typedef pcl::PointCloud<XYZRGB>::Ptr pclXYZRGBptr;
typedef pcl::PointCloud<XYZRGB>::ConstPtr pclXYZRGBcptr;

inline float PackRGB(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color_uint = ((uint32_t)r << 16 | (uint32_t) g << 8 | (uint32_t)b);
  return *reinterpret_cast<float*>(&color_uint);
}

int main(int argc, char **argv){
	ros::init(argc, argv, "grabDepth");
	ros::NodeHandlePtr nh(new ros::NodeHandle());
	ros::Publisher pclpub = nh->advertise<sensor_msgs::PointCloud2>("/RSpclAcquisition", 1);

	sensor_msgs::PointCloud2Ptr cloudMsg (new sensor_msgs::PointCloud2());
	pclXYZRGBptr acquiredCloud(new pclXYZRGB);

	rs2::pipeline RSCamera;
	rs2::pointcloud rs_MatCloud;
	rs2::points rs_Points;
	clock_t clockstart;

	RSCamera.start();

	acquiredCloud->width = 640;
	acquiredCloud->height = 480;
	acquiredCloud->points.resize(acquiredCloud->width * acquiredCloud->height);
	acquiredCloud->is_dense = false;
	//acquiredCloud->points.resize(rs_Points.size());

	while (ros::ok()) {
		clockstart = clock();

		rs_Points = rs_MatCloud.calculate(RSCamera.wait_for_frames().get_depth_frame());
		//acquiredCloud = rs_Point_to_pcl(rs_Points);

		auto ptr = rs_Points.get_vertices();
		for (auto& it : acquiredCloud->points){
			it.x = ptr->x;
			it.y = ptr->y;
			it.z = ptr->z;
			it.rgb = PackRGB(127, 127, 127);
			ptr++;
		}

		pcl::toROSMsg(*acquiredCloud, *cloudMsg);
		pclpub.publish(cloudMsg);

		std::cout << "Acquire Computation Time: " << (double)((clock()-clockstart)/CLOCKS_PER_SEC) << " ms" << std::endl;
	}

	return EXIT_SUCCESS;
}