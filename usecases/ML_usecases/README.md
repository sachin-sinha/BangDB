# ML Usecases
-----------

### SOLVE ML RELATED PROBLEMS ON BANGDB USING CLI IN A SIMPLE WAY

BangDB natively integrated ML (and DL) capabilities, which means we don’t need to have separate ML architecture or management framework in place. Also it avoids movement of data from DB to ML System and model back to the DB for use. Further since data and ML are at the same place therefore lots of steps could be simply automated.

While training models, we go through several steps and quickly we realise that training a model requires lot more than just a simple train command. We need to ingest data, process (preprocess / post process) it, clean, enrich, add/edit, normalise, deal with missing values etc. Moreover, training a model is often involves large files (train or test), metadata, model artifact etc. therefore we must store these in an efficient and accessible manner, version models, deploy them and so on.

BangDB has built lots of things in this regard to simply the procedures and also allow automation as much as possible. For example, the if data in ingested in the streams then we can do lots of pre and post processing, we can compute new attributes, aggregate and use them, apply complex rules to filter data etc. Further, data summarization can be done with a single command, which allows users to see some stats and correlations etc. to take appropriate action when it comes to selecting attributes. Some of the jobs like timeseries and forecast work are provided via simple abstraction which makes the entire process very easy and efficient.

While there are several inbuilt algos within BangDB, in many cases we would like to use external frameworks like Tensorflow, Keras, PyTorch, Scikit-learn etc. BangDB can leverage these without making any changes (except training metadata where we specify this). Users can upload training and test files (python) to train and predict etc. We will see some of these in following examples too

To deal with large files and objects, BangDB implements BRS (BangDB Resource Server) where ML system stores all the data. This mimics S3 like APIs to make it super simple for user to deal with such data/files.

This section is to help users to try out some the decent size problems (all taken from Kaggle) on BangDB using CLI. Please note, we can write application and also do the same, however for this section we will stick with CLI
