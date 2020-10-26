#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/console/parse.h>
#include <pcl/console/print.h>
#include <pcl/io/pcd_io.h>
#include <boost/filesystem.hpp>
#include <flann/flann.h>
#include <flann/io/hdf5.h>
#include <fstream>

typedef std::pair<std::string, std::vector<float> > VfhModel;

bool loadHist (const boost::filesystem::path &path, VfhModel &vfh)
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

void loadFeatureModels(const boost::filesystem::path &dir, const std::string &extension, std::vector<VfhModel> &models)
{
    if(!boost::filesystem::exists(dir) && !boost::filesystem::is_directory(dir))
        return ;
        
    for(boost::filesystem::directory_iterator i (dir); i != boost::filesystem::directory_iterator(); ++i)
    {
        if(boost::filesystem::is_directory(i->status()))
        {
            std::stringstream ss;
            ss << i->path();
            pcl::console::print_highlight("Loading %s (%lu models added so far). \n", ss.str().c_str(), (unsigned long)models.size());
            loadFeatureModels(i->path(), extension, models);
        }
        if(boost::filesystem::is_regular_file(i->status()) && boost::filesystem::extension( i->path()) == extension)
        {
            VfhModel m;
            if(loadHist(dir / i->path().filename(), m))
                models.push_back(m);
        }
    }
}

int main (int argc, char** argv)
{
    // std::cout << "helo" << std::endl;
    std::string extension(".pcd");
    transform(extension.begin(), extension.end(), extension.begin(), (int(*)(int))tolower);
    
    std::string idxFile = "kdtree.idx";
    std::string h5File = "training_data.h5";
    std::string listFile = "training_data.list";

    std::vector<VfhModel> models;

    //load the histograms
    loadFeatureModels("dataset", extension, models);
    pcl::console::print_highlight("%Loadaed %d VFH models. creating training data %s/%s.\n",
        (int)models.size(), h5File.c_str(), listFile.c_str());
    
    // for(int i = 0; i < models.size(); i++)
    // {
    //     std::cout << models[i].first << std::endl; 
    // }
    //converts data into FLANN Format
    flann::Matrix<float> data (new float[models.size() * models[0].second.size()], models.size(), models[0].second.size());

    for(std::size_t i =0 ;  i < data.rows ; ++i)
    {
        for(std::size_t j=0; j < data.cols; ++j)
        {
            data[i][j] = models[i].second[j];
        }
    }

    flann::save_to_file(data, h5File, "training_data");
    std::ofstream fs;
    fs.open(h5File.c_str());
    for(std::size_t i=0; i< models.size(); ++i)
    {
        fs << models[i].first << "\n";
    }
    fs.close();

    //build the tree index and save it to disk
    pcl::console::print_error ("building the kdtree index (%s) for %d elemetns.. \n",
        idxFile.c_str(), (int)data.rows);
    flann::Index<flann::ChiSquareDistance<float>> index (data, flann::LinearIndexParams());
    index.buildIndex();
    index.save(idxFile);
    delete[] data.ptr ();
    
    return 0;
}