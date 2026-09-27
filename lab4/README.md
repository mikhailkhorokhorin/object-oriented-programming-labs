# Lab 4. Templates and Smart Pointers: Polygons

## Task

Rewrite the figure hierarchy as templates over the coordinate type `T` (constrained by the `Scalar` concept).
Variant: `Rhombus<T>`, `Pentagon<T>` and `Hexagon<T>`; vertices are owned by `std::unique_ptr<Point<T>[]>`.
The template container `Array<T>` stores `std::shared_ptr<Figure<T>>`, grows on demand, deep-copies figures and computes the total area.
The program reads figures with `double` coordinates from standard input and prints the array.

## Build and run

```bash
make run LAB=lab4 < lab4/tests/data/01.in
```

## Example

Input:

```text
rhombus 0 0 2 1 0 2 -2 1
pentagon 0 0 2 0 3 2 1 4 -1 2
hexagon 0 0 2 0 3 1 2 2 0 2 -1 1
```

Output:

```text
Figure 1: (0, 0) (2, 1) (0, 2) (-2, 1) Center: (0, 1) Area: 4
Figure 2: (0, 0) (2, 0) (3, 2) (1, 4) (-1, 2) Center: (1, 1.73333) Area: 10
Figure 3: (0, 0) (2, 0) (3, 1) (2, 2) (0, 2) (-1, 1) Center: (1, 1) Area: 6
Total area: 20
```

## Notes

The rhombus area uses its diagonals, $A = \frac{d_1 d_2}{2}$. The pentagon and hexagon use the shoelace formula:

$$
A = \frac{1}{2} \left| \sum_{i=1}^{n} \left(x_i y_{i+1} - x_{i+1} y_i\right) \right|, \qquad (x_{n+1}, y_{n+1}) = (x_1, y_1)
$$

The center is the centroid of the area, not the average of the vertices. For the pentagon above it is $\left(1, \frac{26}{15}\right)$, while the vertex average is $(1, 1.6)$:

$$
C_x = \frac{1}{6A_s} \sum_{i=1}^{n} (x_i + x_{i+1}) \left(x_i y_{i+1} - x_{i+1} y_i\right), \qquad
C_y = \frac{1}{6A_s} \sum_{i=1}^{n} (y_i + y_{i+1}) \left(x_i y_{i+1} - x_{i+1} y_i\right)
$$

Here $A_s$ is the signed area. A degenerate figure with zero area uses the vertex average.

Areas and centers are computed in `double` for every `T`, so integer coordinates are not truncated. The library is header-only (`lab4_core` is an `INTERFACE` target).
