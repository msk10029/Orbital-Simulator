import pandas as pd
import matplotlib.pyplot as plt

# Load CSV data
euler_data = pd.read_csv("data/euler_results.csv")
rk4_data = pd.read_csv("data/Rk4_results.csv")
#rk3_data = pd.read_csv("data/rk3_results.csv")

# Plot X vs Y trajectory
plt.figure(figsize=(8, 8))
plt.plot(euler_data["x"], euler_data["y"], label="Euler Method", linestyle="dashed", color="red")
#plt.plot(euler_data['time'],euler_data["x"], label="Euler Method", linestyle="dashed", color="red")
#plt.plot(rk4_data['time'], rk4_data["x"], label="RK4 Method", linestyle="solid", color="blue")
#plt.plot(rk3_data['time'], rk3_data["x"], label="RK3 Method", linestyle="solid", color="green")
plt.plot(rk4_data["x"],rk4_data['y'], label="RK4 Method", linestyle="dotted", color="blue")
# plt.plot(rk3_data["x"],rk3_data['y'], label="RK3 Method", linestyle="-.", color="green")

# Labels and Legend
plt.xlabel("X Position (km)")
plt.ylabel("Y Position (km)")
plt.title("Orbital Path: Euler vs RK4")
plt.legend()
plt.grid()
plt.axis("equal")

# Show Plot
plt.show()
