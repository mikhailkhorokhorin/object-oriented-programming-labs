# Lab 5. Iterators and Allocators: Vector on a Custom Memory Resource

## Task

Implement `MemoryResource`, a `std::pmr::memory_resource` that records every allocated block in a `std::map` and reuses freed blocks instead of returning them to the system.
Implement the dynamic array `Vector<T>` that allocates through `std::pmr::polymorphic_allocator<T>` and exposes a forward iterator `VectorIterator<T>`.
The program fills vectors of `int` and of a struct through the custom resource and prints the contents and the block statistics.

## Build and run

```bash
make run LAB=lab5
```

## Example

Output:

```text
1 4 9 16 25
size 5, capacity 8
1 Alice 2.5
2 Bob 4.75
blocks in use: 2, free: 4
after scope: in use 0, free 6
```

## Notes

- A freed block is reused only if it is large enough and has at least the requested alignment; blocks are released with their original size and alignment.
- `Vector` follows the rule of five and keeps the memory resource of the source on copy.
- The library is header-only (`lab5_core` is an `INTERFACE` target). The standard iterator type names (`value_type`, `iterator`, ...) are allowed by the naming rules in the root `.clang-tidy`.
