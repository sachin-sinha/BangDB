# Data Clustering Analysis
------------------------

### Credit Card Data Clustering Analysis using Kmeans on BangDB
#### Problem statement
This case requires developing a customer segmentation to define marketing strategy. The Dataset summarizes the usage behavior of about 14360 active credit card holders during the last 6 months. The file is at a customer level with 18 behavioural variables.

This is taken from Kaggle, here is the problem statement in detail

#### Objective
Build a model to perform customer segmentation.

#### Get help doc
Download the file and follow the help doc to complete the task

wget https://bangdb.com/downloads/CrediCardClustering.zip

#### Data description
The dataset contains 14360 events and 18 attributes. The dataset consists of both continuous as well as categorical attributes. The columns are CUSTID,BALANCE,BALANCEFREQUENCY, PURCHASES, ONEOFFPURCHASES, INSTALLMENTSPURCHASES, CASHADVANCE, PURCHASESFREQUENCY, ONEOFFPURCHASESFREQUENCY, ONEOFFPURCHASESFREQUENCY,CASHADVANCE, PURCHASESFREQUENCY, ONEOFFPURCHASESFREQUENCY, PURCHASESINSTALLMENTSFREQUENCY, CASHADVANCEFREQUENCY, CASHADVANCETR, PURCHASESTRX, CREDITLIMIT, PAYMENTS, MINIMUM_PAYMENTS, PRCFULLPAYMENT, TENURE.

#### Algorithm
We have to do customer segmentation for the given problem. To do this we are selecting the kernel k-means algorithm( KKmeans). In kernel k-means before clustering, points are mapped to a higher-dimensional feature space using a nonlinear function, and then kernel k-means partitions the points by linear separators in the new space.

#### Approach
There are three ways to train a model on bangdb. One is to directly register the meta_data for training ( we call it json request which contains all the details about the model ), the second is to create mage_data for training by following the workflow on CLI and the third is by using api’s.. Here we will be training the model using all methods. On bangdb, we have the option of training a model from a file( file format can be CSV or JSON) containing training data or from streaming data. Here we are training the model from a CSV file.

#### Method
using Cli workflow
