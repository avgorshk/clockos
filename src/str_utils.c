#include "str_utils.h"

#define ASCII_ZERO 48

int get_str_len(char str[MAX_STR_SIZE]) {
    int len = 0;
    while (str[len] != '\0') {
        len += 1;
    }
    return (len >= MAX_STR_SIZE ? 0 : len);
}

void revert(char str[MAX_STR_SIZE]) {
    int len = get_str_len(str);
    if (len >= MAX_STR_SIZE) {
        return;
    }

    for (int i = 0; i < len / 2; ++i) {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

char digit_to_char(unsigned digit) {
    digit = digit % 10;
    return digit + ASCII_ZERO;
}

void u32_to_str(unsigned value, char str[MAX_STR_SIZE]) {
    if (value == 0) {
        str[0] = digit_to_char(0);
        str[1] = '\0';
    } else {
        int pos = 0;
        while (value > 0) {
            unsigned digit = value % 10;
            value /= 10;

            str[pos] = digit_to_char(digit);
            pos += 1;
        }
        str[pos] = '\0';
        revert(str);
    }
}

void u64_to_str(unsigned long long value, char str[MAX_STR_SIZE]) {
    if (value == 0) {
        str[0] = digit_to_char(0);
        str[1] = '\0';
    } else {
        int pos = 0;
        while (value > 0) {
            unsigned digit = value % 10;
            value /= 10;

            str[pos] = digit_to_char(digit);
            pos += 1;
        }
        str[pos] = '\0';
        revert(str);
    }
}