#include <string.h>
#include <stdbool.h>

/*
:param s: main string
:param t: substring

:return:
    The position at which the substring first appeared in the main string on successfully match
    -1 on failure

Worst time complexity: O(n * m)
Explanation: s = "aaaaaaaa....aaaaaaaa", t = "aaaaaaab", n = strlen(s), m = strlen(t)
*/
int brute_force(const char *s, const char *t) {
    size_t s_len = strlen(s);
    size_t t_len = strlen(t);
    if (s_len == 0 || t_len == 0 || s_len < t_len) return -1;

    unsigned int number_of_substring = s_len - t_len + 1;
    for (unsigned int i=0; i<number_of_substring; i++) {
        bool match = true;
        int cursor = i;
        for (size_t j=0; j<t_len; j++) {
            if (s[cursor++] != t[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }

    return -1;
}
