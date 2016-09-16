//
// Created by kushal on 13/9/16.
//

#include "Voltmeter.h"
#include "boost/random.hpp"
#include "boost/random/normal_distribution.hpp"
#include "random"
#include "iomanip"
#include "map"

Voltmeter::Voltmeter(double tv, double noise) {
    trueVoltage = tv;
    noiselevel = noise;

}

double Voltmeter::getTrueVoltage() {

    return trueVoltage;
}

void Voltmeter::generateVoltageWithNoise() {

    boost::mt19937 *rng = new boost::mt19937();
    rng->seed(time(NULL));
    boost::normal_distribution<> distribution(trueVoltage, noiselevel);
    boost::variate_generator<boost::mt19937, boost::normal_distribution<> > dist(*rng, distribution);

    for(int i=0;i<1000;i++){
        voltagenoisyreadings[i] = dist();
//        std::cout<<dist()<<std::endl;
    }

}


double Voltmeter::getVoltageWithNoise(int counter){
    return voltagenoisyreadings[counter];
}