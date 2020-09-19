#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/fpfh.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/histogram_visualizer.h>
#include <pcl/features/normal_3d_omp.h>


typedef pcl::PointXYZ PointType;
typedef pcl::Normal NormalType;
typedef pcl::FPFHSignature33 DescriptorType;

int main(int argc, char** argv)
{
    pcl::PointCloud<PointType>::Ptr cloud (new pcl::PointCloud<PointType>);
    pcl::PointCloud<NormalType>::Ptr normals (new pcl::PointCloud<NormalType>);

    if (pcl::io::loadPCDFile <pcl::PointXYZ> (argv[1], *cloud) == -1)
    // load the file
    {
        PCL_ERROR ("Couldn't read file");
        return (-1);
    }


  // Compute the normals
    // pcl::NormalEstimation<PointType, NormalType> normalEstimation;
    pcl::NormalEstimationOMP<PointType, NormalType> normalEstimation;    //normal with OpenAMP to fasting compute
    normalEstimation.setInputCloud (cloud);
    pcl::search::KdTree<PointType>::Ptr tree (new pcl::search::KdTree<PointType>);
    normalEstimation.setSearchMethod (tree);
    normalEstimation.setRadiusSearch (0.05);
    normalEstimation.compute (*normals);



    //create the PFH Estimation class, and pass the input dataset+normals to it
    pcl::FPFHEstimation<PointType, NormalType, DescriptorType> descriptor;
    descriptor.setInputCloud(cloud);
    descriptor.setInputNormals(normals);
    
    //create an empty kdtree
    // pcl::search::KdTree<PointType>::Ptr tree (new pcl::search::KdTree<PointType>);
    // pcl::KdTreeFLANN<PointType>::Ptr tree (new pcl::KdTreeFLANN<PointType>);
    descriptor.setSearchMethod(tree);

    // output dataset
    pcl::PointCloud<DescriptorType>::Ptr outputDescriptor (new pcl::PointCloud<DescriptorType>);

    // use all neighbors in a sphere of radius 5 cm
    // IMPORTANT: the radius used here has to be larger than the radius used to estimate the surface normals!!
    descriptor.setRadiusSearch(0.05);

    //compute the features
    descriptor.compute(*outputDescriptor);

    std::cout << outputDescriptor->size() << std::endl;

    // Display and retrieve the shape context descriptor vector for the 0th point.
    std::cout << outputDescriptor->points[0] << std::endl;


    // //ascii
    pcl::io::savePCDFile("histogram_pfh.pcd", *outputDescriptor);
    std::cerr << "Saved in ASCII Fromat ." << std::endl;


    // Plotter object.
    pcl::visualization::PCLHistogramVisualizer viewer;
    // We need to set the size of the descriptor beforehand.
    viewer.addFeatureHistogram(*outputDescriptor, 308);
    // viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(vfhFeatures, normals);

    viewer.spin();

    return 0;

}