#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/common/common.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <flann/flann.h>
#include <flann/io/hdf5.h>
#include <boost/filesystem.hpp>

typedef std::pair<
    std::string,
    std::vector <float> 
> VfhModel;

bool
loadHist (const boost::filesystem::path &path, VfhModel &vfh)
{
  int vfh_idx;
  // Load the file as a PCD
  try
  {
    pcl::PCLPointCloud2 cloud;
    int version;
    Eigen::Vector4f origin;
    Eigen::Quaternionf orientation;
    pcl::PCDReader r;
    int type; unsigned int idx;
    r.readHeader (path.string (), cloud, origin, orientation, version, type, idx);

    vfh_idx = pcl::getFieldIndex (cloud, "vfh");
    if (vfh_idx == -1)
      return (false);
    if ((int)cloud.width * cloud.height != 1)
      return (false);
  }
  catch (const pcl::InvalidConversionException&)
  {
    return (false);
  }

  // Treat the VFH signature as a single Point Cloud
  pcl::PointCloud <pcl::VFHSignature308> point;
  pcl::io::loadPCDFile (path.string (), point);
  vfh.second.resize (308);

  std::vector <pcl::PCLPointField> fields;
  pcl::getFieldIndex<pcl::VFHSignature308> ("vfh", fields);

  for (std::size_t i = 0; i < fields[vfh_idx].count; ++i)
  {
    vfh.second[i] = point[0].histogram[i];
  }
  vfh.first = path.string ();
  return (true);
}

inline void
nearestKSearch (flann::Index<flann::ChiSquareDistance<float> > &index, const VfhModel &model, 
                int k, flann::Matrix<int> &indices, flann::Matrix<float> &distances)
{
  // Query point
  flann::Matrix<float> p = flann::Matrix<float>(new float[model.second.size ()], 1, model.second.size ());
  memcpy (&p.ptr ()[0], &model.second[0], p.cols * p.rows * sizeof (float));

  indices = flann::Matrix<int>(new int[k], 1, k);
  distances = flann::Matrix<float>(new float[k], 1, k);
  index.knnSearch (p, indices, distances, k, flann::SearchParams (512));
  delete[] p.ptr ();
}

int main(int argc, char** argv)
{   int k = 16;
    double thresh = DBL_MAX;

    std::string extension(".pcd");
    transform(extension.begin(), extension.end(), extension.begin(), (int(*)(int))tolower);

    //load the test histogram
    std::vector<int> pcdIndices = pcl::console::parse_file_extension_argument(argc, argv, ".pcd");
    VfhModel histogram;
    if(!loadHist(argv[pcdIndices.at(0)], histogram))
    {
        pcl::console::print_error("Cannot load test file %s\n", argv[pcdIndices.at(0)]);
        return -1;
    }

    std::string idxFile = "kdtree.idx";
    std::string h5File = "training_data.h5";
    std::string listFile = "training_data.list";

    std::vector<VfhModel> models;
    flann::Matrix<int> kIndices;
    flann::Matrix<float> kDistances;
    flann::Matrix<float> data;
    
    if(!boost::filesystem::exists(h5File) || !boost::filesystem::exists(listFile))
    {
        pcl::console::print_error("could not find kd-tree index in file %s!", idxFile.c_str());
        return -1;
    }else{
        flann::Index<flann::ChiSquareDistance<float>> index (data, flann::SavedIndexParams("kdtree.idx"));
        index.buildIndex();
        nearestKSearch(index, histogram, k, kIndices, kDistances);
    }

    //output the result on screen
    pcl::console::print_highlight("The closest %d neighbors for %s are : \n", k, argv[pcdIndices[0]]);
    for(int i = 0; i < k; i++)
    {
        pcl::console::print_info("%d - $s (%d) with a distance of : %f\n", 
            i, models.at(kIndices[0][i]).first.c_str(), kIndices[0][i], kDistances[0][i]);
    }
    
    //load the result
    pcl::visualization::PCLVisualizer p (argc, argv, "VFH Cluster Classifier");
    int ys = (int )std::floor(sqrt((double)k));
    int xs = ys + (int) std::ceil((k/(double)ys) - ys);
    double xstep = (double)(1/(double)xs);
    double ystep = (double)(1/(double)ys);
    pcl::console::print_highlight ("Preparing to load "); 
    pcl::console::print_value ("%d", k); 
    pcl::console::print_info (" files ("); 
    pcl::console::print_value ("%d", xs);    
    pcl::console::print_info ("x"); 
    pcl::console::print_value ("%d", ys); 
    pcl::console::print_info (" / ");
    pcl::console::print_value ("%f", xstep); 
    pcl::console::print_info ("x"); 
    pcl::console::print_value ("%f", ystep); 
    pcl::console::print_info (")\n");

    int viewport = 0, l=0, m=0;
    for(int i =0; i<k; ++i)
    {
        std::string cloud_name = models.at(kIndices[0][i]).first;
        boost::replace_last(cloud_name, "_vfh", "");

        p.createViewPort(l*xstep, m*ystep, (l+1) * xstep, (m+1)* ystep, viewport);
        l++;
        if(l >= xs)
        {
            l=0;
            m++;
        }

        pcl::PCLPointCloud2 cloud;
        pcl::console::print_highlight(stderr, "Loading ");
        pcl::console::print_value(stderr, "%s ", cloud_name.c_str());
        if(pcl::io::loadPCDFile(cloud_name, cloud) == -1)
        {
            break;
        }

        //convert from blob to pointlcloud
        pcl::PointCloud<pcl::PointXYZ> cloud_xyz;
        pcl::fromPCLPointCloud2(cloud, cloud_xyz);
        
        if(cloud_xyz.size() == 0)
        {
            break;
        }

        pcl::console::print_info ("[done, "); 
        pcl::console::print_value ("%zu", static_cast<std::size_t>(cloud_xyz.size ()));
        pcl::console::print_info (" points]\n");
        pcl::console::print_info ("Available dimensions: "); 
        pcl::console::print_value ("%s\n", pcl::getFieldsList (cloud).c_str ());

        
    // Demean the cloud
    Eigen::Vector4f centroid;
    pcl::compute3DCentroid (cloud_xyz, centroid);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz_demean (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::demeanPointCloud<pcl::PointXYZ> (cloud_xyz, centroid, *cloud_xyz_demean);
    // Add to renderer*
    p.addPointCloud (cloud_xyz_demean, cloud_name, viewport);
    
    // Check if the model found is within our inlier tolerance
    std::stringstream ss;
    ss << kDistances[0][i];
    if (kDistances[0][i] > thresh)
    {
      p.addText (ss.str (), 20, 30, 1, 0, 0, ss.str (), viewport);  // display the text with red

      // Create a red line
      pcl::PointXYZ min_p, max_p;
      pcl::getMinMax3D (*cloud_xyz_demean, min_p, max_p);
      std::stringstream line_name;
      line_name << "line_" << i;
      p.addLine (min_p, max_p, 1, 0, 0, line_name.str (), viewport);
      p.setShapeRenderingProperties (pcl::visualization::PCL_VISUALIZER_LINE_WIDTH, 5, line_name.str (), viewport);
    }
    else
      p.addText (ss.str (), 20, 30, 0, 1, 0, ss.str (), viewport);

    // Increase the font size for the score*
    p.setShapeRenderingProperties (pcl::visualization::PCL_VISUALIZER_FONT_SIZE, 18, ss.str (), viewport);

    // Add the cluster name
    p.addText (cloud_name, 20, 10, cloud_name, viewport);
  }
  // Add coordianate systems to all viewports
  p.addCoordinateSystem (0.1, "global", 0);

  p.spin ();
  return (0);
}