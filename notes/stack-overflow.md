# 🧠 Stack Buffer Overflow – Vulnerabilities 1001 (OST2)

Stack-based buffer overflows are one of the most classic and dangerous memory corruption vulnerabilities in C/C++ programs. This note summarizes the concept, how they occur, and how they can be exploited — as demonstrated in the *Vulnerabilities 1001* course by OpenSecurityTraining2.

---

## 📌 1. What is a Stack Buffer Overflow?

A **stack overflow** happens when data written to a local (stack) buffer exceeds its allocated size and overwrites adjacent memory – typically including saved registers like **EIP** or **return address**.

### 🔍 Vulnerable Example:

```c
void vulnerable() {
    char buffer[64];
    gets(buffer); // Dangerous: no bounds checking!
}
```

If an attacker inputs >64 bytes, they can overwrite the return address and hijack execution flow.

## 🔧 2. Demo Setup

✅ Compile with no protections:

```bash
gcc -fno-stack-protector -z execstack -no-pie vuln-stack.c -o vuln-stack
```

Make sure ASLR is disabled: echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

## ⚠️ 3. Exploitation Steps

- Overwrite return address with shellcode or jump to controlled memory

- May use NOP sled or ret2libc if protections are in place

- Payload: [padding][EIP][shellcode]

📌 Example Payload (Python 2):

```python 
payload = "A" * 72 + "\xef\xbe\xad\xde"  # Overwrites return address
```

## 🧪 4. Real Exploit Example

See demo/vuln-stack.c and exploit-stack.py for hands-on PoC.

## 🔒 5. Mitigations & Bypasses

| Protection   | Description                                       | Can Bypass?               |
| ------------ | ------------------------------------------------- | ------------------------- |
| **Canaries** | Stack protector using a guard value before return | Yes (leak or brute force) |
| **ASLR**     | Randomizes stack/heap addresses                   | Yes (info leak)           |
| **DEP/NX**   | Makes stack non-executable                        | Yes (ROP, ret2libc)       |
| **PIE**      | Position Independent Executables                  | Harder to ROP             |

## 💡 6. Pro Tips (Red Team / CTF)

- Use objdump -d, gdb, or pwndbg to analyze binary

- Leverage pattern_create.rb / pattern_offset.rb from Metasploit

- Try ROPgadget or ropper to build chain

## 📚 References

- OpenSecurityTraining2: Vulnerabilities 1001 – Modules 1–3

- SmashTheStack Wargame

- Buffer Overflow 101 – LiveOverflow - https://www.youtube.com/watch?v=1S0aBV-Waeo

