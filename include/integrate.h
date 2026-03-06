#pragma once

// A State must support scalar multiply-add: s + dt * deriv
// Explicit State types change per problem, so the integrators are generic.

template<typename S, typename F>
S euler(int N, double dt, S s, F f) {
    for (int i{}; i < N; i++)
        s = s + dt * f(i * dt, s);
    return s;
}

template<typename S, typename F>
S midpoint(int N, double dt, S s, F f) {
    for (int i{}; i < N; i++) {
        double t { i * dt };
        auto k   { f(t, s) };
        s = s + dt * f(t + dt/2, s + (dt/2) * k);
    }
    return s;
}

template<typename S, typename F>
S runge_kutta(int N, double dt, S s, F f) {
    for (int i{}; i < N; i++) {
        double t { i * dt };
        auto k1  { f(t, s) };
        auto k2  { f(t + dt/2, s + (dt/2) * k1) };
        auto k3  { f(t + dt/2, s + (dt/2) * k2) };
        auto k4  { f(t + dt,   s + dt     * k3) };
        s = s + (dt/6) * (k1 + 2*k2 + 2*k3 + k4);
    }
    return s;
}