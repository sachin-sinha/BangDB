# RainFall Prediction
-------------------

### RainFall prediction for Commonwealth games Australia on BangDB using Tensorflow (Keras)

#### Problem statement
Predict whether or not it will rain tomorrow by training a binary classification model on target RainTomorrow.
This is taken from Kaggle and here is the detail problem description

#### Help doc
Download the help doc and follow the instruction to complete the task

wget https://bangdb.com/downloads/RainFallPrediction.zip

#### Data description
This dataset contains daily weather observations from numerous Australian weather stations. The target variable RainTomorrow means: Did it rain the next day? Yes or No. We excluded the variable Risk-MM when training a binary classification model. Not excluding it will leak the answers to your model and reduce its predictability.RISK_MM is the amount of rainfall in millimeters for the next day. It includes all forms of precipitation that reach the ground, such as rain, drizzle, hail and snow. And it was the column that was used to actually determine whether or not it rained to create the binary target. For example, if RISK_MM was greater than 0, then the RainTomorrow target variable is equal to Yes.

Since it contains information about the future, and since it contains information directly about the target variable, including it would leak the future information to your model. Using it as a predictor to build a model and then testing on this dataset would give the false appearance of a high accuracy.

Observations were drawn from numerous weather stations. The daily observations are available from http://www.bom.gov.au/climate/data. Copyright Commonwealth of Australia 2010, Bureau of Meteorology.

#### Algorithm
This is a classification problem and we are going to solve this problem by using the Custom External algorithm that is by uploading external python code.In this example we will use Keras / Tensorflow

#### Approach
We can train model using algorithm which are not in built by uploading training and prediction python code it has to follow some basic protocol
