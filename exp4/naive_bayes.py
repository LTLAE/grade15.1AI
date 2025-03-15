import pandas as pd
import numpy as np
from numpy.distutils.conv_template import header
from sklearn.metrics import f1_score
from sklearn.metrics import accuracy_score

training_dataset = pd.read_csv('training_set.csv', header=None)
train_features = training_dataset.iloc[:, 1:]
train_target = training_dataset.iloc[:, 0]

# calculate class prior probabilities
class_counts = train_target.value_counts()
class_priors = {class_id: count / len(train_target) for class_id, count in class_counts.items()}
print("Class priors: ", class_priors)

# calculate class means and variances
class_means = train_features.groupby(train_target).mean()
class_variances = train_features.groupby(train_target).var()
print("Class means: \n", class_means)
print("Class variances: \n", class_variances)

# use means and variances to predict
test_dataset = pd.read_csv('test_set.csv', header=None)
test_features = test_dataset.iloc[:, 1:]
test_target = test_dataset.iloc[:, 0]

# calculate probabilities
predictions = []    # used to store the predicted class labels
for _, sample in test_features.iterrows():
    class_probabilities = {}
    # calculate the posterior probability for each class
    for class_label, class_prior in class_priors.items():
        class_prob = class_prior

        # calculate the likelihood each feature in class
        for feature in train_features.columns:
            mean = class_means.loc[class_label, feature]
            var = class_variances.loc[class_label, feature]
            class_prob *= 1 / np.sqrt(2 * np.pi * (var + 1e-9)) * np.exp(-0.5 * (sample[feature] - mean) ** 2 / (var + 1e-9))

        class_probabilities[class_label] = class_prob

    # pick result with the highest probability
    predicted_class = max(class_probabilities, key=class_probabilities.get)
    predictions.append(predicted_class)

# calculate accuracy
acc = accuracy_score(test_target, predictions)
print("Accuracy: ", acc)

# calculate f1 score
f1 = f1_score(test_target, predictions, average='weighted')
print("F1 score: ", f1)
