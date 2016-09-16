//
// Created by kushal on 17/9/16.
//

#include "Plot.h"
#include <iostream>
#include "fstream"
#include "vector"
#include "string"

using namespace std;



void Plot::showPlot(string x){
    string cmd = "python ../plot/python_plot.py "+x;
    system(cmd.c_str());
//    system("py    thon ../plot/python_plot.py");
}



void Plot::writeToFile(string filename,  vector<double> v1, vector<double> v2, vector<double> v3){
    ofstream output_file(filename);
    for(int i=0; i<v1.size(); i++){
        string each;
        each += boost::lexical_cast<string>(v1[i]);
        each +=",";
        each += boost::lexical_cast<string>(v2[i]);
        each +=",";
        each += boost::lexical_cast<string>(v3[i]);
        each += "\n";
//        cout<<each<<endl;
        output_file << each;
    }
    output_file.close();
}

