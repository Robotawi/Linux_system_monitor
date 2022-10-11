#include "ncurses_display.h"
#include "system.h"

//The main instantiates a System representing the Linux system. It has other classes\
there is a container of threads/process, Processor, and all of them call the linux_parser\
the Ncurses takes the system and outputs its data on the display 

int main() {
  System system;
  NCursesDisplay::Display(system);
}