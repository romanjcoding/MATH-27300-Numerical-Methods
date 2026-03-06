import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("van_der_pol.csv")
mus = sorted(df["mu"].unique())

fig, axes = plt.subplots(1, len(mus), figsize=(4 * len(mus), 4), sharey=True)

for ax, mu in zip(axes, mus):
    grp = df[df["mu"] == mu]
    ax.plot(grp["x"], grp["v"], lw=0.6, color="blue")
    ax.set_title(f"μ = {mu}")
    ax.set_xlabel("x")
    ax.axhline(0, color="k", lw=0.3)
    ax.axvline(0, color="k", lw=0.3)

axes[0].set_ylabel("x'")
fig.suptitle("Van der Pol phase plane", fontsize=13)
plt.tight_layout()
plt.savefig("van_der_pol.png", dpi=150)
plt.show()