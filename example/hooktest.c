#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inlineHook.h"

int (*old_puts)(const char *) = NULL;

int new_puts(const char *string)
{
    char *success = "== inlineHook success ==";
    char *msg = (char *) malloc(strlen(string) + strlen(success));
    sprintf(msg, "%s%s", string, success);
    old_puts(msg);
    return 0;
}

int hook()
{
    if (registerInlineHook((uint32_t) puts, (uint32_t) new_puts, (uint32_t **) &old_puts) != ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) puts) != ELE7EN_OK) {
        return -1;
    }

    return 0;
}

int unHook()
{
    if (inlineUnHook((uint32_t) puts) != ELE7EN_OK) {
        return -1;
    }

    return 0;
}

int main()
{
    puts("test");
    hook();
    puts("test");
    unHook();
    puts("test");

    return 0;
}
