//
// Created by youfa on 2021/11/23.
//

#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include "sophus/se3.hpp"

using namespace std;
using namespace Eigen;

int main(int argc,char** argv)
{
    //沿着z周转90度的旋转矩阵
    Eigen::Matrix3d R=AngleAxisd(M_PI/2,Vector3d(0,0,1)).toRotationMatrix();

    //或者四元数
    Quaterniond q(R);
    Sophus::SO3d SO3_R(R);
    Sophus::SO3d SO3_q(q);

    //而真等价
    cout<<"SO(3) from matrix: \n"<<SO3_R.matrix()<<endl;
    cout<<"SO(3) from quaternion: \n"<<SO3_q.matrix()<<endl;

    //使用对数映射获得它的李代数
    Vector3d so3=SO3_R.log();
    cout<<"so3="<<so3.transpose()<<endl;

    //hat 为向量到反对成矩阵
    cout<<"so3 hat=\n"<<Sophus::SO3d::hat(so3)<<endl;

    //相对的，vee为反对称到向量
    cout<<"so3 hat vee= "<<Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose()<<endl;

    //增量绕动模型的更新
    Vector3d update_so3(1e-4,0,0);
    Sophus::SO3d SO3_updated=Sophus::SO3d::exp(update_so3)*SO3_R;
    cout<<"SO3_updated=\n"<<SO3_updated.matrix()<<endl;


    cout<<'------------------------------'<<endl;

    //对SE操作
    Vector3d t(1,0,0);
    Sophus::SE3d SE3_Rt(R,t);
    Sophus::SE3d SE3_qt(q,t);
    cout<<"SE3 from R,t= \n"<<SE3_Rt.matrix()<<endl;
    cout<<"SE3 from q,t= \n"<<SE3_qt.matrix()<<endl;

    //李代数se(3)六维度向量
    typedef Matrix<double,6,1> Vector6d;
    Vector6d se3=SE3_qt.log();
    cout<<"se3= "<<se3.transpose()<<endl;

    //se3 平移在前，旋转在后
    cout<<"se3 hat \n" <<Sophus::SE3d::hat(se3)<<endl;
    cout<<"se3 hat vee= "<<Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose()<<endl;

    //最后，更新
    Vector6d updated_se3;
    updated_se3.setZero();
    updated_se3(0,0)=1e-4d;
    Sophus::SE3d SE3_updated=Sophus::SE3d::exp(updated_se3)*SE3_Rt;
    cout<<"SE3 updated= "<<endl<<SE3_updated.matrix()<<endl;

    return 0;
}