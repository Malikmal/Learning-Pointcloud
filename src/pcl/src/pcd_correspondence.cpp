#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/correspondence.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h>
#include <pcl/features/board.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/recognition/cg/hough_3d.h>
#include <pcl/recognition/cg/geometric_consistency.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>

typedef pcl::PointXYZRGB PointType;
typedef pcl::Normal NormalType;
typedef pcl::ReferenceFrame RFType;
typedef pcl::SHOT352 DescriptorType;


int main (int argc, char** argv)
{
    pcl::PointCloud<PointType>::Ptr model (new pcl::PointCloud<PointType> ());
    pcl::PointCloud<PointType>::Ptr scene (new pcl::PointCloud<PointType> ());
    pcl::PointCloud<PointType>::Ptr modelKeypoints (new pcl::PointCloud<PointType> ());
    pcl::PointCloud<PointType>::Ptr sceneKeypoints (new pcl::PointCloud<PointType> ());
    pcl::PointCloud<NormalType>::Ptr normalModel (new pcl::PointCloud<NormalType> ());
    pcl::PointCloud<NormalType>::Ptr normalScene (new pcl::PointCloud<NormalType> ());
    pcl::PointCloud<DescriptorType>::Ptr descriptorModel (new pcl::PointCloud<DescriptorType> ());
    pcl::PointCloud<DescriptorType>::Ptr descriptorScene (new pcl::PointCloud<DescriptorType> ());
    
    

    if (pcl::io::loadPCDFile <PointType> (argv[1], *model) == -1)
    {
        PCL_ERROR ("Couldn't read Model file");
        return (-1);
    }

    if (pcl::io::loadPCDFile <PointType> (argv[2], *scene) == -1)
    {
        PCL_ERROR ("Couldn't read Scene file");
        return (-1);
    }



    // normals
    pcl::NormalEstimationOMP<PointType, NormalType> normal;
    normal.setKSearch(10);
    normal.setInputCloud(model);
    normal.compute(*normalModel);

    normal.setInputCloud(scene);
    normal.compute(*normalScene);

    // // downnsample to extract keypoints
    pcl::UniformSampling<PointType> uniform_sampling;
    uniform_sampling.setInputCloud (model);
    uniform_sampling.setRadiusSearch (0.01f);
    uniform_sampling.filter (*modelKeypoints);
    std::cout << "Model total points: " << model->size () << "; Selected Keypoints: " << modelKeypoints->size () << std::endl;

    uniform_sampling.setInputCloud (scene);
    uniform_sampling.setRadiusSearch (0.03f);
    uniform_sampling.filter (*sceneKeypoints);
    std::cout << "Scene total points: " << scene->size () << "; Selected Keypoints: " << sceneKeypoints->size () << std::endl;


    // // descriptor shot
    pcl::SHOTEstimationOMP<PointType, NormalType, DescriptorType> descriptor;
    descriptor.setRadiusSearch(0.02f);

    descriptor.setInputCloud(modelKeypoints);
    descriptor.setInputNormals(normalModel);
    descriptor.setSearchSurface(model);
    descriptor.compute(*descriptorModel);

    descriptor.setInputCloud(sceneKeypoints);
    descriptor.setInputNormals(normalScene);
    descriptor.setSearchSurface(scene);
    descriptor.compute(*descriptorScene);

    // // find model-scene correspondnces with kdtree
    pcl::CorrespondencesPtr correspondence (new pcl::Correspondences());

    pcl::KdTreeFLANN<DescriptorType> tree;
    tree.setInputCloud(descriptorModel);

    //for each scene keypoint descriptro, find nearest neighbor into the model keypoint
    for(std::size_t i = 0; i < descriptorScene->size(); ++i)
    {
        std::vector<int> neighborIndices(1);
        std::vector<float> neighborSqrDists(1);
        if(!std::isfinite(descriptorScene->at(i).descriptor[0])) //skipping NaNs
        {
            continue;
        }
        int foundNeighbor = tree.nearestKSearch(descriptorScene->at(i), 1,neighborIndices, neighborSqrDists);
        if(foundNeighbor == 1 && neighborSqrDists[0] < 0.25f) // add match only if the squared descriptor distance is less than 0.25 (SHOT descriptor distances are between 0 and 1 by design)
        {
            pcl::Correspondence corr (neighborIndices[0], static_cast<int> (i), neighborSqrDists[0]);
            correspondence->push_back (corr);
        }
    }
    std::cout << "Correspondences found : " << correspondence->size() << std::endl;
    


    //
    //  Actual Clustering
    //
    std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f> > rototranslations;
    std::vector<pcl::Correspondences> clustered_corrs;
    // // hough 3d
    // pcl::PointCloud

    // hough 3D
    
    //  Compute (Keypoints) Reference Frames only for Hough
    //
    pcl::PointCloud<RFType>::Ptr model_rf (new pcl::PointCloud<RFType> ());
    pcl::PointCloud<RFType>::Ptr scene_rf (new pcl::PointCloud<RFType> ());

    pcl::BOARDLocalReferenceFrameEstimation<PointType, NormalType, RFType> rf_est;
    rf_est.setFindHoles (true);
    rf_est.setRadiusSearch (0.015f);

    rf_est.setInputCloud (modelKeypoints);
    rf_est.setInputNormals (normalModel);
    rf_est.setSearchSurface (model);
    rf_est.compute (*model_rf);

    rf_est.setInputCloud (sceneKeypoints);
    rf_est.setInputNormals (normalScene);
    rf_est.setSearchSurface (scene);
    rf_est.compute (*scene_rf);

    //  Clustering
    pcl::Hough3DGrouping<PointType, PointType, RFType, RFType> clusterer;
    clusterer.setHoughBinSize (0.01f);
    clusterer.setHoughThreshold (5.0f);
    clusterer.setUseInterpolation (true);
    clusterer.setUseDistanceWeight (false);

    clusterer.setInputCloud (modelKeypoints);
    clusterer.setInputRf (model_rf);
    clusterer.setSceneCloud (sceneKeypoints);
    clusterer.setSceneRf (scene_rf);
    clusterer.setModelSceneCorrespondences (correspondence);

    //clusterer.cluster (clustered_corrs);
    clusterer.recognize (rototranslations, clustered_corrs);

    //visualization
    pcl::visualization::PCLVisualizer viewer ("Correspondence Groupping");
    viewer.addPointCloud(scene, "Scene_cloud");

    pcl::PointCloud<PointType>::Ptr offSceneModel (new pcl::PointCloud<PointType> ());
    // pcl::PointCloud<PointType>::Ptr offSceneModelKeypoints (new pcl::PointCloud<PointType> ());

    pcl::transformPointCloud(*model, *offSceneModel, Eigen::Vector3f(1,0,0), Eigen::Quaternionf(1,0,0,0));
    // pcl::transformPointCloud(*modelKeypoints, *offSceneModelKeypoints,Eigen::Vector3f(-1,0,0), Eigen::Quternionf(1,0,0,0) )

    pcl::visualization::PointCloudColorHandlerCustom<PointType> handler(offSceneModel, 255, 255, 128);
    viewer.addPointCloud(offSceneModel, handler, "offSceneModel");

    // pcl::PointCloud
    for (std::size_t i = 0; i < rototranslations.size (); ++i)
    {
        pcl::PointCloud<PointType>::Ptr rotated_model (new pcl::PointCloud<PointType> ());
        pcl::transformPointCloud (*model, *rotated_model, rototranslations[i]);

        std::stringstream ss_cloud;
        ss_cloud << "instance" << i;

        pcl::visualization::PointCloudColorHandlerCustom<PointType> rotated_model_color_handler (rotated_model, 0, 255, 0);
        viewer.addPointCloud (rotated_model, rotated_model_color_handler, ss_cloud.str ());
    }

    while (!viewer.wasStopped ())
    {
        viewer.spinOnce (); 
    }
 
    return 0;
}