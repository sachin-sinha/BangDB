# Credit Risk Analysis
--------------------

#### PROBLEM STATEMENT:
In this project, we have to manage credit risk by using the past data and deciding whom to give the loan in the future. The data file contains complete loan data for all loans issued between 2007-2015. The data contains the indicator of default, payment information, credit history, etc.
This is taken from Kaggle, here is the problem statement in detail

The data is divided into training and test data. We have used the training data to build a model and finally applied it to test data to measure the performance and robustness of the models.

#### Objective
To build a machine learning model to detect load defaulters.

LinksTake the zip file and follow the instruction to complete the task.

wget https://bangdb.com/downloads/CreditRisk.zip

#### Data description
The dataset contains 855969 events with 73 attributes ( containing both categorical and numerical data). Total number of defaulters are 46467 out of 855969 which is approx 6% of the total. This clearly is a case of an imbalanced class problem where the value of class is far less than the other.

Data processing: The percentage of missing data in many columns are more than 75%. So, we’ll have to remove columns having data less than 75%. 2 attributes have only 1 unique value and 7 attributes are highly correlated to each other. We are also dropping columns like id, member_id , zip, title etc as they play no role in model training. In the final dataset we have 29 attributes.

#### Algorithm
The given problem is a classification problem. To solve it, we will be using the Support Vector Classifier algorithm ( SVC) with weights to deal with class imbalance. Why SVM, because SVM is more effective in high dimensional spaces and SVM is relatively memory efficient.

#### Approach
There are three ways to train a model on bangdb. One is to directly register the meta_data for training ( we call it json request which contains all the details about the model ), second is to create mage_data for training by following the workflow on CLI and the last one is to train using api’s. Here we will be training the model using CLI.

#### Method
Training model by following workflow on cli
