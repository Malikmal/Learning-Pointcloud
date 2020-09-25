#include <iostream>
#include <vector>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/shot.h>
#include <pcl/visualization/histogram_visualizer.h>



int main (int argc, char** argv)
{
    std::string fileName = argv[1];
    std::cout << "Reading " << fileName << std::endl;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile <pcl::PointXYZ> (fileName.c_str(), *cloud) == -1)
        // load the file
        {
        PCL_ERROR ("Couldn't read file");
        return (-1);
        }
    std::cout << "Loaded " << cloud->points.size() << " points." << std::endl;

    // Compute the normals
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud (cloud);

    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    normalEstimation.setSearchMethod (tree);

    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud< pcl::Normal>);
    normalEstimation.setRadiusSearch (0.03);
    normalEstimation.compute (*normals);

    // Setup the SHOT features
    //typedef pcl::FPFHSignature33 ShotFeature; // Can't use this, even despite: http://docs.pointclouds.org/trunk/structpcl_1_1_f_p_f_h_signature33.html
    typedef pcl::SHOT352 ShotFeature;
    pcl::SHOTEstimation<pcl::PointXYZ, pcl::Normal, ShotFeature> shotEstimation;
    shotEstimation.setInputCloud(cloud);
    shotEstimation.setInputNormals(normals);

    // Use the same KdTree from the normal estimation
    shotEstimation.setSearchMethod (tree);
    pcl::PointCloud<ShotFeature>::Ptr shotFeatures(new pcl::PointCloud<ShotFeature>);
    shotEstimation.setRadiusSearch (0.2);
    shotEstimation.setKSearch(0); // ?

    // Actually compute the spin images
    shotEstimation.compute (*shotFeatures);
    std::cout << "SHOT output points.size (): " << shotFeatures->points.size () << std::endl;

    // Display and retrieve the SHOT descriptor for the first point.
    ShotFeature descriptor = shotFeatures->points[0];
    std::cout << descriptor << std::endl;


    // // //ascii
    pcl::io::savePCDFile("histogram_shot.pcd", *shotFeatures);
    std::cerr << "Saved in ASCII Fromat ." << std::endl;


    return 0;
}



















// #include <iostream>
// #include <pcl/io/pcd_io.h>
// #include <pcl/features/normal_3d.h>
// #include <pcl/features/shot.h>
// #include <pcl/visualization/histogram_visualizer.h>

// int
// main(int argc, char** argv)
// {
// 	// Object for storing the point cloud.
// 	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
// 	// Object for storing the normals.
// 	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
// 	// Object for storing the SHOT descriptors for each point.
// 	pcl::PointCloud<pcl::SHOT352>::Ptr descriptors(new pcl::PointCloud<pcl::SHOT352>());

// 	// Read a PCD file from disk.
// 	if (pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud) != 0)
// 	{
// 		return -1;
// 	}

// 	// Note: you would usually perform downsampling now. It has been omitted here
// 	// for simplicity, but be aware that computation can take a long time.

// 	// Estimate the normals.
// 	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
// 	normalEstimation.setInputCloud(cloud);
// 	normalEstimation.setRadiusSearch(0.03);
// 	pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
// 	normalEstimation.setSearchMethod(kdtree);
// 	normalEstimation.compute(*normals);

// 	// SHOT estimation object.
// 	pcl::SHOTEstimation<pcl::PointXYZ, pcl::Normal, pcl::SHOT352> shot;
// 	shot.setInputCloud(cloud);
// 	shot.setInputNormals(normals);
// 	// The radius that defines which of the keypoint's neighbors are described.
// 	// If too large, there may be clutter, and if too small, not enough points may be found.
// 	shot.setRadiusSearch(1.05);

// 	shot.compute(*descriptors);



//     // // //ascii
//     pcl::io::savePCDFile("histogram_shot.pcd", *descriptors);
//     std::cerr << "Saved in ASCII Fromat ." << std::endl;

//     // // Plotter object.
//     // pcl::visualization::PCLHistogramVisualizer viewer;
//     // // We need to set the size of the descriptor beforehand.
//     // viewer.addFeatureHistogram(*descriptors, 308);
//     // // viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(vfhFeatures, normals);

//     // viewer.spin();


//     return 0;
// }