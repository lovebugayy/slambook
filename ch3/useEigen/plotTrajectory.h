//
// Created by youfa on 2021/11/21.
//

#ifndef SLAMBOOK_PLOTTRAJECTORY_H
#define SLAMBOOK_PLOTTRAJECTORY_H

#include <iostream>
#include <pangolin/pangolin.h>
#include <eigen3/Eigen/Core>
#include <unistd.h>

using namespace std;
using namespace Eigen;

void test();

void DrawTrajectory(vector<Isometry3d,Eigen::aligned_allocator<Isometry3d>> poses);
#endif //SLAMBOOK_PLOTTRAJECTORY_H
