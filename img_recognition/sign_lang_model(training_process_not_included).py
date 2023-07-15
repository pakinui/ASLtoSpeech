import numpy as np
import pandas as pd
import tensorflow as tf
import matplotlib.pyplot as plt
import os
import pickle, gzip
from sklearn.preprocessing import LabelBinarizer

load_from_file = True

test_df = pd.read_csv("sign_mnist_test.csv")

y_test = test_df['label']
del test_df['label']

# transforms raw feature vectors into a representation more suitable for training
label_binarizer = LabelBinarizer()
y_test = label_binarizer.fit_transform(y_test)

x_test = test_df.values

x_test = x_test / 255

x_test = x_test.reshape(-1,28,28,1)


# Specify the names of the save files
save_name = os.path.join('saved', 'sign_lang')
checkpoint_save_name = save_name + 'sign_cnn_net.chk'
net_save_name = save_name + '_cnn_sign_lang.h5'
history_save_name = save_name + '_cnn_sign_lang.hist'


if load_from_file and os.path.isfile(net_save_name):
   # ***************************************************
   # * Loading previously trained neural network model *
   # ***************************************************

   # Load the model from file
   print("Loading neural network from %s..." % net_save_name)
   model = tf.keras.models.load_model(net_save_name)


   # Load the training history
   if os.path.isfile(history_save_name):
      with gzip.open(history_save_name) as f:
         history = pickle.load(f)
   else:
      history = []

loss, classification_output_accuracy= model.evaluate(x_test, y_test, verbose=0)

print("Test classification accuracy (tf): %.2f" % classification_output_accuracy)

# Test neural network with test images
test_output = model.predict(x_test[:16])
tested_category = np.argmax(test_output, axis=1)

fig, axes = plt.subplots(4, 4, figsize=(8, 8))
fig.subplots_adjust(hspace=0.2, wspace=0.1)

# Show the result of classification problem

class_names = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y']

for i, ax in enumerate(axes.flat):
   image = x_test[i]

   # Fetch category from test image
   label = np.where(y_test[i] == 1)[0][0]
   bfr = class_names[label]

   aftr = class_names[tested_category[i]]

   # Show image
   ax.imshow(image, cmap='gray')
   ax.text(0.5, -0.12, f'(label={bfr}, output={aftr})', ha='center',
        transform=ax.transAxes, color='black')
   ax.set_xticks([])
   ax.set_yticks([])



plt.show()
