# Lab 3. Inheritance and Polymorphism: Quadrilaterals

## Task

Build a hierarchy of figures with the abstract base class `Figure` and the variant figures `Square`, `Rectangle` and `Trapezoid`, each given by four vertices.
Every figure computes its geometric center and area (`static_cast<double>`), supports `operator<<`, `operator>>`, `operator==`, copying and moving.
The dynamic array `Array` stores figures polymorphically, prints them, computes the total area and removes a figure by index.
The program reads figures from standard input and prints the whole array.

## Build and run

```bash
make run LAB=lab3 < lab3/tests/data/01.in
```

## Example

Input:

```text
square 0 0 2 0 2 2 0 2
rectangle 0 0 3 0 3 2 0 2
trapezoid 0 0 4 0 3 2 1 2
```

Output:

```text
Figure 1: (0, 0) (2, 0) (2, 2) (0, 2) Center: (1, 1) Area: 4
Figure 2: (0, 0) (3, 0) (3, 2) (0, 2) Center: (1.5, 1) Area: 6
Figure 3: (0, 0) (4, 0) (3, 2) (1, 2) Center: (2, 0.888889) Area: 6
Total area: 16
```

## Notes

The square area is $a^2$ and the rectangle area is $ab$, where $a$ and $b$ are the sides at vertex 1. The trapezoid area uses the shoelace formula, so the trapezoid may have any orientation:

$$
A = \frac{1}{2} \left| \sum_{i=1}^{n} \left(x_i y_{i+1} - x_{i+1} y_i\right) \right|, \qquad (x_{n+1}, y_{n+1}) = (x_1, y_1)
$$

The geometric center is the centroid of the figure's area, not the average of its vertices. For the trapezoid above it is $\left(2, \frac{8}{9}\right)$, while the vertex average is $(2, 1)$:

$$
C_x = \frac{1}{6A_s} \sum_{i=1}^{n} (x_i + x_{i+1}) \left(x_i y_{i+1} - x_{i+1} y_i\right), \qquad
C_y = \frac{1}{6A_s} \sum_{i=1}^{n} (y_i + y_{i+1}) \left(x_i y_{i+1} - x_{i+1} y_i\right)
$$

Here $A_s$ is the signed area, i.e. the sum without the absolute value. A degenerate figure with zero area uses the vertex average.

Vertices are stored in a `std::array`, so a moved-from figure stays valid.
