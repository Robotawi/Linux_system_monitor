#include <string>

#include "format.h"

using std::string;
using std::to_string;

string Format::FormatZero(long times)
{
    return times < 10 ? "0" + to_string(times) : to_string(times);
}

string Format::ElapsedTime(long seconds)
{
    int hours = seconds / 3600;
    seconds %= 3600;

    int mins = seconds / 60;
    seconds %= 60;

    return FormatZero(hours) + ":" + FormatZero(mins) + ":" + FormatZero(seconds);
}