/*
 * OctoMap - An Efficient Probabilistic 3D Mapping Framework Based on Octrees
 * http://octomap.github.com/
 *
 * Copyright (c) 2009-2013, K.M. Wurm and A. Hornung, University of Freiburg
 * All rights reserved.
 * License: New BSD
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of Freiburg nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <fstream>
#include <pcl/common/transforms.h>

using namespace std;
using namespace octomap;
using namespace pcl;

string outpath = "";

void saveCloud(OcTree& tree){
    //init counters
    unsigned int mlsOccupied = 0;
    unsigned int mlsFree = 0;

    //init clouds as PointXYZI to save probability as the intensity scalar value in .pcd files
    pcl::PointCloud<pcl::PointXYZI> mlsOccupiedPcl;
    pcl::PointCloud<pcl::PointXYZI> mlsFreePcl;

    tree.expand();

    // iterate through the entire tree
    for(OcTree::tree_iterator it=tree.begin_tree(),
                end=tree.end_tree(); it!= end; ++it) {
        if (it.isLeaf()) {
            if (tree.isNodeOccupied(*it)) {
                //occupied cells counter
                mlsOccupied += 1;

                float probAsIntensityOcc = it->getOccupancy();

                pcl::PointXYZI tmpOcc = pcl::PointXYZI(probAsIntensityOcc);
                tmpOcc.x = static_cast<float>(it.getX());
                tmpOcc.y = static_cast<float>(it.getY());
                tmpOcc.z = static_cast<float>(it.getZ());

                mlsOccupiedPcl.points.push_back(tmpOcc);

//                cout << endl;
//                cout << "Probability of the occupancy: "<< probAsIntensityOcc << endl;


//                cout << endl;
//                cout << "Coordinate for getCoord for OCCUPIED: " << it.getCoordinate() << endl;
            }
            else {
                //free cells counter
                mlsFree += 1;

                float probAsIntensity = it->getOccupancy();

                pcl::PointXYZI tmp = pcl::PointXYZI(probAsIntensity);
                tmp.x = static_cast<float>(it.getX());
                tmp.y = static_cast<float>(it.getY());
                tmp.z = static_cast<float>(it.getZ());

                mlsFreePcl.points.push_back(tmp);

//                cout << endl;
//                cout << "Probability of the occupancy of the Free cells: "<< probAsIntensity << endl;

//                cout << endl;
//                cout << "Coordinate for getCoord for FREE: " << it.getCoordinate() << endl;
            }
        }
    }

    cout << endl;
    cout << "Occupied & Free cells: " << mlsOccupied << " occ; " << mlsFree << " free; " << endl;

    tree.prune();

    //set up PCD-specific settings
    mlsOccupiedPcl.width    = 1;
    mlsOccupiedPcl.height   = mlsOccupied;
    mlsOccupiedPcl.is_dense = false;
    mlsOccupiedPcl.points.resize (mlsOccupiedPcl.width * mlsOccupiedPcl.height);

    mlsFreePcl.width    = 1;
    mlsFreePcl.height   = mlsFree;
    mlsFreePcl.is_dense = false;
    mlsFreePcl.points.resize (mlsFreePcl.width * mlsFreePcl.height);

    string fileNameOccupied = "mlsOccupied.pcd";
    string fileNameFree =  "mlsFree.pcd";
    string outpath1 = outpath + fileNameOccupied;
    string outpath2 = outpath + fileNameFree; //"/home/olaf/Olaf/PhD/pfg2021/data/utm/mlsOccupiedFree/mlsFree.pcd";
    pcl::io::savePCDFile (outpath1, mlsOccupiedPcl, false);
    pcl::io::savePCDFile (outpath2, mlsFreePcl, false);

}


int main(int argc, char *argv[]) {
    if (argc != 3)
    { cout<<"Wron no. of parameters! Please provide 1 + 2 (program name + parameters) parameters"<<endl<< "Parameter #1: Program name"<<endl<< "Parameter #2: Input point clouds path"<<endl<< "Parameter #3: Output point clouds (voxels) path"<<endl;
        return 0;
    }
    if (argc == 3) {
        cout << "Your selected paths: " << endl << "Input point clouds: " << argv[1]
             << endl
             << endl << "Output point clouds (voxels): " << endl << argv[2]
             << endl;
    }

    //global paths to files
    const char *cloudPath = argv[1];
    string cPath = argv[1];

    //e.g,:
    //const char *cloudPath = "/home/olaf/Olaf/PhD/pfg2021/data/utm/laserscanner1/";
    //string cPath = "/home/olaf/Olaf/PhD/pfg2021/data/utm/laserscanner1/";

    //global out-path for files
    string oPath = argv[2];
    outpath.append(oPath);

    //e.g,:
    // /home/olaf/Olaf/PhD/pfg2021/data/utm/mlsOccupiedFree/...;

    //BBox search for selected bld (id: DEBY_LOD2_4959458_B)  --> how about using the BBox from loaded citygml blds and buffer them?

/*
    //ID: DEBY_LOD2_4959458_B (OK)
//    unsigned int Xmin = 260;
//    unsigned int Ymin = 225;
//    unsigned int Xmax = 325;
//    unsigned int Ymax = 262;

    //ID: DEBY_LOD2_4959460 (OK)
//    unsigned int Xmin = 228;
//    unsigned int Ymin = 268;
//    unsigned int Xmax = 349;
//    unsigned int Ymax = 354;

    //ID: DEBY_LOD2_4959462 (OK)
//    unsigned int Xmin = 301;
//    unsigned int Ymin = 240;
//    unsigned int Xmax = 332;
//    unsigned int Ymax = 285;


    //ID: DEBY_LOD2_4906970 (OK)
//    unsigned int Xmin = 190;
//    unsigned int Ymin = 36;
//    unsigned int Xmax = 211;
//    unsigned int Ymax = 55;
*/

    //ID: pfister, DEBY_LOD2_4957921 (...)
//    unsigned int Xmin = 1094;
//    unsigned int Ymin = 1054;
//    unsigned int Xmax = 1140;
//    unsigned int Ymax = 1090;
//    unsigned int Zmin = 0;    //from the lowest...
//    unsigned int Zmax = 1000; //...to arbitrarily high

    //ID: pfister, DEBY_LOD2_4959323 (...)
//    unsigned int Xmin = 142;
//    unsigned int Ymin = 158;
//    unsigned int Xmax = 196;
//    unsigned int Ymax = 236;
//    unsigned int Zmin = 0;    //from the lowest...
//    unsigned int Zmax = 1000; //...to arbitrarily high

    unsigned int Xmin = 151;
    unsigned int Ymin = 82;
    unsigned int Xmax = 182;
    unsigned int Ymax = 106;
    unsigned int Zmin = 0;    //from the lowest...
    unsigned int Zmax = 1000; //...to arbitrarily high



    cout << endl;
    cout << "Selected BBox: " << "[Xmin: " << Xmin << " Ymin: " << Ymin << " Xmax: " << Xmax << " Ymax: " << Ymax << "]" << endl;

    //TEST
    //int testSetMLS = 10;
    //int testSetGML = 0;

    //init octo-tree with 0.1m resolution
    OcTree tree(0.1);

    //sensor model:
    //log-odds: L_occ = 0.85, L_free = -0.4 that correspond to probabilities:
    tree.setProbHit(0.7);
    tree.setProbMiss(0.4);
    //clamping policy:
    //probabilities 0.12 and 0.97 that correspond to log-odds:
    tree.setClampingThresMin(-2);
    tree.setClampingThresMax(3.5);

/*
  probabilistic values according to [Hornung et al., 2013]:
  https://link.springer.com/article/10.1007/s10514-012-9321-0
*/

    //count files and gather filepaths in the selected dir for MLS
    vector<string> fPathListMLS;
    vector<int> mlsFilesCounter;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (cloudPath)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            //printf ("%s\n", ent->d_name);
            string fName = ent->d_name;
            if (fName != "." && fName != ".." && fName != "..."){ //peculiar file names elimination
                mlsFilesCounter.push_back(1);
                string fPath;
                fPath = cPath + fName;
                fPathListMLS.push_back(fPath);
            }
        }
        closedir (dir);
    } else {
        //could not open directory
        perror ("");
        return EXIT_FAILURE;
    }

    //check no. of loaded files
    int nrFilesToLoad = mlsFilesCounter.size();
    cout << endl;
    cout << "No of point clouds loaded to perform raycasting: " << endl << nrFilesToLoad << endl;

    //init counter of loaded point clouds for the sake of terminal print tracking
    unsigned int initCloudCounter = 0;

    //load all MLS point clouds and perform ray casting
    for (int i = 0; i < nrFilesToLoad; i++){

        //load iteratively MLS data
        // get XYZ, sensor origin (aka. viewpoint), and clouds
        pcl::PointCloud<pcl::PointWithViewpoint>::Ptr cloudViewPoint(new pcl::PointCloud<pcl::PointWithViewpoint>);
        string cloudName = fPathListMLS[i];
        pcl::io::loadPCDFile(cloudName, *cloudViewPoint);

        initCloudCounter += 1;
        cout << endl;
        cout << "In cloud count: " << initCloudCounter << endl << "  Cloud name: " << cloudName << endl;

        //transform pcl to octomap point cloud
        Pointcloud * cloud = new Pointcloud;
        for ( size_t i = 0; i < cloudViewPoint->size(); ++ i ) {
            point3d pt(cloudViewPoint->points[i].x, cloudViewPoint->points[i].y, cloudViewPoint->points[i].z);
            cloud->push_back( pt );
        }
        //crop point cloud to BBox
        point3d BBoxMin(Xmin,Ymin,Zmin);
        point3d BBoxMax(Xmax,Ymax,Zmax);
        cloud->crop(BBoxMin, BBoxMax);

        //extract sensor origin from the file's header
        point3d sensor_origin(cloudViewPoint->sensor_origin_.x(),cloudViewPoint->sensor_origin_.y(),cloudViewPoint->sensor_origin_.z());

        //perform batch ray casting
        tree.insertPointCloudRays(cloud,sensor_origin);

    }


    //save point clouds per occupied & free
    saveCloud(tree);

    //write occupation grid
/*
    cout << endl;
    tree.writeBinary("simple_tree.bt");
    cout << "wrote example file simple_tree.bt" << endl << endl;
    cout << "now you can use octovis to visualize: octovis simple_tree.bt"  << endl;
    cout << "Hint: hit 'F'-key in viewer to see the freespace" << endl  << endl;
*/

    //print the resolution of the tree for the final check
    cout << "The resolution of the octomap:" << endl;
    cout << tree.getResolution() << endl;



}