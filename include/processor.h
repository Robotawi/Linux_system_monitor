#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<array>

class Processor
{
public:
    Processor() : prevIdleTime(0.0), prevTotalTime(0.0), deltaIdleTime(0.0), deltaTotalTime(0.0), cpuUtil(0.0) {}
    float Utilization();

private:
    std::array<float, 2> cpuTimes;
    float prevIdleTime;
    float prevTotalTime;
    float deltaIdleTime;
    float deltaTotalTime;
    float cpuUtil;
};

#endif