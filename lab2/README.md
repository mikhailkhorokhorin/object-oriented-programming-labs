# Lab 2. Classes and Dynamic Memory: Money

## Task

Implement the class `Money` for non-negative amounts of rubles and kopecks stored as an array of decimal digits (least significant first).
Variant: the amount is created from a string like `123.45` or from a `double`; the class provides addition, subtraction (negative results are rejected) and all comparisons as static methods, plus conversion to a string and to a `double`.
The program reads pairs of amounts and prints their sum and difference.

## Build and run

```bash
make run LAB=lab2 < lab2/tests/data/01.in
```

## Example

Input:

```text
100.50 250.75
0.50 0.50
100.00 99.99
```

Output:

```text
100.50 + 250.75 = 351.25
100.50 < 250.75
0.50 + 0.50 = 1.00
0.50 - 0.50 = 0.00
100.00 + 99.99 = 199.99
100.00 - 99.99 = 0.01
```

## Notes

- Digits are kept in a `std::vector<unsigned char>`, so copying and assignment follow the rule of zero.
- Every result is normalized (no leading zeros), so `equals` and the comparisons work on any operands.
- An invalid amount or an amount without a pair stops the program with exit code 1.
