#include <iostream>
#include "fstream"
#include "Voltmeter.cpp"
#include "Kalman.cpp"
#include "Plot.cpp"

using namespace std;

int main() {

    cout << "Kalman filteR" << endl;
    Kalman kf;
    kf.printObject();
    Voltmeter voltmeter(1.25, 0.25);
    voltmeter.generateVoltageWithNoise();
    vector<double> measuredVoltage;
    vector<double> trueVoltageVector;
    vector<double> kalman;
    int numsteps = 500;
    for(int i=0;i<numsteps;i++){
        double measured = voltmeter.getVoltageWithNoise(i);
//        cout<<measured<<endl;
        measuredVoltage.push_back(measured);
        double tv = voltmeter.getTrueVoltage();
        trueVoltageVector.push_back(tv);
        boost::numeric::ublas::matrix<double> tmp_kv = kf.getCurrentEstimate();
        double t_kv = tmp_kv(0, 0);
        kalman.push_back(t_kv);
//        cout<<"Kalman Value : "<<t_kv<<endl;
        boost::numeric::ublas::matrix<double> zeroMtx(1,1);
        boost::numeric::ublas::matrix<double> measuredMtx(1,1);
        zeroMtx(0, 0) = 0;
        measuredMtx(0, 0) = measured;
        kf.Step(zeroMtx, measuredMtx);
    }

//    for(int i=0;i<kalman.size();i++){
//        printf("True Val : %lf , Measured Value : %lf, Kalman Value : %lf\n",trueVoltageVector[i], measuredVoltage[i], kalman[i]);
//    }

    Plot plotter;
    plotter.writeToFile("dummy.txt", trueVoltageVector, measuredVoltage, kalman);
    plotter.showPlot("dummy.txt");
    return 0;
}