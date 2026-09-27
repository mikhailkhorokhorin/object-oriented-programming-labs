# Lab 1. First Program: Removing Vowels

## Task

Read text line by line from standard input and print every line with all vowels removed.
Variant: the vowels are `a`, `e`, `i`, `o`, `u` in either case; all other characters, including digits, punctuation and non-ASCII bytes, are kept.
The logic lives in `removeVowels` and is covered by GoogleTest unit tests.

## Build and run

```bash
make run LAB=lab1 < lab1/tests/data/01.in
```

## Example

Input:

```text
Hello World
Moscow Aviation Institute
This website is for LOL!
```

Output:

```text
Hll Wrld
Mscw vtn nsttt
Ths wbst s fr LL!
```
