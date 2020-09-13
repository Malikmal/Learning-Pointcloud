#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/crop_box.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/visualization/pcl_visualizer.h>


float minX = -30, maxX = 20;
float minY = -30, maxY = 10;
float minZ = -10, maxZ = 250;

int main(int argc, char** argv)
{
    std::cout << "This cropping area pcd node." << std::endl;
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr body (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr bodyFiltered(new pcl::PointCloud<pcl::PointXYZRGB>);
    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>("convert_file_ascii.pcd", *body) == -1)
    {
        PCL_ERROR("File not found !! \n");
        return (-1);
    }

    pcl::CropBox<pcl::PointXYZRGB> boxFilter;
    boxFilter.setMin(Eigen::Vector4f(minX, minY, minZ, 1.0f));
    boxFilter.setMax(Eigen::Vector4f(maxX, maxY, maxZ, 1.0f));
    boxFilter.setInputCloud(body);
    boxFilter.filter(*bodyFiltered);

    pcl::io::savePCDFile("pcd_cropping.pcd", *bodyFiltered);
    std::cerr << "pcd_cropping.pcd created. " << bodyFiltered->size() << " data points to File." << std::endl;

    viewer.addPointCloud(bodyFiltered, "body");
    viewer.spin();

    return 0;

}
