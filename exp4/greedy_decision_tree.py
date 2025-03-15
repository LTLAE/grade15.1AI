import pandas as pd
import numpy as np
from collections import Counter

# read training_set
training_set = pd.read_csv('training_set.csv', header=None)

# get rid of the first column
training_set = training_set.iloc[:, 1:]

# get target values (column 0 after dropping the first column)
training_target = training_set.iloc[:, 0]

# get features (all columns except the first column)
training_features = training_set.iloc[:, 1:]

# use information gain to select the best feature
def entropy(y):
    counts = Counter(y)
    probabilities = [count / len(y) for count in counts.values()]
    return -sum(p * np.log2(p) for p in probabilities)

def information_gain(X_column, y, threshold):
    # spilt the data
    left_idx = X_column <= threshold
    right_idx = X_column > threshold
    left_y, right_y = y[left_idx], y[right_idx]
    # calculate the information gain
    n = len(y)
    left_weight = len(left_y) / n
    right_weight = len(right_y) / n
    gain = entropy(y) - (left_weight * entropy(left_y) + right_weight * entropy(right_y))
    return gain

# find best split point
def best_split(X, y):
    best_gain = -1
    best_feature = None
    best_threshold = None

    for feature in range(X.shape[1]):
        X_column = X[:, feature]
        thresholds = np.unique(X_column)
        for threshold in thresholds:
            gain = information_gain(X_column, y, threshold)
            if gain > best_gain:
                best_gain = gain
                best_feature = feature
                best_threshold = threshold

    return best_feature, best_threshold

# data structure for decision tree
class DecisionTree:
    def __init__(self, depth=0, max_depth=None):
        self.depth = depth
        self.max_depth = max_depth
        self.feature = None
        self.threshold = None
        self.left = None
        self.right = None
        self.prediction = None

    def fit(self, X, y):
        # stop splitting when: all labels are the same or max depth
        if len(set(y)) == 1 or (self.max_depth and self.depth >= self.max_depth):
            self.prediction = Counter(y).most_common(1)[0][0]
            return

        # find the best split
        feature, threshold = best_split(X, y)
        if feature is None:
            self.prediction = Counter(y).most_common(1)[0][0]
            return

        self.feature = feature
        self.threshold = threshold

        # spilt the data
        left_idx = X[:, feature] <= threshold
        right_idx = X[:, feature] > threshold
        left_X, left_y = X[left_idx], y[left_idx]
        right_X, right_y = X[right_idx], y[right_idx]

        # create left and right nodes
        self.left = DecisionTree(depth=self.depth + 1, max_depth=self.max_depth)
        self.left.fit(left_X, left_y)
        self.right = DecisionTree(depth=self.depth + 1, max_depth=self.max_depth)
        self.right.fit(right_X, right_y)

    def predict(self, X):
        if self.prediction is not None:
            return self.prediction
        if X[self.feature] <= self.threshold:
            return self.left.predict(X)
        else:
            return self.right.predict(X)

    def predict_batch(self, X):
        return np.array([self.predict(x) for x in X])

# train
X = training_features.values
y = training_target.values
tree = DecisionTree(max_depth=5)
tree.fit(X, y)

# read test_set
test_set = pd.read_csv('test_set.csv', header=None)
test_target = test_set.iloc[:, 0]
test_features = test_set.iloc[:, 1:]

# predict
predictions = tree.predict_batch(test_features.values)
print("Predictions:\n", predictions)

# result: 8.196 and 9.504 -> 1 and 0
predictions_binary = (predictions > 9).astype(int)
print("Predictions:\n", predictions_binary)

# calculate acc
acc = np.mean(predictions_binary == test_target)
print("Accuracy:", acc)

# calculate AUC
from sklearn.metrics import roc_auc_score
auc = roc_auc_score(test_target, predictions)
print("AUC:", auc)

