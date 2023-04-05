#Forecast Product Demand
-----------------------

### Training model for forecasting product demand on BangDB using CLI
#### Problem statement
In this competition, you will forecast the demand of a product for a given week, at a particular store. The dataset you are given consists of 9 weeks of sales transactions in Mexico. Every week, there are delivery trucks that deliver products to the vendors. Each transaction consists of sales and returns. Returns are the products that are unsold and expired. The demand for a product in a certain week is defined as the sales this week subtracted by the return next week.

This is taken from Kaggle, here is the problem statement in detail

#### Objective
To build a model which predicts the demand of a product.

#### Get help doc
Simply download and follow the doc to complete the task

wget https://bangdb.com/downloads/DemandForecast_Regression.zip

#### Data description
The dataset contains 180000 events and 11 attributes. All attributes are numerical. The attribute Demanda_uni_equil is the target value that we are trying to predict.

#### Algorithm
The given problem is a regression problem. To solve it, we will be using the Support Vector Regression algorithm ( SVR). The advantage of SVR over linear regression is that SVR gives us the flexibility to define how much error is acceptable in our model and will find an appropriate line (or hyperplane in higher dimensions) to fit the data.

#### Approach
There are three ways to train a model on bangdb. One is to directly register the meta_data for training ( we call it json request which contains all the details about the model ), the second is to create mage_data for training by following the workflow on CLI and the third is by using api’s. Here we will be training the model using CLI.
