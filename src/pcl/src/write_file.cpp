#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main (int argc, char** argv)
{
    std::cout << "Test writing file pcd" << std::endl;

    pcl::PointCloud<pcl::PointXYZ> cloud; // (new pcl::PointCloud)

    cloud.width = 5;
    cloud.height = 1;
    cloud.is_dense = false;
    cloud.points.resize(cloud.width*cloud.height);

    for(auto& point: cloud)
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    //ascii
    pcl::io::savePCDFileASCII("writing_file_ascii.pcd", cloud);
    std::cerr << "Saved in ASCII Fromat ." << std::endl;


    //binary
    pcl::io::savePCDFileBinary("writing_file_binary.pcd", cloud);
    std::cerr << "Saved in Binary Fromat ." << std::endl;


    //binary compressed
    pcl::io::savePCDFileBinaryCompressed("writing_file_binary_compressed.pcd", cloud);
    std::cerr << "Saved in binary compressed Fromat ." << std::endl;

    return 0;
}