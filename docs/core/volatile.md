---
title: "volatile"
---


Tells the compiler to avoid aggressive memory optimizations for a variable.

## When to Use

- Memory-mapped hardware registers
- Variables modified by signal handlers
- Variables accessed by multiple threads (though prefer `std::atomic`)

## Example: Memory-Mapped Register

```cpp
// Without volatile - compiler may optimize away the loop
int* ptr1 = (int*)0x1234;
while (*ptr1 == 0) { } // May become infinite loop!

// With volatile - forces memory read each iteration
volatile int* ptr2 = (volatile int*)0x1234;
while (*ptr2 == 0) { } // Actually reads from memory
```

The compiler might optimize the first loop by reading `*ptr1` once and caching it in a register, never seeing external changes.

## Example: Out-of-Bounds Access

```cpp
// Without volatile - UB, compiler may remove entirely with -O1
int arr[5];
arr[5] = 10; // May be optimized away

// With volatile - generates the actual memory access
volatile int arr2[5];
arr2[5] = 10; // Code generated (will likely crash)
```

## Key Points

- `volatile` prevents optimization, not thread-safety
- Use `std::atomic` for thread-safe access
- Common in embedded/systems programming
- Can combine with `const`: `const volatile int*`

## See Also

- [const](const.md) - const qualifier
- [memory-order](../memory/memory-order.md) - memory ordering for atomics
