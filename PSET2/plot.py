import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

df = pd.read_csv("lotka_volterra.csv")

step_sizes = sorted(df["dt"].unique())
methods    = ["euler", "rk4"]
titles     = {"euler": "Euler", "rk4": "Runge-Kutta 4"}

fig, axes = plt.subplots(len(methods), len(step_sizes),
                         figsize=(5 * len(step_sizes), 4 * len(methods)),
                         sharex=False, sharey=False)

for row, method in enumerate(methods):
    for col, dt in enumerate(step_sizes):
        ax = axes[row][col]
        subset = df[(df["method"] == method) & (df["dt"] == dt)]

        for c_idx, (curve_id, group) in enumerate(subset.groupby("curve_id")):
            ax.plot(group["x"], group["y"],
                    color=cm.viridis(c_idx / subset["curve_id"].nunique()),
                    linewidth=0.8, alpha=0.85)

        ax.set_title(f"{titles[method]},  Δt = {dt}", fontsize=10)
        ax.set_xlabel("Prey (x)")
        ax.set_ylabel("Predator (y)")
        ax.set_xlim(left=0)
        ax.set_ylim(bottom=0)
        ax.grid(True, alpha=0.3)

fig.suptitle("Lotka–Volterra Phase Curves\n"
             "k=1, l=1, a=0.1, b=0.075  |  T=60",
             fontsize=13, y=1.01)
plt.tight_layout()
plt.savefig("lotka_volterra.png", dpi=150)
plt.show()