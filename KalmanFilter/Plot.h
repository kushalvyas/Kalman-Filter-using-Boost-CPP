//
// Created by kushal on 17/9/16.
//

#ifndef KF_PLOT_H
#define KF_PLOT_H

#include "iostream"
#include "vector"
#include "string"

class Plot {
public:
    void showPlot(std::string x);
    void writeToFile( std::string filename, std::vector<double> v1, std::vector<double> v2, std::vector<double> v3);

};


#endif //KF_PLOT_H
