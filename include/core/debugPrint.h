#ifndef DEBUGPRINT_H
#define DEBUGPRINT_H

#define CONFIG_ENABLE_DEBUG
#ifdef CONFIG_ENABLE_DEBUG

#include <stdio.h>

#define DBG_ERR(...)                                    \
do {                                                    \
        printf("ERROR: " __VA_ARGS__);                  \
        printf("\n ---FILE: %s, FUNC: %s, LINE: %d---\n\n", __FILE__, __func__, __LINE__);                                   \
} while (0)

#define DBG_WARN(...)                                    \
do {                                                    \
        printf("WARNING: " __VA_ARGS__);                  \
        printf("\n");                                   \
} while (0)

#define DBG_OUT(...)                                    \
do {                                                    \
        printf("DEBUG: " __VA_ARGS__);                  \
        printf("\n");                                   \
} while (0)

#endif

#endif