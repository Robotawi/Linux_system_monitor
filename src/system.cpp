#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

//What is the relationship between this class, and the LinuxParser namespace functions?\
For example, this class wants to get the uptime of the system with its UpTime() function.\
This UpTime() here can call the function with the same name in the LinuxParser namespace to get this data.

// TODO: Return the system's CPU
Processor &System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process> &System::Processes()
{
    pids_.clear();
    processes_.clear();

    pids_ = LinuxParser::Pids();
    for (auto pid : pids_)
    {
        processes_.emplace_back(std::move(Process(pid)));
    }

    std::sort(processes_.begin(), processes_.end());
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
/*Properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

long int System::UpTime() { return LinuxParser::UpTime(); }
