#include <iostream>
#include "interval.h"


int main() {
    interval X, S;
    while (true) {
        std::cout << "Enter the left boundary of the interval> ";
        std::cin >> X.left;
        std::cout << "Enter the right boundary of the interval> ";
        std::cin >> X.right;
        S = fold(subtraction(fold(-2, multiply(3, X)), multiply(2, multiply(X, X))), multiply(multiply(X, X), X));
        //S=
        std::cout << "Answer =[ " << S.left << " ; " << S.right << " ]" << std::endl;
    }
}
