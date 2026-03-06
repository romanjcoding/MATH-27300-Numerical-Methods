#include <cmath>
#include <numbers>
#include <format>
#include <iostream>
#include "../include/integrate.h"

auto f = [](double t, double x) { return x; }; // x' = x

void print_table(std::string name, auto method) {
    std::cout << std::format("\n=== {} ===\n", name);
    std::cout << std::format("{:>10}  {:>20}  {:>20}\n", "N", "x(1) approx", "error");
    for (int k{10}; k <= 20; k++) {
        int N { 1 << k };
        double approx { method(N, 1.0 / N, 1.0, f) };
        double error  { std::abs(approx - std::numbers::e) };
        std::cout << std::format("{:>10}  {:>20.15f}  {:>20.6e}\n", N, approx, error);
    }
}

int main() {
    std::cout << std::format("Exact e = {:.15f}\n", std::numbers::e);
    print_table("Euler", euler<double, decltype(f)>);
    print_table("Midpoint", midpoint<double, decltype(f)>);
    print_table("Runge-Kutta", runge_kutta<double, decltype(f)>);
}