import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv("lorenz.csv")
trajs = df["traj"].unique()

cloud = [0, 1, 2, 3]
far = [4, 5, 6, 7]

cloud_colors = plt.cm.viridis(np.linspace(0.2, 0.9, len(cloud)))
far_colors = plt.cm.plasma(np.linspace(0.0, 0.5, len(far)))

# 3D attractor (cloud)
fig = plt.figure(figsize=(8, 6))
ax  = fig.add_subplot(111, projection="3d")
for i, color in zip(cloud, cloud_colors):
    g = df[df["traj"] == i]
    ax.plot(g["x"], g["y"], g["z"], lw=0.3, alpha=0.8, color=color,
            label=f"({g['x0'].iloc[0]:.2f}, {g['y0'].iloc[0]:.2f}, {g['z0'].iloc[0]:.2f})")
ax.set_title("Lorenz attractor with small cloud of initial conditions")
ax.set_xlabel("x"); ax.set_ylabel("y"); ax.set_zlabel("z")
ax.legend(fontsize=7)
plt.tight_layout()
plt.savefig("lorenz_3d_cloud.png", dpi = 150)

# 3D attractor (far pts.)
fig = plt.figure(figsize=(8, 6))
ax  = fig.add_subplot(111, projection="3d")
for i, color in zip(far, far_colors):
    g = df[df["traj"] == i]
    ax.plot(g["x"], g["y"], g["z"], lw=0.3, alpha=0.8, color=color,
            label=f"({g['x0'].iloc[0]:.0f}, {g['y0'].iloc[0]:.0f}, {g['z0'].iloc[0]:.0f})")
ax.set_title("Lorenz attractor with large initial conditions")
ax.set_xlabel("x"); ax.set_ylabel("y"); ax.set_zlabel("z")
ax.legend(fontsize=7)
plt.tight_layout()
plt.savefig("lorenz_3d_far.png", dpi = 150)

# x(t) for cloud
fig, ax = plt.subplots(figsize=(10, 4))
for i, color in zip(cloud, cloud_colors):
    g = df[df["traj"] == i]
    ax.plot(g["t"], g["x"], lw=0.6, alpha=0.8, color=color,
            label=f"({g['x0'].iloc[0]:.2f}, {g['y0'].iloc[0]:.2f}, {g['z0'].iloc[0]:.2f})")
ax.set_title("x(t) for nearby initial conditions (cloud)")
ax.set_xlabel("t"); ax.set_ylabel("x")
ax.legend(fontsize=7)
plt.tight_layout()
plt.savefig("lorenz_xt_cloud.png", dpi = 150)

# x(t) for far points
fig, ax = plt.subplots(figsize=(10, 4))
for i, color in zip(far, far_colors):
    g = df[df["traj"] == i]
    ax.plot(g["t"], g["x"], lw=0.6, alpha=0.8, color=color,
            label=f"({g['x0'].iloc[0]:.0f}, {g['y0'].iloc[0]:.0f}, {g['z0'].iloc[0]:.0f})")
ax.set_title("x(t) for far initial conditions")
ax.set_xlabel("t"); ax.set_ylabel("x")
ax.legend(fontsize=7)
plt.tight_layout()
plt.savefig("lorenz_xt_far.png", dpi = 150)

plt.show()