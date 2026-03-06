#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/integrate.h"

struct State {
    double x, v;
    State operator+(State o)  const { return { x + o.x, v + o.v }; }
    State operator*(double s) const { return { x * s,   v * s   }; }
};
State operator*(double s, State st) { return st * s; }

int main() {

    std::vector<double> mus { 0.1, 0.5, 1.0, 2.0, 4.0, 10.0};

    double dt { 0.005 };
    double T  { 500.0 };
    int    N  { static_cast<int>(T / dt) };

    std::ofstream out("van_der_pol.csv");
    out << "mu,x,v\n";

    State s0 { 0.5, 0.0 };  // initial condition

    for (double mu : mus) {

        // convert Van der Pol to 
        // x' = v
        // v' = mu(1 - x^2)v - x
        auto f = [&](double t, State s) {
            return State { s.v, mu * (1 - s.x * s.x) * s.v - s.x };
        };

        State s = s0;
        for (int i{}; i <= N; i++) {
            out << std::format("{},{:.6f},{:.6f}\n", mu, s.x, s.v);
            s = runge_kutta(1, dt, s, f);
        }
    }
}