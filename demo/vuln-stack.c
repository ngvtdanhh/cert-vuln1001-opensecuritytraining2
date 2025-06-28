// vuln-stack.c
// Vulnerable Stack Buffer Overflow Demo – OST2 Style

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void win() {  
    system("/bin/sh");
}

void vulnerable_function(char *input) {
    char buffer[64];

    strcpy(buffer, input);  // ❌ Vulnerability: no bounds checking

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }

    printf("[*] Address of win(): %p\n", (void *)win);
    vulnerable_function(argv[1]);

    printf("[*] Program finished normally.\n");
    return 0;
}
