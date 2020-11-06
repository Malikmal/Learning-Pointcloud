//To Prevent Warnings
#ifdef _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <iostream>
#include <sstream>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointXYZRGB XYZRGB;
typedef pcl::PointCloud<XYZRGB> pclXYZRGB;
typedef pcl::PointCloud<XYZRGB>::Ptr pclXYZRGBptr;
typedef pcl::PointCloud<XYZRGB>::ConstPtr pclXYZRGBcptr;

std::shared_ptr<pcl::visualization::PCLVisualizer> createRGBVisualizer(pcl::PointCloud<XYZRGB>::ConstPtr cloud) {
  std::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("PCL RS 3D Viewer"));
  viewer->setBackgroundColor(0.12, 0.12, 0.12);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGB>(cloud, rgb);
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.5);
  viewer->addCoordinateSystem(1.0);
  viewer->initCameraParameters();
  return (viewer);
}

inline float PackRGB(uint8_t r, uint8_t g, uint8_t b) {
  uint32_t color_uint = ((uint32_t)r << 16 | (uint32_t) g << 8 | (uint32_t)b);
  return *reinterpret_cast<float*>(&color_uint);
  //
  // 1111 1111 1111 1111 1111 1111
}

pclXYZRGBptr rs_Point_to_pcl(const rs2::points& rs_Points){
	pclXYZRGBptr acquiredCloud(new pclXYZRGB());
	acquiredCloud->width = rs_Points.get_profile().as<rs2::video_stream_profile>().width();
	acquiredCloud->height = rs_Points.get_profile().as<rs2::video_stream_profile>().height();
	acquiredCloud->is_dense = false;
	acquiredCloud->points.resize(rs_Points.size());

	auto ptr = rs_Points.get_vertices();
	for (auto& it : acquiredCloud->points){
		it.x = ptr->x;
		it.y = ptr->y;
		it.z = ptr->z;
    it.rgb = PackRGB(127, 127, 127);
		ptr++;
	}
	return acquiredCloud;
}

int main(int argc, char **argv){
	rs2::pipeline RSCamera;
	rs2::pointcloud rs_MatCloud;
	rs2::points rs_Points;
	pclXYZRGBptr acquiredCloud (new pclXYZRGB());
	std::shared_ptr<pcl::visualization::PCLVisualizer> viewer = createRGBVisualizer(acquiredCloud);
	RSCamera.start();

	while (!viewer->wasStopped()) { // Application still alive?
		rs_Points = rs_MatCloud.calculate(RSCamera.wait_for_frames().get_depth_frame());
		acquiredCloud = rs_Point_to_pcl(rs_Points);
		viewer->updatePointCloud(acquiredCloud);
		viewer->spinOnce();
	}

	return EXIT_SUCCESS;
}