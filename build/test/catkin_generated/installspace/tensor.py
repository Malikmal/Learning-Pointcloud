import numpy as np
import tensorflow as tf
from keras.models import Model
from keras.layers import Input, Activation, Dense, Conv2D, MaxPooling2D, ZeroPadding2D, Flatten
from keras.optimizers import Adam
from keras.utils.np_utils import to_categorical
from keras.callbacks import TensorBoard
from keras.datasets import fashion_mnist

(train_x, train_y), (test_x, test_y) = fashion_mnist.load_data()

train_x = train_x.astype('float32') / 255.
test_x = test_x.astype('float32') / 255.

train_x = np.reshape(train_x, (len(train_x), 28, 28, 1))
test_x = np.reshape(test_x, (len(test_x), 28, 28, 1))

train_y = to_categorical( train_y )
test_y = to_categorical( test_y )

# Feature Extraction Layer
inputs = Input(shape=(28, 28, 1))
conv_layer = ZeroPadding2D(padding=(2,2))(inputs)
conv_layer = Conv2D(16, (5, 5), strides=(1,1), activation='relu')(conv_layer)
conv_layer = MaxPooling2D((2, 2))(conv_layer)
conv_layer = Conv2D(32, (3, 3), strides=(1,1), activation='relu')(conv_layer)
conv_layer = Conv2D(32, (3, 3), strides=(1,1), activation='relu')(conv_layer)
conv_layer = MaxPooling2D((2, 2))(conv_layer)
conv_layer = Conv2D(64, (3, 3), strides=(1,1), activation='relu')(conv_layer)

# Flatten feature map to Vector with 576 element.
flatten = Flatten()(conv_layer)

# Fully Connected Layer
fc_layer = Dense(256, activation='relu')(flatten)
fc_layer = Dense(64, activation='relu')(fc_layer)
outputs = Dense(10, activation='softmax')(fc_layer)

model = Model(inputs=inputs, outputs=outputs)

# Adam Optimizer and Cross Entropy Loss
adam = Adam(lr=0.0001)
model.compile(optimizer=adam, loss='categorical_crossentropy', metrics=['accuracy'])

# Print Model Summary
print(model.summary())

# Use TensorBoard
callbacks = TensorBoard(log_dir='./Graph')

# Train for 100 Epochs and use TensorBoard Callback
model.fit(train_x, train_y, batch_size=256, epochs=100, verbose=1, validation_data=(test_x, test_y), callbacks=[callbacks])

# Save Weights
model.save_weights('src/test/data/weights.h5')
















############################ heros csv ############################

# import numpy as np
# import pandas as pd
# import tensorflow as tf
# from keras.models import Model, Sequential
# from keras.layers import Input, Activation, Dense
# from keras.optimizers import SGD
# from keras.utils.np_utils import to_categorical

# # Pandas read CSV
# sf_train = pd.read_csv('src/test/data/p5_training_data.csv')

# # Correlation Matrix for target
# corr_matrix = sf_train.corr()
# print(corr_matrix['type'])

# # Drop unnecessary columns
# sf_train.drop(sf_train.columns[[5, 12, 14, 21, 22, 23]], axis=1, inplace=True)
# print(sf_train.head())

# # Pandas read Validation CSV
# sf_val = pd.read_csv('src/test/data/p5_val_data.csv')

# # Drop unnecessary columns
# sf_val.drop(sf_val.columns[[5, 12, 14, 21, 22, 23]], axis=1, inplace=True)

# # Get Pandas array value (Convert to NumPy array)
# train_data = sf_train.values
# val_data = sf_val.values

# # Use columns 2 to last as Input
# train_x = train_data[:,2:]
# val_x = val_data[:,2:]

# # Use columns 1 as Output/Target (One-Hot Encoding)
# train_y = to_categorical( train_data[:,1] )
# val_y = to_categorical( val_data[:,1] )

# # Create Network
# inputs = Input(shape=(16,))
# h_layer = Dense(10, activation='sigmoid')(inputs)

# # Softmax Activation for Multiclass Classification
# outputs = Dense(3, activation='softmax')(h_layer)

# model = Model(inputs=inputs, outputs=outputs)

# # Optimizer / Update Rule
# sgd = SGD(lr=0.001)

# # Compile the model with Cross Entropy Loss
# model.compile(optimizer=sgd, loss='categorical_crossentropy', metrics=['accuracy'])

# # Train the model and use validation data
# model.fit(train_x, train_y, batch_size=16, epochs=5000, verbose=1, validation_data=(val_x, val_y))
# model.save_weights('weights.h5')

# # Predict all Validation data
# predict = model.predict(val_x)

# # Visualize Prediction
# df = pd.DataFrame(predict)
# df.columns = [ 'Strength', 'Agility', 'Intelligent' ]
# df.index = val_data[:,0]
# print(df)