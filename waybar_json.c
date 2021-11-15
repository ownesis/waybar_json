#include <string.h>
#include <json-c/json.h>

#include "waybar_json.h"

char *waybar_json(struct Waybar_args *args) {
    json_object *jobj = NULL;
    json_object *tmp = NULL;
    char *ret = NULL;

    jobj = json_object_new_object();
   
    if (!jobj)
        return NULL;

    JOBJ_ADDNEW(string, text);
    JOBJ_ADDNEW(string, tooltip);
    JOBJ_ADDNEW(uint64, percentage);

    JOBJ_NEW(array_ext, class_len);

    for (size_t i = 0; i < args->class_len; i++) {
        if (json_object_array_add(tmp, json_object_new_string(args->class[i])))
            return NULL;
    }

    JOBJ_ADD(class);

    ret = strdup(json_object_to_json_string(jobj));

    json_object_put(jobj);

    return ret;
}
