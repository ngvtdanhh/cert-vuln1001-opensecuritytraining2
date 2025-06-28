# ➕ Integer Overflow Vulnerabilities – Vulnerabilities 1001 (OST2)

Integer overflows happen when an arithmetic operation exceeds the maximum (or minimum) size a variable can hold, causing it to wrap around. This can lead to **buffer overflows**, **bypass of size checks**, or **unexpected logic flow**, which may result in memory corruption or privilege escalation.

---

## 📌 1. Vulnerable Example (C)

```c
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void process_input(size_t len) {
    char *buffer;

    // Intended to allocate len + 1 bytes
    buffer = (char *)malloc(len + 1);

    if (!buffer) {
        puts("Memory allocation failed");
        return;
    }

    memset(buffer, 'A', len + 1);
    buffer[len] = '\0';

    printf("Buffer: %s\n", buffer);
    free(buffer);
}
```

If len = SIZE_MAX, then len + 1 = 0 due to overflow.

→ malloc(0) returns a tiny chunk → memset() overflows.

## 🔎 2. Common Scenarios

| 📚 Scenario                 | 🔥 Effect                                   |
| --------------------------- | ------------------------------------------- |
| Unsigned int wraparound     | Size check passes, allocation fails         |
| Signed/unsigned confusion   | Negative input treated as huge unsigned int |
| Length calculation in loops | May cause OOB write                         |

## 🧪 3. Exploitation Vectors

- ❌ Bypass input validation

- 🛠️ Force allocation of small buffer

- 📦 Trigger heap overflow after malloc

- 🔁 Lead into memory corruption via logic flaw

## 🔐 4. Mitigations

| 🛡️ Technique                 | 📋 Description                                       | Bypassable?             |
| ----------------------------- | ---------------------------------------------------- | ----------------------- |
| **Compiler warnings**         | Use `-Wall`, `-Wextra`, `-Woverflow` in GCC/Clang    | ⚠️ Yes – dev may ignore |
| **Safe math libraries**       | Use `__builtin_add_overflow()` or `SafeInt` wrappers | ✅ Harder                |
| **Fuzzing + static analysis** | Tools like AFL, CodeQL, Infer can detect overflows   | ✅ Yes                   |
| **Input range checks**        | Manual sanitization before arithmetic                | ✅ If missed logic edge  |

## 🛠️ 5. Tools for Detection

- clang-analyzer, Infer, cppcheck – static code analyzers

- asan, ubsan – runtime sanitizers

- CodeQL – GitHub's semantic code scanner

- Fuzzers: AFL++, libFuzzer

## 📚 References

- OST2 – Vulnerabilities 1001: Integer Overflow

- CERT C Coding Standard – INTxx Rules

- Google's SafeInt (C++) - https://github.com/dcleblanc/SafeInt

