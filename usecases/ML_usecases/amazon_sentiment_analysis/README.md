# Amazon Sentiment Analysis
-------------------------

### Training sentiment model using BangDB IE (Information Extraction) module

#### Problem statement

We have to categorize opinions expressed in feedback forums. This can be utilized for a feedback management system. We classify individual comments/reviews.and we also determine overall rating based on individual comments/reviews. So that company can get a complete idea on feedback provided by customers and can take care of those particular fields. This makes more loyal Customers to the company, increase in business , fame ,brand value ,profits.

This is taken from Kaggle, here is the problem statement in detail:
https://www.kaggle.com/bittlingmayer/amazonreviews

#### Help doc
Download the help doc and follow the instruction to complete the task

wget https://bangdb.com/downloads/AmazonSentimentAnalysis.zip

#### Objective
The task is to build a model that will determine the class ( level_1 or level_2) of the text.

#### Data description
This dataset consists of Amazon customer reviews (input text) and star ratings (output labels). The training file is in CSV format. We have to convert the training file from CSV to JSON for training. Converting data from : __label__2 Great necklace: I love the color of the stone and how it hangs on my neck. It’s a great necklace for the price. To : {“label”:”2”,”text”:“Great necklace: I love the color of the stone and how it hangs on my neck. It’s a great necklace for the price.”}

#### Algorithm
We are going to use the algorithm IE_sent which is in build. It’s ready to use algorithm only for sentiment analysis. User have to provide data in json format and provide labels.

#### Approach
The requirements are – a training file in json format and data type is categorical with only two attributes one is label and other is text.

#### Method

#### Cli workflow
