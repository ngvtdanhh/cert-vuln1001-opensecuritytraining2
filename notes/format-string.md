# 🧾 Format String Vulnerabilities – Vulnerabilities 1001 (OST2)

Format string vulnerabilities occur when untrusted input is used as the format string parameter in functions like `printf()`. This allows attackers to **read and/or write arbitrary memory**, and in some cases, gain code execution.

---

## 📌 1. Vulnerable Pattern

```c
#include <stdio.h>

void vulnerable(char *input) {
    printf(input);  // ❌ Dangerous – input is used directly
}
```

If the attacker supplies a string like %x %x %x, printf() will read data from the stack. With %n, they may write to memory.

## 🔬 2. Exploitation Goals

- 🧠 Information Disclosure (leak memory, addresses)

- ✏️ Arbitrary Write via %n to overwrite:

  - Return addresses

  - Function pointers

  - GOT/PLT entries

## 🧪 3. Realistic Payload Example

```bash

# Leak stack addresses
./vuln-format "%x %x %x %x"

# Write to memory using %n
python -c 'print("AAAA%08x%08x%n")' | ./vuln-format
```

## 🔐 4. Mitigations

| Protection       | Description                               | Can Bypass?                        |
| ---------------- | ----------------------------------------- | ---------------------------------- |
| Format Hardening | GCC `-Wformat`, use `printf("%s", input)` | ✅ Yes (only prevents careless use) |
| ASLR + NX        | Makes exploitation harder                 | ✅ Yes (info leak + ret2libc)       |
| Fortify Source   | Detects format issues in compile time     | ❌ May stop trivial cases           |

## 🧰 5. Analysis Tools

- ltrace ./vuln-format "%x %x %x" – traces libc function calls

- gdb, pwndbg, gef – dynamic debugging

- objdump -R – find GOT entries

- strings + readelf – static inspection

## 💻 6. Sample Vulnerable Code

See demo/vuln-format.c and exploit-format.py for a working PoC.

## 🧠 Pro Tips (CTF / Red Team)

- Look for %x, %p, %n, %s – if input is reflected directly into format functions

- Try %s to dump memory at stack positions

- %n → write primitive (but need address control)

- Combine with GOT overwrite for code execution

##  📚 References

- OpenSecurityTraining2 – Vulnerabilities 1001, Format String Modules

- Phrack 59 – "Smashing the Stack for Fun and Profit" - https://phrack.org/issues/59/7

- Format String Exploits (IOActive)








