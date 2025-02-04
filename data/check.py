import numpy as np
import matplotlib.pyplot as plt

# Constants
G = 6.674e-11  # Gravitational constant (m^3/kg/s^2)
M = 5.972e24   # Mass of Earth (kg)
R_Earth = 6371e3  # Radius of Earth (m)
r0 = R_Earth + 500e3  # Initial orbit radius (m)
v0 = 7.5e3  # Circular orbit velocity (m/s)

# Initial conditions
x, y = r0, 0
vx, vy = 0, v0
h = 10  # Time step (s)
T = 1000  # Simulation time (s)
steps = int(T / h)

# Function for acceleration
def acceleration(x, y):
    r = np.sqrt(x**2 + y**2)
    a_x = -G * M * x / r**3
    a_y = -G * M * y / r**3
    return a_x, a_y

# RK4 loop
positions = []
for _ in range(steps):
    positions.append((x, y))

    # Compute k values
    ax1, ay1 = acceleration(x, y)
    k1_vx, k1_vy = ax1 * h, ay1 * h
    k1_x, k1_y = vx * h, vy * h

    ax2, ay2 = acceleration(x + k1_x/2, y + k1_y/2)
    k2_vx, k2_vy = ax2 * h, ay2 * h
    k2_x, k2_y = (vx + k1_vx/2) * h, (vy + k1_vy/2) * h

    ax3, ay3 = acceleration(x + k2_x/2, y + k2_y/2)
    k3_vx, k3_vy = ax3 * h, ay3 * h
    k3_x, k3_y = (vx + k2_vx/2) * h, (vy + k2_vy/2) * h

    ax4, ay4 = acceleration(x + k3_x, y + k3_y)
    k4_vx, k4_vy = ax4 * h, ay4 * h
    k4_x, k4_y = (vx + k3_vx) * h, (vy + k3_vy) * h

    # Update positions and velocities
    x += (k1_x + 2*k2_x + 2*k3_x + k4_x) / 6
    y += (k1_y + 2*k2_y + 2*k3_y + k4_y) / 6
    vx += (k1_vx + 2*k2_vx + 2*k3_vx + k4_vx) / 6
    vy += (k1_vy + 2*k2_vy + 2*k3_vy + k4_vy) / 6

# Plot the orbit
positions = np.array(positions)
plt.plot(positions[:, 0], positions[:, 1], label="Satellite Path")
plt.scatter([0], [0], color="red", label="Earth")  # Earth at (0,0)
plt.xlabel("x position (m)")
plt.ylabel("y position (m)")
plt.title("Satellite Orbit using RK4")
plt.legend()
plt.axis("equal")
plt.show()
