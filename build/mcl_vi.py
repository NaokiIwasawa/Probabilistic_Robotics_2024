import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import numpy as np

# CSVファイルの読み込み
data = pd.read_csv('particle_positions.csv')

# グラフの初期設定
fig, ax = plt.subplots(figsize=(10, 6))
ax.set_xlim(-10, 30)  # 数直線上の表示範囲
ax.set_ylim(0, 50)  # パーティクル数の最大値を調整
ax.set_xlabel("Position")
ax.set_ylabel("Particle Count")
plt.title("Particle Overlap per Position")

# 初期の棒グラフを設定（labelを1回だけ設定）
bins = np.arange(-10, 31)  # ビンの範囲（-10から30までの整数）
bars = ax.bar(bins[:-1], np.zeros(len(bins) - 1), width=0.9, align='center', color='blue', label='Particle Density')

# アニメーションの更新関数
def update(frame):
    # 各イテレーションにおけるパーティクルの位置を取得
    positions = data[data['Iteration'] == frame + 1]['Position'].values

    # ヒストグラムデータを作成
    counts, _ = np.histogram(positions, bins=bins)

    # ヒストグラムを更新
    for bar, count in zip(bars, counts):
        bar.set_height(count)

    return bars

# アニメーションの作成
ani = animation.FuncAnimation(fig, update, frames=range(data['Iteration'].max()), repeat=False)

# グラフを表示
plt.legend()  # legendを1回だけ表示
plt.show()
