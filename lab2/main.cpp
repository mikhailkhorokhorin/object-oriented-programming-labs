#include "money.hpp"

int main() {
    Money a("100.50");
    Money b(250.75);

    Money sum = Money::add(a, b);
    Money diff = Money::subtract(b, a);

    a.print();
    b.print();
    sum.print();
    diff.print();

    return 0;
}
