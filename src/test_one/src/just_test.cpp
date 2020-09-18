#include <iostream>
#include <vector>
#include <utility>
#include <pcl/io/pcd_io.h>
#include <pcl/features/integral_image_normal.h>
#include <pcl/point_cloud.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/visualization/pcl_visualizer.h>
#include<pcl/visualization/pcl_plotter.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <pcl/features/vfh.h>


typedef pcl::PointXYZRGB PointType;
typedef pcl::Normal NormalType;
typedef pcl::ReferenceFrame RFType;
// typedef pcl::SHOT352 DescriptorType;
typedef pcl::VFHSignature308 DescriptorType;



int main (int argc, char** argv)
{   


  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());

//   ... read, pass in or create a point cloud with normals ...
//   ... (note: you can create a single PointCloud<PointNormal> if you want) ...

    if (pcl::io::loadPCDFile (argv[1], *cloud) < 0)
    {
        std::cout << "Error loading model cloud." << std::endl;
        // showHelp (argv[0]);s
        return (-1);
    }


  // Create the VFH estimation class, and pass the input dataset+normals to it
  pcl::VFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::VFHSignature308> vfh;
  vfh.setInputCloud (cloud);
  vfh.setInputNormals (normals);
  // alternatively, if cloud is of type PointNormal, do vfh.setInputNormals (cloud);

  // Create an empty kdtree representation, and pass it to the FPFH estimation object.
  // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
  vfh.setSearchMethod (tree);

  // Output datasets
  pcl::PointCloud<pcl::VFHSignature308>::Ptr vfhs (new pcl::PointCloud<pcl::VFHSignature308> ());

  // Compute the features
  vfh.compute (*vfhs);

  // vfhs->size () should be of size 1*

    // //plot
    // pcl::visualization::PCLPlotter * plotter = new PCLPlotter ();

    // //define polynomial function, y = x^2,
    // std::vector<double> func1(3,0);
    // func1[2] = 1;

    // //add the polynomial func1 to the plotter iwth [-10, 10] as the range x
    // plotter->addPlotData(func1, -10, 10, "y = x^2");

    // plotter->plot();

//   std::cerr << vfh <<std::endl;

    // pcl::PointCloud<PointType>::Ptr cloud (new pcl::PointCloud<PointType>);

    // if (pcl::io::loadPCDFile (argv[1], *cloud) < 0)
    // {
    //     std::cout << "Error loading model cloud." << std::endl;
    //     // showHelp (argv[0]);s
    //     return (-1);
    // }

    // //read, pass in or creatae a point cloud with normals
    // pcl::PointCloud<NormalType>::Ptr normals (new pcl::PointCloud<NormalType>);
    // // pcl::IntegralImageNormalEstimation<PointType, NormalType> normals;
    
    // // pcl::NormalEstimationOmp<PointType, NormalType> normals;
    // // ne.setNormalEstimationMethod (ne.AVERAGE_3D_GRADIENT);
    // // normals.setKSearch(10);
    // // normals.setInputCloud(cloud);
    // // normals.compute(*normals);

    // //create the VFH Estimation class, and pass the input dataset+normals to it
    // pcl::VFHEstimation<PointType, NormalType, DescriptorType> vfh;
    // vfh.setInputCloud(cloud);
    // vfh.setInputNormals(normals);
    
    // //create an empty kdtree representation, and pass it to the FPFH estimation object .
    // // its content will be filled inside the object, based on the given input dataset (as no other search surface is given)
    // pcl::search::KdTree<PointType>::Ptr tree (new pcl::search::KdTree<PointType>);
    // vfh.setSearchMethod(tree);

    // // output datasets
    // pcl::PointCloud<DescriptorType>::Ptr vfhs (new pcl::PointCloud<DescriptorType>);

    // // compute the features
    // vfh.compute(*vfhs);






    // pcl::PointCloud<PointType>::Ptr model (new pcl::PointCloud<PointType> ());
    // pcl::PointCloud<PointType>::Ptr model_keypoints (new pcl::PointCloud<PointType> ());
    // pcl::PointCloud<PointType>::Ptr scene (new pcl::PointCloud<PointType> ());
    // pcl::PointCloud<PointType>::Ptr scene_keypoints (new pcl::PointCloud<PointType> ());
    // pcl::PointCloud<NormalType>::Ptr model_normals (new pcl::PointCloud<NormalType> ());
    // pcl::PointCloud<NormalType>::Ptr scene_normals (new pcl::PointCloud<NormalType> ());
    // pcl::PointCloud<DescriptorType>::Ptr model_descriptors (new pcl::PointCloud<DescriptorType> ());
    // pcl::PointCloud<DescriptorType>::Ptr scene_descriptors (new pcl::PointCloud<DescriptorType> ());

    // //  Load clouds
    // if (pcl::io::loadPCDFile ("milk.pcd", *model) < 0)
    // {
    //     std::cout << "Error loading model cloud." << std::endl;
    //     // showHelp (argv[0]);s
    //     return (-1);
    // }
    // if (pcl::io::loadPCDFile ("milk_cartoon_all_small_clorox.pcd", *scene) < 0)
    // {
    //     std::cout << "Error loading scene cloud." << std::endl;
    //     // showHelp (argv[0]);
    //     return (-1);
    // }

    // // compute normal
    // pcl::NormalEstimationOmp<PointType, NormalType> norm_est;
    // norm_est.setKSearch(10);
    // norm_est.setInputCloud(model);
    // norm_est.compute(*scene_normals);

    // norm_est.setInputCloud(scene);
    // norm_est.compute($scene_normals);


    // //find model scene correspondences with KdTree
    // pcl::CorrespondencesPtr model_scene_corrs (new pcl::Correspondences());

    // pcl::KdTreeFLANN<DescriptorType> math_search>;
    // math_search.setInputCloud(model_descriptors);

    // //for each scene keypoint descriptor, find nearest neightbor into the model keypoint cloud 

    return 0;
}