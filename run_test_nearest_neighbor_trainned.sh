#!/bin/bash

# Example directory containing _vfh.pcd files
DATA=dataset

# Inlier distance threshold
thresh=50

# Get the closest K nearest neighbors
k=16

for i in `find $DATA -type d -name "*"`
do
  echo $i
  for j in `find $i -type f \( -iname "*cluster*_vfh.pcd" \) | sort -R`
  # for j in `find $i -type f \( -iname "*cluster*_nxyz.pcd" \) | sort -R`
  do
    echo $j
    # pcl_viewer $j
    rosrun test_one nearest_neighbors -k $k -thresh $thresh $j -cam "0.403137,0.868471/0,0,0/-0.0932051,-0.201608,-0.518939/-0.00471487,-0.931831,0.362863/1464,764/6,72"
  done
done