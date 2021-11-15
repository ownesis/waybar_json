#ifndef __WAYBAR_JSON_H__
#define __WAYBAR_JSON_H__

#define JOBJ_NEW(t, k)                      \
    do {                                    \
        tmp = json_object_new_##t(args->k); \
        if (!tmp)                           \
            return NULL;                    \
    } while (0)

#define JOBJ_ADD(k)                                      \
    do {                                                 \
        if (json_object_object_add(jobj, #k, tmp) <  0)  \
            return NULL;                                 \
    } while (0)

#define JOBJ_ADDNEW(t, n)   \
    do {                    \
        JOBJ_NEW(t, n);     \
        JOBJ_ADD(n);        \
    } while (0)

struct Waybar_args {
    char *text;
    char *tooltip;
    char **class;
    size_t class_len;
    int percentage;
};

char *waybar_json(struct Waybar_args *);

#endif /* __WAYBAR_JSON_H__ */
