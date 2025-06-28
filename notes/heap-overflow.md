# 🧱 Heap Overflow Vulnerabilities – Vulnerabilities 1001 (OST2)

Heap overflows occur when a program writes beyond the bounds of a dynamically allocated memory buffer. This may allow an attacker to corrupt adjacent heap metadata or overwrite function pointers, leading to **arbitrary code execution** or **control flow hijacking**.

---

## 📌 1. What is a Heap Overflow?

```c
char *buffer = malloc(64);
strcpy(buffer, attacker_input); // ❌ no bounds checking!
```

If attacker_input is >64 bytes, it overwrites heap structures and possibly other allocations, enabling heap exploitation.

## 🧪 2. Real-World Attack Goals

- 📦 Corrupt adjacent heap chunks or metadata (e.g., chunk size, pointers)

- ✏️ Overwrite function pointers stored on heap

- 🔁 Trigger reuse of corrupted chunk (UAF → exploit)

- 🚪 Redirect control flow: __free_hook, vtable, or ROP

## 🔧 3. Demo Setup (No Protection)

```bash
gcc -m32 -g -z execstack -no-pie -fno-stack-protector vuln-heap.c -o vuln-heap
```

## 💡 Use libc-database to match libc version for ret2libc / hook exploitation.

## 🧨 4. Common Techniques

| Technique            | Description                                             |
| -------------------- | ------------------------------------------------------- |
| **House of Spirit**  | Fake chunk in controlled memory                         |
| **House of Force**   | Overwrite `top_chunk` size to gain arbitrary allocation |
| **Fastbin Dup**      | Create double-free condition to reuse freed chunks      |
| **Tcache Poisoning** | Overwrite tcache freelist to control malloc return      |

## 🧰 5. Analysis & Tools

- gdb, pwndbg, gef – visualize heap & allocations

- ltrace, valgrind, heaptrace – monitor memory calls

- libc-database – find offsets for hooks like __free_hook, __malloc_hook

## 💻 6. Sample Vulnerable Code

See demo/vuln-heap.c and exploitation script exploit-heap.py

## 🔐 7. Heap Hardening Techniques

| Mitigation             | Description                                           | Can Bypass?                  |
| ---------------------- | ----------------------------------------------------- | ---------------------------- |
| **Safe unlinking**     | Checks integrity before unlinking chunks (glibc ≥2.7) | ✅ With proper chunk crafting |
| **Tcache**             | Thread-local cache for malloc (glibc ≥2.26)           | ✅ Poisoning possible         |
| **ASLR**               | Randomizes heap base addresses                        | ✅ Info leak required         |
| **Pointer Encryption** | Protects freelist pointers (glibc ≥2.32)              | 🔶 Harder, needs leak + math |

## 🧠 Pro Tips (CTF / Red Team)

- Always check glibc version using ldd --version

- Practice on heaplab, how2heap, and glibc-all-in-one

- Combine heap overflow + UAF + leak = powerful chain

- Look for overwritten vtable, function ptr, or hook for control

## 📚 References

- OpenSecurityTraining2 – Vulnerabilities 1001, Heap Modules

- how2heap - https://github.com/shellphish/how2heap

- heap-exploitation – LiveOverflow - https://www.youtube.com/playlist?list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN

- glibc-all-in-one - https://github.com/matrix1001/glibc-all-in-one


