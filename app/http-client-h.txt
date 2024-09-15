#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <stdio.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

char* fetch_url(const char* url);

#endif // HTTP_CLIENT_H
