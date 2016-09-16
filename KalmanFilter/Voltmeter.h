//
// Created by kushal on 13/9/16.
//

#ifndef KF_VOLTMETER_H
#define KF_VOLTMETER_H


class Voltmeter {

public:
    double trueVoltage;
    double noiselevel;
    double voltagenoisyreadings[1000];

    Voltmeter(double tv, double noise);
    double getTrueVoltage();
    double getVoltageWithNoise(int counter);
    void generateVoltageWithNoise();


};


#endif //KF_VOLTMETER_H
