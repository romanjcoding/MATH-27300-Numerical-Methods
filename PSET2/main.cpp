#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/integrate.h"

struct Params { double k, l, a, b; };
Params p { .k=1.0, .l=1.0, .a=0.1, .b=0.075 };

struct State {
    double x, y;
    State operator+(State o)  const { return { x + o.x, y + o.y }; }
    State operator*(double s) const { return { x * s,   y * s   }; }
};
State operator*(double s, State st) { return st * s; }

// x' = kx - axy,  
// y' = bxy - ly
auto f = [](double t, State s){
    return State {
        p.k * s.x - p.a * s.x * s.y,
        p.b * s.x * s.y - p.l * s.y
    };
};

int main() {
    double T { 60.0 };

    std::vector<State> initials    { {10,5}, {15,5}, {20,5}, {10,10}, {30,4} };
    std::vector<double> step_sizes { 0.25, 0.1, 0.02, 0.005 };

    std::ofstream out("lotka_volterra.csv");
    out << "curve_id,method,x,y,dt\n";

    int id { 0 };
    for (double dt : step_sizes) {
        int N { static_cast<int>(T / dt) };
        for (auto& s0 : initials) {
            State s { s0 };
            for (int i{}; i <= N; i++) {
                out << std::format("{},euler,{:.6f},{:.6f},{}\n", id, s.x, s.y, dt);
                s = euler(1, dt, s, f);
            }
            id++;

            s = s0;
            for (int i{}; i <= N; i++) {
                out << std::format("{},rk4,{:.6f},{:.6f},{}\n", id, s.x, s.y, dt);
                s = runge_kutta(1, dt, s, f);
            }
            id++;
        }
    }
}