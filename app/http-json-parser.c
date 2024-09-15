#include <stdio.h>
#include <stdlib.h>
#include "http_client.h"
#include "json_parser.h"

int main(void) {
    const char* url = "https://api.example.com/data.json";
    char* json_data = fetch_url(url);

    if (json_data) {
        printf("Received data from %s\n", url);
        parse_and_print_json(json_data);
        free(json_data);
    } else {
        printf("Failed to fetch data from %s\n", url);
    }

    return 0;
}
