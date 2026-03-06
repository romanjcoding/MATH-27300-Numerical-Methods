#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>
#include "../include/integrate.h"

struct State {
    double x, y, z;
    State operator+(State o)  const { return { x+o.x, y+o.y, z+o.z }; }
    State operator*(double s) const { return { x*s,   y*s,   z*s   }; }
};
State operator*(double s, State st) { return st * s; }

struct Params { double sigma, rho, beta; };

int main() {
    Params p { .sigma = 10.0, .rho = 28.0, .beta = 8.0/3.0 };

    std::vector<State> initials {
        
        // Cloud
        { 0.0,  1.0,  0.0 }, // 0
        { 0.01, 1.0,  0.0 }, // 1
        { 0.0,  1.01, 0.0 }, // 2
        { 0.01, 1.01, 0.0 }, // 3

        // Far points
        { 30.0,  30.0,  30.0 }, // 4
        { -20.0, 10.0,  40.0 }, // 5
        { 0.0,   0.0,  50.0  }, // 6
        { 80.0, -80.0,  1.0  }, // 7

    };

    double dt { 0.001 };
    double T  { 60.0 };
    int N     { static_cast<int>(T / dt) };

    std::ofstream out("lorenz.csv");
    out << "traj,x0,y0,z0,t,x,y,z\n";

    auto f = [&](double t, State s) {
        return State {
            p.sigma * (s.y - s.x),
            s.x * (p.rho - s.z) - s.y,
            s.x * s.y - p.beta * s.z
        };
    };

    int id { 0 }; 
    for (auto& s0 : initials) {
        State s { s0 };
        for (int i{}; i <= N; i++) {
            out << std::format("{},{:.3f},{:.3f},{:.3f},{:.4f},{:.6f},{:.6f},{:.6f}\n",
                                id, s0.x, s0.y, s0.z, i * dt, s.x, s.y, s.z);
            s = runge_kutta(1, dt, s, f);
        }
        id++;
    }
}