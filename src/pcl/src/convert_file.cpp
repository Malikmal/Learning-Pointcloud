#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>

int main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr inCloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr outCloud (new pcl::PointCloud<pcl::PointXYZRGB>);

    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>("frame.pcd", *inCloud) == -1)
    {
        PCL_ERROR("Couldn't Find File!!! \n");
        return (-1);
    }

    std::vector<int> nanRemoved;
    pcl::removeNaNFromPointCloud(*inCloud, *outCloud, nanRemoved);

    for(auto& point: *outCloud)
    {
        point.x = point.x * 100;
        point.y = point.y * 100;
        point.z = point.z * 100;
    }

    pcl::io::savePCDFileASCII("convert_file_ascii.pcd", *outCloud);

    std::cerr << "Data has saved as convert_file_ascii.pcd" << std::endl;

    return 0;
}