#include "DateUtil.h"
#include <ctime>
#include <cstdio>

void getCurrentDate(char* date, int size) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    snprintf(date, size, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
} 