#include<iostream>

#include<ctime>

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

#define MATRIX_SIZE 50

int main(int argc,char** argv)
{
    Matrix<float,2,3> matrix_23;

    Vector3d v_3d;

    Matrix<float,3,1> vd_3d;

    Matrix3d matrix_33=Matrix3d::Zero();

    Matrix<double,Dynamic,Dynamic> matrix_dynamic;

    MatrixXd matrix_x;

    matrix_23<<1,2,3,4,5,6;

    cout<<"matrix 2x3 from 1 to 6: \n"<<matrix_23<<endl;

    cout<<"print matrix 2x3: "<<endl;
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            cout<<matrix_23(i,j)<<"\t";
        }
        cout<<endl;
    }

    v_3d<<3,2,1;
    vd_3d<<4,5,6;

   // Matrix<double,2,1> result_wrong_type=matrix_23*v_3d;
   Matrix<double,2,1> result=matrix_23.cast<double>()*v_3d;

   cout<<"[1,2,3;4,5,6]*[3,2,1]="<<result.transpose()<<endl;

   Matrix<float,2,1> result2=matrix_23*vd_3d;
    cout<<"[1,2,3;4,5,6]*[4,5,6]="<<result2.transpose()<<endl;

    matrix_33=Matrix3d::Random();
    cout<<"random matrix: \n"<<matrix_33<<endl;
    cout<<"transpose: "<<matrix_33.transpose()<<endl;
    cout<<"sum: "<<matrix_33.sum()<<endl;

    cout<<"trace: "<<matrix_33.trace()<<endl;

    cout<<"inverse: "<<matrix_33.inverse()<<endl;
    cout<<"det: "<<matrix_33.determinant()<<endl;

    //eigen value
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout<<"eigen value"<<eigen_solver.eigenvalues()<<endl;
    cout<<"Eigen vectors: "<<eigen_solver.eigenvectors()<<endl;

    //解方程
    Matrix<double,MATRIX_SIZE,MATRIX_SIZE> matrix_NN =
            MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);
    matrix_NN=matrix_NN*matrix_NN.transpose();

    Matrix<double,MATRIX_SIZE,1> v_Nd=MatrixXd::Random(MATRIX_SIZE,1);

    clock_t time_start=clock();

    //求逆矩阵
    Matrix<double,MATRIX_SIZE,1> x=matrix_NN.inverse()*v_Nd;
    cout<<"time of normal inverse is: "<<1000*(clock()-time_start)/(double) CLOCKS_PER_SEC << "ms"<<endl;
    cout<<"x: "<<x.transpose()<<endl;

    //通常采用矩阵分解来求解
    time_start=clock();
    x=matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout<<"time of normal inverse is: "<<1000*(clock()-time_start)/(double) CLOCKS_PER_SEC << "ms"<<endl;
    cout<<"x: "<<x.transpose()<<endl;

    //对于正定矩阵，还可以使用cholesky分解来求解
    time_start=clock();
    x=matrix_NN.ldlt().solve(v_Nd);
    cout<<"time of normal inverse is: "<<1000*(clock()-time_start)/(double) CLOCKS_PER_SEC << "ms"<<endl;
    cout<<"x: "<<x.transpose()<<endl;

    return 0;
}
