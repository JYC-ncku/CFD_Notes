# make_restart.py
# 欺騙 SU2 的四宮格初始狀態產生器

import math

# 氣體常數 (空氣通常設為 1.4)
gamma = 1.4

# 定義經典的 4-Contact 黎曼問題 (Configuration 3)
# 回傳: 密度(rho), X速度(u), Y速度(v), 壓力(p)
def get_state(x, y):
	if x > 0.5 and y > 0.5:     # 第一象限 (右上)
		return 1.0, 0.75, -0.5, 1.0
	elif x <= 0.5 and y > 0.5:  # 第二象限 (左上)
		return 2.0, 0.75, 0.5, 1.0
	elif x <= 0.5 and y <= 0.5: # 第三象限 (左下)
		return 1.0, -0.75, 0.5, 1.0
	else:                       # 第四象限 (右下)
		return 3.0, -0.75, -0.5, 1.0

# 必須跟網格的設定一模一樣！
NX, NY = 1000, 1000
L, H = 1.0, 1.0

with open("solution_flow.dat", "w") as f:
	# 寫入 SU2 規定的 CSV 魔法標頭
	f.write('"PointID","x","y","Density","Momentum_x","Momentum_y","Energy"\n')

	Node_id = 0
	for j in range(NY + 1):
		y = j * (H / NY)
		for i in range(NX + 1):
			x = i * (L / NX)

			# 判斷這個點在哪個象限，取得對應狀態
			rho, u, v, p = get_state(x, y)
			# 轉換成 SU2 看得懂的「守恆變數 (Conservative Variables)」
			mom_x = rho * u
			mom_y = rho * v
			# 總能量 (Total Energy) 的物理公式
			energy = (p / (gamma - 1.0)) + 0.5 * rho * (u**2 + v**2)
			# 寫入這一行 (注意格式不能亂動)
			f.write(f"{Node_id},{x:.6f},{y:.6f},{rho:.6f},{mom_x:.6f},{mom_y:.6f},{energy:.6f}\n")
			Node_id += 1

print("The solution_flow.dat make successfully!\n")
