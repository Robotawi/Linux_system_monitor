#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

// This is not a class, but a namespace. The reason is that there are no object/member level data that needs to be persisted within the parser.
// It is a namespace within which different functions and constants are presented.

namespace LinuxParser
{
  // Paths constants
  const std::string procDir{"/proc/"};
  const std::string cmdlineFile{"/cmdline"};
  const std::string cpuinfoFile{"/cpuinfo"};
  const std::string statusFile{"/status"};
  const std::string statFile{"/stat"};
  const std::string uptimeFile{"/uptime"};
  const std::string meminfoFile{"/meminfo"};
  const std::string versionFile{"/version"};
  const std::string osreleaseFile{"/etc/os-release"};
  const std::string passwdFile{"/etc/passwd"};

  // System
  float MemoryUtilization();
  long UpTime();
  std::vector<int> Pids();
  int TotalProcesses();
  int RunningProcesses();
  std::string OperatingSystem();
  std::string Kernel();

  // CPU
  enum CPUStates
  {
    kUser_ = 0,
    kNice_,
    kSystem_,
    kIdle_,
    kIOwait_,
    kIRQ_,
    kSoftIRQ_,
    kSteal_,
    kGuest_,
    kGuestNice_
  };
  float CpuUtilization();
  long Jiffies();
  long ActiveJiffies();
  long ActiveJiffies(int pid);
  long IdleJiffies();

  // Processes
  std::string Command(int pid);
  std::string Ram(int pid);
  std::string Uid(int pid);
  std::string User(int pid);
  long int UpTime(int pid);
}; // namespace LinuxParser

#endif