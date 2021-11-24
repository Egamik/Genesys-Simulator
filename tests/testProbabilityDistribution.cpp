/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/cppsimpletest.cc to edit this template
 */

/* 
 * File:   testProbabilityDistribution.cpp
 * Author: rlcancian
 *
 * Created on 23 de novembro de 2021, 18:30
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

#include "../tools/ProbabilityDistribution.h"
#include "../tools/Integrator_if.h"
#include "../tools/IntegratorDefaultImpl1.h"
#include "../kernel/statistics/SamplerDefaultImpl1.h"
#include "../kernel/statistics/CollectorDatafileDefaultImpl1.h"
#include "../kernel/statistics/StatisticsDataFileDefaultImpl.h"

void test1() {
    //std::cout << "testProbabilityDistribution test 1" << std::endl;

    Sampler_if* sampler = new SamplerDefaultImpl1();
    StatisticsDatafile_if *stat = new StatisticsDatafileDefaultImpl1();
    CollectorDatafile_if *collector = static_cast<CollectorDatafile_if*> (stat->getCollector());
    collector->setDataFilename("./datafile.txt");
    double x;
    for (unsigned short i = 0; i < 5e3; i++) {
        x = sampler->sampleNormal(100, 20);
        collector->addValue(x);
    }
    std::cout << "min: " << stat->min() << std::endl;
    std::cout << "max: " << stat->max() << std::endl;
    std::cout << "avg: " << stat->average() << std::endl;
    std::cout << "std: " << stat->stddeviation() << std::endl;
    std::cout << "e0: " << stat->halfWidthConfidenceInterval() << std::endl;
    std::cout << "med: " << stat->mediane() << std::endl;
    std::cout << "mod: " << stat->mode() << std::endl;
    for (unsigned short i = 1; i <= 4; i++) {
        std::cout << "qrt" << i << ": " << stat->quartil(i) << std::endl;
    }
    for (unsigned short i = 1; i <= 10; i++) {
        std::cout << "dec" << i << ": " << stat->decil(i) << std::endl;
    }
}

void test2() {
    //std::cout << "testProbabilityDistribution test 2" << std::endl;
    //std::cout << "%TEST_FAILED% time=0 testname=test2 (testProbabilityDistribution) message=error message sample" << std::endl;
    Integrator_if* integr = new IntegratorDefaultImpl1(1e-6, 1e3);
    double x = integr->integrate(0.0, 0.5, &ProbabilityDistribution::beta, 4.0, 2.0);
    std::cout << x << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% testProbabilityDistribution" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    //std::cout << "%TEST_STARTED% test1 (testProbabilityDistribution)" << std::endl;
    //test1();
    // std::cout << "%TEST_FINISHED% time=0 test1 (testProbabilityDistribution)" << std::endl;

    //std::cout << "%TEST_STARTED% test2 (testProbabilityDistribution)\n" << std::endl;
    test2();
    // std::cout << "%TEST_FINISHED% time=0 test2 (testProbabilityDistribution)" << std::endl;

    // std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

