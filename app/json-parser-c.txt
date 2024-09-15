#include "json_parser.h"
#include <json-c/json.h>

void parse_and_print_json(const char* json_string) {
    json_object *jobj = json_tokener_parse(json_string);
    if (jobj != NULL) {
        printf("Parsed JSON data:\n%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_PRETTY));
        json_object_put(jobj);
    } else {
        printf("Failed to parse JSON data\n");
    }
}
