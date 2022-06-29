/* date = June 29th 2022 0:50 pm */

#ifndef LOGGER_H
#define LOGGER_H

typedef enum {LT_INFO, LT_WARN, LT_ERROR, LT_DEBUG} ELogType;

void Println(ELogType type, const char* format, ...);


#endif //LOGGER_H
