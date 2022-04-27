#ifndef _STR_UTILS_H
#define _STR_UTILS_H

#define MAX_STR_SIZE 64

void u32_to_str(unsigned value, char str[MAX_STR_SIZE]);
void u64_to_str(unsigned long long value, char str[MAX_STR_SIZE]);

#endif /* _STR_UTILS_H */