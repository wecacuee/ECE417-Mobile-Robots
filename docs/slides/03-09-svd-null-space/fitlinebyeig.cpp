#include <iostream>
#include <vector>

#include "matplotlibcpp.h"
#include "Eigen/Eigenvalues"

namespace plt = matplotlibcpp;

std::vector<double>
to_std_vector(const Eigen::VectorXd v) {
    std::vector<double>  stdv(v.data(), v.data() + v.rows() * v.cols());
    return stdv;
}

int main(int argc, char* argv[]) {
    // Initialize a 4 x 3 matrix
    Eigen::MatrixXd A(4, 3);
    A << 100, 98, 1,
         105, 95, 1,
         107, 90, 1,
         110, 85, 1;

    Eigen::EigenSolver<Eigen::MatrixXd> solver(A.transpose() * A);
    Eigen::VectorXcd Lambda = solver.eigenvalues();
    Eigen::MatrixXcd S = solver.eigenvectors();

    // Left singular vectors of A are the same as eigenvectors of AᵀA
    Eigen::MatrixXd V = S.real();

    // We take the rank of the matrix to be 2 and take the last column of V to
    // be the basis of nullspace
    Eigen::Vector3d l = V.col(2);
    std::cout << "\nRepr of line = Basis of NullSpace(A) = " <<  l << "\n";

    plt::named_plot("points", to_std_vector(A.col(0)), to_std_vector(A.col(1)), "r+");

    Eigen::VectorXd xs = A.col(0);
    Eigen::VectorXd ys = (- l(2) - l(0) * xs.array()) / l(1);
    plt::named_plot("line", to_std_vector(xs), to_std_vector(ys), "b-");
    plt::show();
}
