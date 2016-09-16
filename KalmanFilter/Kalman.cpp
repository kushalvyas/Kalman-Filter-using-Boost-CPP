//
// Created by kushal on 13/9/16.
//
#include "stdio.h"
#include "Kalman.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <python2.7/Python.h>


Kalman::Kalman(){
    std::cout<<"In constructor"<<std::endl;
    F = boost::numeric::ublas::matrix<double>(1, 1);
    H = boost::numeric::ublas::matrix<double>(1, 1);
    B = boost::numeric::ublas::matrix<double>(1, 1);
    Q = boost::numeric::ublas::matrix<double>(1, 1);
    R = boost::numeric::ublas::matrix<double>(1, 1);
    current_state_estimate = boost::numeric::ublas::matrix<double>(1, 1);
    current_prob_estimate = boost::numeric::ublas::matrix<double>(1, 1);
    I = boost::numeric::ublas::matrix<double>(1, 1);
    F(0, 0) = 1;
    H(0, 0) = 1;
    B(0, 0) = 0;
    Q(0, 0) = 0.0001;
    R(0, 0) = 0.1;
    I(0, 0) = 1;
    current_state_estimate(0, 0) = 3;
    current_prob_estimate(0, 0) = 1;




}

boost::numeric::ublas::matrix<double> Kalman::getCurrentEstimate() {
//    std::cout<<"getCurrentEstimate() :: current_state_estimate =>"<< current_state_estimate(0, 0)<<std::endl;
    return current_state_estimate;
}

void Kalman::Step(boost::numeric::ublas::matrix<double> control_vector, boost::numeric::ublas::matrix<double> measurement_vector) {
    boost::numeric::ublas::matrix<double> predicted_state_estimate = multiply(F, current_state_estimate) + multiply(B, control_vector);

    boost::numeric::ublas::matrix<double> predicted_prob_estimate = multiply(multiply(F, current_prob_estimate), boost::numeric::ublas::trans(F)) + Q;

    boost::numeric::ublas::matrix<double> innovation = measurement_vector - multiply(H, predicted_state_estimate);
    boost::numeric::ublas::matrix<double> innovation_covariance = multiply(multiply(H, predicted_prob_estimate), boost::numeric::ublas::trans(H)) + R;

//    correction step
    boost::numeric::ublas::matrix<double> kalman_gain = multiply(predicted_prob_estimate, boost::numeric::ublas::trans(H));
    boost::numeric::ublas::matrix<double> innovation_covariance_inverse(1, 1);
    innovation_covariance_inverse = inverse(innovation_covariance);
    kalman_gain = multiply(kalman_gain, innovation_covariance_inverse);
    current_state_estimate = predicted_state_estimate + multiply(kalman_gain, innovation);
    current_prob_estimate = I - multiply(kalman_gain, H);
    current_prob_estimate = multiply(current_prob_estimate, predicted_prob_estimate);
//    std::cout<<"Step() :: current_State_estimate =>"<<current_state_estimate<<std::endl;

}

boost::numeric::ublas::matrix<double> Kalman::multiply(boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::matrix<double> B){
    return boost::numeric::ublas::prod(A, B);
}
boost::numeric::ublas::matrix<double> Kalman::inverse(boost::numeric::ublas::matrix<double> input){


    boost::numeric::ublas::matrix<double> inv(1, 1);
    int N = input.size1();
    boost::numeric::ublas::matrix<double> A (input);
    typedef boost::numeric::ublas::permutation_matrix<std::size_t> pmatrix;
    pmatrix P(N);

    // Assign the identity matrix to the inverse
    inv.assign(boost::numeric::ublas::identity_matrix<double>(N));
    lu_factorize(A,P);
    lu_substitute(A,P,inv);
//    std::cout<<"Inverse matrix : "<< inv<<std::endl;
//    return inv;
    double dx = 1.0/input(0, 0);
    inv(0, 0)= dx;
    return inv;
}



void Kalman::printObject() {
    double d = F(0, 0);
    std::cout<<"F = "<<d<<std::endl;
    std::cout<<"H = "<<H(0, 0)<<std::endl;
    std::cout<<"B = "<<B(0, 0)<<std::endl;
    std::cout<<"Q = "<<Q(0, 0)<<std::endl;
    std::cout<<"R = "<<R(0, 0)<<std::endl;
    std::cout<<"Current State Estimate = "<<current_state_estimate(0, 0)<<std::endl;
    std::cout<<"Current probability Estimate = "<<current_prob_estimate(0, 0)<<std::endl;

}


//
//namespace INV {
//    using namespace boost::numeric::ublas;
//    using namespace std;
//
///* Matrix inversion routine.
//Uses lu_factorize and lu_substitute in uBLAS to invert a matrix */
//    template<class T>
//    bool InvertMatrix(const matrix<T> &input, matrix<T> &inverse) {
//        typedef permutation_matrix<std::size_t> pmatrix;
//
//        // create a working copy of the input
//        matrix<T> A(input);
//
//        // create a permutation matrix for the LU-factorization
//        pmatrix pm(A.size1());
//
//        // perform LU-factorization
//        int res = lu_factorize(A, pm);
//        if (res != 0)
//            return false;
//
//        // create identity matrix of "inverse"
//        inverse.assign(identity_matrix<T>(A.size1()));
//
//        // backsubstitute to get the inverse
//        lu_substitute(A, pm, inverse);
//
//        return true;
//    }
//}