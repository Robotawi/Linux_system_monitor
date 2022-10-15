#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem()
{
  string line{""};
  string key{""};
  string value{""};

  std::ifstream fstream(osreleaseFile);
  if (fstream.is_open())
  { // multiline file
    while (getline(fstream, line))
    {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::replace(line.begin(), line.end(), '=', ' ');

      std::istringstream stringstream(line);
      while (stringstream >> key >> value)
      {
        if (key == "PRETTY_NAME")
        {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
        value = "NULL"; // to indicate an error state if it happens
      }
    }
  }

  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel()
{
  string os{""};
  string kernel{""};
  string version{""};
  string line{""};
  std::ifstream fstream(procDir + versionFile);
  if (fstream.is_open())
  {
    std::getline(fstream, line);
    std::istringstream sstream(line);
    sstream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids()
{
  vector<int> pids;
  DIR *directory = opendir(procDir.c_str());
  struct dirent *file;
  while ((file = readdir(directory)) != nullptr)
  {
    // Is this a directory?
    if (file->d_type == DT_DIR)
    {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit))
      {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  float memTotal{0.0};
  float memFree{0.0};
  // float memAvailable{0.0};
  // float memBuffers{0.0};

  string line{""};
  string key{""};
  string value{""};

  std::ifstream fstream(procDir + meminfoFile);
  if (fstream.is_open())
  {
    while (getline(fstream, line))
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stringstream(line);
      while (stringstream >> key >> value)
      {
        if (key == "MemTotal")
        {
          memTotal = std::stof(value);
          continue;
        }
        if (key == "MemFree")
        {
          memFree = std::stof(value);
          break;
        }
      }
    }
    // after processing all lines. can be optimized?
    return (memTotal - memFree) / memTotal;
  }

  return -1.0; // to indicate a fault
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime()
{
  string line{""};
  string upTime{"0000"};

  std::ifstream filestream(procDir + uptimeFile);
  if (filestream.is_open())
  {
    getline(filestream, line);
    std::istringstream stringstream(line);
    stringstream >> upTime;
  }

  return std::stol(upTime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  string line{""};
  string key{""};
  string value{""};
  int processes{0};

  std::ifstream filestream(procDir + statFile);
  if (filestream.is_open())
  {
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      stringstream >> key >> value; 

      if(key == "processes"){
        processes = std::stoi(value); 
        return processes; 
      }
    }
  }

  return processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {

  string line{""};
  string key{""};
  string value{""};
  int proc_running{0};

  std::ifstream filestream(procDir+statFile);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      stringstream >> key >> value;

      if(key == "procs_running"){
        proc_running = std::stoi(value);
        return proc_running;
      }
    }
  }

  return proc_running;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }
