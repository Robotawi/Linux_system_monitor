#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization()
{   
    // Return instant CPU utilization
    // cpuTimes.at(0) is the total cpu time 
    // cpuTimes.at(1) is the idle cpu time

    // Reference: see this https://rosettacode.org/wiki/Linux_CPU_utilization
    
    cpuTimes = LinuxParser::CpuUtilization();
    deltaTotalTime = cpuTimes.at(0) - prevTotalTime; 
    deltaIdleTime = cpuTimes.at(1) - prevIdleTime; 

    cpuUtil = 1 - (deltaIdleTime/deltaTotalTime); 

    prevTotalTime = cpuTimes.at(0);
    prevIdleTime = cpuTimes.at(1);

    return cpuUtil;

    // For the aggregate CPU utilization,\
    cpuUtil = 1 - (cpuTimes.at(1)/cpuTimes.at(0)) would be enough
}