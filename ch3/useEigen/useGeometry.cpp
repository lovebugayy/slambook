//
// Created by youfa on 2021/11/20.
//

#include<iostream>
#include <cmath>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main(int argc,char** argv)
{

    //3d矩阵旋转
    Matrix3d rotation_matric =Matrix3d::Identity();

    //旋转矩阵选择是AngleAxisd ，他的底层不直接是matrix，但是运算的时候却可以当作矩阵
    AngleAxisd rotation_vector(M_PI/4,Vector3d(0,0,1)); //沿着z轴旋转45度

    cout.precision(3); //应该是设置精度

    cout<<"rotation matrix =\n"<<rotation_vector.matrix()<<endl;//用matrix换成矩阵

    rotation_matric=rotation_vector.toRotationMatrix();

    //用AngleAxised进行坐标变换
    Vector3d v(1,0,0);
    Vector3d v_rotated =rotation_vector*v;

    cout<<"(1,0,0) after rotation by angle axis ="<<v_rotated.transpose()<< endl;

    //欧拉角
    Vector3d euler_angle=rotation_matric.eulerAngles(2,1,0); //ZYX顺序
    cout<<"yaw pitch roll="<< euler_angle.transpose()<<endl;


    //欧拉变换使用Eigen::Isometry
    Isometry3d f=Isometry3d::Identity();
    f.rotate(rotation_vector);
    f.pretranslate(Vector3d(1,3,4));
    cout<<"Transform matrix = \n"<<f.matrix()<<endl;

    //用变化矩阵进行坐标变换
    Vector3d v_transformed = f*v;
    cout<<"v transformed ="<< v_transformed.transpose()<<endl;

    //对于仿射变换和射影变换，使用Eigen::Affined3d 和 Eigen::Projective3d 即可
    Quaterniond q=Quaterniond(rotation_vector);
    cout<<"quaernion from rotation vector ="<<q.coeffs().transpose()<<endl;
    //coeffs的顺序是x,y,z,w.其中w是实部，其余部分是虚部

    //也可以用旋转矩阵来赋值
    q=Quaterniond (rotation_matric);
    cout<<"quaernion from rotation vector ="<<q.coeffs().transpose()<<endl;

    v_rotated=q*v; //数学上是qvq(-1) ，后面是逆矩阵
    cout<<"(1,0,0) after rotation=" << v_rotated.transpose()<<endl;

    //常规向量乘法表示
    cout<<"should be equal to "<<(q*Quaterniond(0,1,0,0)*q.inverse()).coeffs().transpose()<<endl;

    return 0;




}