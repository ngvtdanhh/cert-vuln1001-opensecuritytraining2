// vuln-format.c
// Vulnerable Format String Demo – OST2 Style

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void win() {
    system("/bin/sh");
}

void vulnerable_function(char *input) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), input); // ⚠️ UNSAFE: format string vulnerability
    printf(buffer);                          // ⚠️ Double trouble!
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    vulnerable_function(argv[1]);

    return 0;
}
