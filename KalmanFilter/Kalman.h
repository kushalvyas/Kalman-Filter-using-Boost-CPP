//
// Created by kushal on 13/9/16.
//

#ifndef KF_KALMAN_H
#define KF_KALMAN_H

#include "boost/numeric/ublas/matrix.hpp"



class Kalman {
public:
    boost::numeric::ublas::matrix<double> F;
    boost::numeric::ublas::matrix<double> H;
    boost::numeric::ublas::matrix<double> B;
    boost::numeric::ublas::matrix<double> Q;
    boost::numeric::ublas::matrix<double> R;
    boost::numeric::ublas::matrix<double> current_state_estimate;
    boost::numeric::ublas::matrix<double> current_prob_estimate;
    boost::numeric::ublas::matrix<double> I;




    Kalman();
    boost::numeric::ublas::matrix<double> getCurrentEstimate();
    void Step(boost::numeric::ublas::matrix<double> control_vector, boost::numeric::ublas::matrix<double> measurement_vector);
    void printObject();
    boost::numeric::ublas::matrix<double> multiply(boost::numeric::ublas::matrix<double> A, boost::numeric::ublas::matrix<double> B);
    boost::numeric::ublas::matrix<double> inverse(boost::numeric::ublas::matrix<double> input);
//    bool InvertMatrix(const matrix<T>& input, matrix<T>& inverse);

};


#endif //KF_KALMAN_H
