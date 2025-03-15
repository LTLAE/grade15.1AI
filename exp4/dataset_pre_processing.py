import pandas as pd
import numpy as np

# read file
dataset = pd.read_csv('wdbc.data', header=None)

# drop the first column
dataset = dataset.iloc[:, 1:]

# convert M to 0 and B to 1
dataset.iloc[:, 0] = dataset.iloc[:, 0].map({'M': 0, 'B': 1})

# pick 20% of the data as test set
test_indices = np.random.choice(dataset.index, size=int(dataset.shape[0] * 0.2), replace=False)
test_set = dataset.loc[test_indices]

# drop test set
training_set = dataset.drop(index=test_indices)

# save to file
training_set.to_csv('training_set.csv', index=False, header=False)
test_set.to_csv('test_set.csv', index=False, header=False)

