#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

enum logLevel
{
    FATAL,
    ERROR,
    WARNING,
    VERBOSE
};

void DBG_PRINT(int level, const char *format, ...)
{
    return;
}

#endif