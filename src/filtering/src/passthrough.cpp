#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

typedef pcl::PointXYZ PointType;

int main (int argc, char** argv)
{
    pcl::PointCloud<PointType>::Ptr cloud (new pcl::PointCloud<PointType>);
    pcl::PointCloud<PointType>::Ptr cloud_filtered (new pcl::PointCloud<PointType>);
    
    // fill in the cloud
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for(auto& point: *cloud)
    {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    std::cerr << "Cloud before filtering : " << std::endl;
    for(const auto& point: *cloud)
    {
        std::cerr << "    " << point.x << " "
                            << point.y << " "
                            << point.z << std::endl;
    }
    
    //create the filtering object
    pcl::PassThrough<PointType> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    // pass.setFilterLimitsNegative(true);
    pass.filter(*cloud_filtered);

    std::cerr << "cloud after filtering : " << std::endl;
    for (const auto& point : *cloud_filtered)
    {
        std::cerr << "    " << point.x << " "
                            << point.y << " "
                            << point.z << std::endl;
    }

    return 0;
}