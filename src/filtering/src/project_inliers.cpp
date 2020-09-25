#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/visualization/pcl_visualizer.h>

int
 main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_projected (new pcl::PointCloud<pcl::PointXYZ>);


    if(argv[1])
    {
        pcl::PCDReader reader;
        reader.read<pcl::PointXYZ> (argv[1], *cloud);
    }else{
        // Fill in the cloud data
        cloud->width  = 5;
        cloud->height = 1;
        cloud->points.resize (cloud->width * cloud->height);

        for (auto& point: *cloud)
        {
            point.x = 1024 * rand () / (RAND_MAX + 1.0f);
            point.y = 1024 * rand () / (RAND_MAX + 1.0f);
            point.z = 1024 * rand () / (RAND_MAX + 1.0f);
        }
    }


  std::cerr << "Cloud before projection: " << std::endl;
  for (const auto& point: *cloud)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;

  // Create a set of planar coefficients with X=Y=0,Z=1
  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
  coefficients->values.resize (4);
  coefficients->values[0] = coefficients->values[1] = 0;
  coefficients->values[2] = 1.0;
  coefficients->values[3] = 0;

  // Create the filtering object
  pcl::ProjectInliers<pcl::PointXYZ> proj;
  proj.setModelType (pcl::SACMODEL_PLANE);
  proj.setInputCloud (cloud);
  proj.setModelCoefficients (coefficients);
  proj.filter (*cloud_projected);

  std::cerr << "Cloud after projection: " << std::endl;
  for (const auto& point: *cloud_projected)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;

    //
    pcl::visualization::PCLVisualizer viewer ("Correspondence Grouping");
    // viewer.addPointCloud (cloud_projected, "scene_cloud");


    // int v1(0);
    // viewer->createViewPort(0.5, 0.0, 1.0, 1.0, v1);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloud, 0, 255, 0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> filtered_color(cloud_projected, 0, 0, 255);
    viewer.addPointCloud (cloud, cloud_color, "scene_cloud");
    viewer.addPointCloud (cloud_projected, filtered_color, "scenea_cloud");
    viewer.addCoordinateSystem();

    while (!viewer.wasStopped ())
    {
        viewer.spinOnce ();
    }
  return (0);
}