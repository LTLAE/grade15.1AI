import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('time_and_moves.csv')

# Create first figure
fig1, plt1 = plt.subplots()
plt1.plot(df['dish_count'], df['time'], label='Time')
plt1.set_title('Dish Count vs Time')
plt1.set_xlabel('Dish Count')
plt1.set_ylabel('time')
plt1.legend()

# Create second figure
fig2, plt2 = plt.subplots()
plt2.plot(df['dish_count'], df['moves'], label='Moves')
plt2.set_title('Dish Count vs Moves')
plt2.set_xlabel('Dish Count')
plt2.set_ylabel('Moves')
plt2.legend()

# Show both figures
plt.show()