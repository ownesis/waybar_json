#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <waybar_json.h>

unsigned int count_digit_in_number(unsigned int i) {
    unsigned int ret = 1;
    while (i /= 10) ret++;

    return ret;
}

int main(void) {
    char *use_str = NULL;
    char *ret = NULL;    
    char **class = NULL;
    size_t class_len = 0;
    unsigned int count_digit = 0;
    char *warn_class[] = {"warning", "caution"};
    char *crit_class[] = {"critical"};
    char *good_class[] = {"good"};

    struct statvfs stats = {0};

    statvfs("/", &stats);

    size_t frees = (stats.f_bsize * stats.f_bavail) / pow(1024, 3);
    size_t total = (stats.f_bsize * stats.f_blocks) / pow(1024, 3);
    size_t use = (total - frees);
    size_t percent = (use * 100)/total;

    count_digit = count_digit_in_number(use);

    use_str = malloc(count_digit+1);
    if (!use_str)
        return 1;

    memset(use_str, 0, count_digit+1);

    snprintf(use_str, count_digit+1, "%ld", use);

    if (percent < 50) {
        class = good_class;
        class_len = 1;
    } else if (percent < 80) {
        class = warn_class;
        class_len = 2;
    } else {
        class = crit_class;
        class_len = 1;
    }

    struct Waybar_args args = {
        .text       = use_str,
        .tooltip    = "false",
        .class      = class,
        .class_len  = class_len,
        .percentage = percent
    };

    ret = waybar_json(&args);

    puts(ret);
    free(ret);
    free(use_str);
    
    return 0;
}
