# plot_restart.py
import numpy as np
import matplotlib.pyplot as plt

# 讀取我們手上的重啟 CSV 檔案
csv_filename = "solution_flow_00199.csv"

print(f"正在讀取重啟檔案: {csv_filename}...")
# SU2 的 CSV 通常第一行是標頭，用逗號隔開
data = np.loadtxt(csv_filename, delimiter=",", skiprows=1)

print("資料形狀:", data.shape)

# 在 SU2 的 restart 檔中：
# 欄位通常依序是：PointID, x, y, (然後是各項守恆變數，例如 Density, Momentum, Energy...)
# 讓我們先把座標和密度抓出來
x = data[:, 1]
y = data[:, 2]
density = data[:, 3]  # 如果密度剛好在第 3 欄 (index 3)

nx, ny = 1000, 1000
X = x.reshape((ny + 1, nx + 1))
Y = y.reshape((ny + 1, nx + 1))
Rho = density.reshape((ny + 1, nx + 1))

# 開始畫圖
plt.figure(figsize=(8, 6))
contour = plt.contourf(X, Y, Rho, levels=50, cmap="jet")
plt.colorbar(contour, label="Density")
plt.title("4-Contact Riemann Problem (Restart CSV)")
plt.xlabel("X")
plt.ylabel("Y")
plt.axis("equal")

output_img = "riemann_result.png"
plt.savefig(output_img, dpi=300, bbox_inches="tight")
print(f"完美收工！震波圖已經存成 {output_img}！快去欣賞你的心血結晶吧！")
