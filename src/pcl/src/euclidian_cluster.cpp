#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/visualization/pcl_visualizer.h>

int main (int argc, char** argv)
{
    // std::cout << "Hello World !" << std::endl;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr in_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_r (new pcl::PointCloud<pcl::PointXYZRGB>);

    if(pcl::io::loadPCDFile<pcl::PointXYZRGB>("pcd_cropping.pcd", *in_cloud) == -1)
    {
        PCL_ERROR("Couldn't find File!!! \n");
        return(-1);
    }

    std::cout << "Point cloud before Filtering: " << in_cloud->size() << "data points." << std::endl;


    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficient (new pcl::ModelCoefficients);
    pcl::PCDWriter writer;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RRANSAC);
    seg.setMaxIterations(100);
    seg.setDistanceThreshold(2);

    int i=0, nr_points = (int) cloud_plane->size();
    seg.setInputCloud(in_cloud);
    seg.segment(*inliers, *coefficient);
    if(inliers->indices.size() == 0){
        std::cout << "Couldn't estimate a plannar model for given dataset!!! \n" << std::endl;
        return(-1);
    }

    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(in_cloud);
    extract.setIndices(inliers);
    extract.setNegative(false);

    extract.filter(*cloud_plane);
    std::cout << "Point Cloud Representing the Planar: " << cloud_plane->size() << " data points." << std::endl;

    pcl::io::savePCDFileASCII ("setNegative_false.pcd", *cloud_plane);

    extract.setNegative(true);
    extract.filter(*cloud_f);

    pcl::io::savePCDFileASCII ("setNegative_true.pcd", *cloud_f);

    *cloud_plane = *cloud_f;

    pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> sor;
    sor.setInputCloud(cloud_f);
    sor.setMeanK(50);
    sor.setStddevMulThresh(1.0);
    sor.filter(*cloud_r);

    pcl::io::savePCDFileASCII ("outliers_removal.pcd", *cloud_r);

    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree->setInputCloud(cloud_r);

    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
    ec.setClusterTolerance(2);
    ec.setMinClusterSize(1000);       //smallest cluster
    ec.setMaxClusterSize(6000);     //highest cluster
    ec.setSearchMethod(tree);
    ec.setInputCloud(cloud_r);
    ec.extract(cluster_indices);

    int j = 0;
    for(std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it){
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZRGB>);
        for(std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end();pit++){
            cloud_cluster->push_back((*cloud_r)[*pit]);
        }
        cloud_cluster->width = cloud_cluster->size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        std::cout << "Point Cloud representing the cluster " << j << ": " << cloud_cluster->size() << " data points." << std::endl;
        std::stringstream ss;
        ss << "cloud_cluster_" << j << ".pcd";
        writer.write<pcl::PointXYZRGB> (ss.str(), *cloud_cluster, false);
        j++;
    }

    return 0;
}