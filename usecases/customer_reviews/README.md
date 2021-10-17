User/customer messages/reviews analysis
---------------------------------------

Scenario

	Users and customers are sending their messages or reviews from their devices. 
	There are several such messages streaming from different users into the system. 
	We must first be able to ingest these messages in real time manner.
	Further we should be able to processes every single message and  take corrective action as needed. 
	The processes would include following;

        a. set the streams and sliding window and ingest the data in these streams in continuous manner
        b. find out the sentiment of the message [ positve, negative ] using IE (information extraction) (
	   NOTE: we can find out many different sentiments/ emotions as we want, the demo deals with only two). We need to train a model here for this
        c. filter messages with negative sentiment and put them in separate stream for further action / processing
        d. find out a definitive pattern and send such events matching the patter to another stream for further review / action. The patter is as follows;
               i. Any particular product that gets minimum 3 consequtive negative sentiment messages 
		  from different users in span of 1000 sec, find this pattern in continuous sliding manner
        e. store few tripples in graph store like (user, POSTS_REVIEW, prod) and (prod, HAS_REVIEWS, revid), revid id review id and prod is product
        f. set running stats for different attributes in the event such as uniquw count for users or min/max/avg/sdtdev/sum/kurt for amount spend etc.
        g. set up reverse index for messages such that it can used for text search by the user
        h. set up secondary indexes for several attributes that could be helpful in query and also internal stream joins/ filter etc.

Relevant application areas

	a. ecommerce
	b. payment and banking
	c. Ridesharing and cabs on hire, ex Uber, Ola
	d. Home delivery entities (food, etc)

Complexities

	There are several challenges here, some of them could be
	
	a. Volume and Velocity.The number of messages could be very high, as these could be several users sending messages per second 
	   across the geographical areas. Hence data ingestion in real time is critical
	b. The messages could be in English or in other vernacular langauages, hence we need to extract sentiment from unstructured data, 
	   and keep improving or updating the models in real time
	c. Extracting patterns from the streaming set of events in continuous manner, this requires CEP on the streaming data which is 
	   very hard to implement on SQL or regular NoSQL databases
	d. Storing certain truples (sub, obj, predicate) in a graph which is continously updated as events arrive, helpful in linking data and/or events
	e. Different database queries along with text search which requires many secondary and reverse indexes 
	f. Infrstructure deplyment and maintenance if too many siols are used. Further automation is difficult to achieve in typical deployment models
	
Benefits of BangDB

	a. Use light weight high performance bangdb agents or other messaging framework to stream data into the BangDB. 
	   BangDB is high performance database with ingestion speed over 5K+ events per second per server leading to half a billion 
	   events processing per commodity server in a day
	b. Integrated stream processing within BangDB allows users to simply start the process with a simple json schema definition. 
	   There is no extra silos setup for streaming infrastructure
	c. Ingerated AI within BangDB allows users to simply train, deploy and predict on incoming data without having to set up separate infra and 
	   then exporting data/ importing model etc. The entire process can be automated within BangDB
	d. BangDB is a multi model database and it also allows Graph to be integrated with streams such that the graph is updated on streaming data with triples
	e. BangDB supports many kinds of indexes including reverse indexes, hence running rich queries along with searches on BangDB is quite simple
	f. Integrated with Grafana for visualization of time-series data


Overview of the solution

	1. We have a stream schema ecomm_schema. Here in these streams we will be ingesting data from various sources
	2. Ingestion of data happens as and when data is created. Therefore agent monitors a set of files here and as we write data into these files
	   agent will parse the data and send to bangdb server. We could directly write data using cli or using program which uses bangdb client etc...
	3. We have 3 different data sources here;
		a. product data - this is rathe non-streaming data, but still we could ingest these using agent
		b. order data - as and when order is placed
		c. customer or user reviews/ messages. This should be high volume streaming data
	4. Sample data is provided here, however you may add more data to run it at larger scale etc.


Steps to run the demo on your own


	A. Set up BangDB on your machine

		Note: If you have got the BangDB already, you may skip the step
		a. Get the BangDB, please check out https://bangdb.com/download ot https://github.com/sachin-sinha/BangDB
		b. Follow the read me file available in the folder and install the db

	
	Check out or clone this repo to get the files for the use case, and go to customer_reviews dir

	Note: It will be good to have several shell terminals for server, agent, cli and mon folder

	> cd customer_reviews

	copy the binaries (server, agent, cli) to the folders here in this folder (note: it's not required but simple to run the demo)
	a. copy bangdb-server-2.0 binary to the server/ folder
	b. copy bangdb-agent-2.0 binary to the agent/ folder
	c. copy bangdb-cli-2.0 binary to the cli/ folder

	Before running the demo from scratch, you should simply clean the database, ensure agent.conf file is reset, and the files
	which are being monitored by the agent are also reset. To do this run the reset.sh file in the base folder

	Also, please ensure the file and dir attributes are pointing to the right file and folder respectively in the agent/agent.conf file
	edit the agent/agent.conf file and update following with the right base path

      "file": "/mnt/test/customer_reviews/mon/prod.txt",
      "dir": "/mnt/test/customer_reviews/mon/",

	you will need to update "/mnt/test" part only


	B. Run the server, agent and cli

	Run the server
	
	> cd server
	> ./bangdb-server-2.0 -c hybrid -w 18080
	> cd ..

	Note: we are running bangdb in hybrid lisetening mode (tcp and http) both, http port is 18080. This will come handy
	in ingesting data using agents, interactions using cli etc. and at the same time visulisation using grafana
	
	Run the agent

	> cd  agent
	> ./bangdb-agent-2.0
	> cd ..

	Run the cli

	> cd cli
	> ./bangdb-cli-2.0

	you will see something like this on the prompt


	server [ 127.0.0.1 : 10101 ] is master with repl = OFF

	 __     _    _   _   ____   ___    ___
	|   \  / \  | \ | | | ___\ |   \  |   \
	|   / /   \ |  \| | | | __ |    | |   /
	|   \/ ___ \| | \ | | |__|||    | |   \
	|___/_/   \_|_| |_| |_____||___/  |___/
	
	command line tool for db+stream+ai+graph

	please type 'help' to get more info, 'quit' or 'exit' to return

	bangdb> 


	C. Register the schema (set of streams)

	Let's first register the stream schema into which we will be receiving the data

	bangdb> register schema ecomm_schema.txt 
	success


	now let's ingest few data into the stream product.
	NOTE: to help user ingest some events, there is simple script "sendline.sh" which takes following arguments;
	
	bash sendline <fromfile> <tofile> <numrec> <stopsec>

	send <fromfile> to <tofile> with <numrec> num of events <stopsec> per sec

	In real scenario, application or program will write these events into some log file and agent will keep
	sending data to the server. For demo purpose, we will simulate application / program by using sendline.sh


	D. Send product data to the server

	> cd mon/
	> bash sendline.sh ../data/ecomm_product.txt prod.txt 1 1

	Note: you can send 1000's of event per second by using 
	> bash sendline.sh ../data/ecomm_product.txt prod.txt 1000 1

	E. Send order data to the server

	bash sendline.sh ../data/ecomm_order.txt order.txt 1 1

	Now come back to the cli shell terminal and train a model for sentiment analysis.
	BangDB will keep using this sentiment model for adding "sentiment" attribute for every event as it arrives

	F. Train sentiment model

	When you train a model from cli, here is what you will see, you may follow as it's shown here or
	simply follow the workflow as cli will keep asking questions.

	NOTE: Sentiment model requires a knowlegde base for the context. It's always a good idea to train a
	KB for the context/ area in which we work. Therefore for better accuracy and performance we should ideally train a model.
	Howerver, for the demo purpose, we have a sample kb (which is trained on minimal data), which can be used but not
	sufficient. If you want proper KB for sentiment analysis for customer reviews / comments / messages then please
	send me mail (sachin@bangdb.com), I will forward the link to you. For production, we must use proper trained KB file

	bangdb> train model user_sentiment
	what's the name of the schema for which you wish to train the model?: ecomm
	do you wish to read earlier saved ml schema for editing/adding? [ yes |  no ]: 


		BangDB supports following algorithm, pls select from these
		Classification (1) | Regression (2) | Lin-regression/Classification (3) | Kmeans (4) | Custom (5)
		| IE - ontology (6) | IE - NER (7) | IE - Sentiment (8) | IE - KB (9) | TS - Forecast (10) 
		| DL - resnet (11) | DL - lenet (12) | DL - face detection (13) | DL - shape detection (14) | SL - object detection (15)

	what's the algo would you like to use (or Enter for default (1)): 8
	what's the input (training data) source? [ local file (1) | file on BRS (2) | stream (3) ] (press enter for default (1)): 1
	enter the training file name for upload (along with full path): ../data/review_train.txt


		we need to do the mapping so it can be used on streams later
		This means we need to provide attr name and its position in the training file

	need to add mapping for [ 2 ] attributes as we have so many dimensions
	enable attr name: sentiment
	enable attr position: 0
	enable attr name: msg
	enable attr position: 1


	we also need to provide the labels for which the model will be trained
        enter the label name: positive
	do you wish to add more labels? [ yes |  no ]: yes
        enter the label name: negative
	do you wish to add more labels? [ yes |  no ]: 
        enter the name of the KB model file (full path)(for ex; /mydir/total_word_feature_extractor.dat): total_word_feature_extractor.dat
        Do you wish to upload the file? [ yes |  no ]: yes
	training request : 
	{
	   "training_details" : {
	      "train_action" : 0,
	      "training_source_type" : 1,
	      "training_source" : "review_train.txt",
	      "file_size_mb" : 1
	   },
	   "model_name" : "user_sentiment",
	   "algo_type" : "IE_SENT",
	   "labels" : [
	      "positive",
	      "negative"
	   ],
	   "schema-name" : "ecomm",
	   "total_feature_ex" : "total_word_feature_extractor.dat",
	   "attr_list" : [
	      {
		 "position" : 0,
		 "name" : "sentiment"
	      },
	      {
		 "name" : "msg",
		 "position" : 1
	      }
	   ]
	}
	do you wish to start training now? [ yes |  no ]: yes
	model [ user_sentiment ] scheduled successfully for training
	you may check the train status by using 'show train status' command
	do you wish to save the schema (locally) for later reference? [ yes |  no ]: 


	Now you can see the status of the model training

	bangdb> show models
	+--------------------+--------------+-------+------------+-----------+------------------------+------------------------+
	|key                 |model name    |   algo|train status|schema name|train start time        |train end time          |
	+--------------------+--------------+-------+------------+-----------+------------------------+------------------------+
	|ecomm:user_sentiment|user_sentiment|IE_SENT|passed      |ecomm      |Sat Oct 16 00:07:11 2021|Sat Oct 16 00:07:12 2021|
	+--------------------+--------------+-------+------------+-----------+------------------------+------------------------+


	Now let's ingest the customer reviews and see the output

	cd mon
	bash sendline.sh ../data/user_msg.txt reviews.txt 1 1

	come back to cli terminal and select few events from the stream "reviews" in the "ecomm"schema

	bangdb> select * from ecomm.reviews
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|key             |val                                                                                                                             |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329532924119|{"uid":"sal","prod":"ipad","msg":"finally the order arrived but i am returning it due to delay","tag":"return","revid":"rev13","|
	|                |_pk":1634329532924119,"sentiment":"negative","_v":1}                                                                            |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329531921928|{"uid":"raman","prod":"guitar","msg":"finally order is placed, delivery date is still ok do it's fine","tag":"order","revid":"re|
	|                |v12","_pk":1634329531921928,"sentiment":"positive","_v":1}                                                                      |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329530919064|{"uid":"sal","prod":"iphone","msg":"just ordered for p3 and i got a call that the delivery is delayed","tag":"order","revid":"re|
	|                |v11","_pk":1634329530919064,"sentiment":"positive","_v":1}                                                                      |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329529916681|{"uid":"raman","prod":"guitar","msg":"the product is in cart, i want to order but it's not going","tag":"cart","revid":"rev10","|
	|                |_pk":1634329529916681,"sentiment":"negative","_v":1}                                                                            |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329528914003|{"uid":"mike","prod":"football","msg":"how amazing to get the packet before time, great work xyz","tag":"order","revid":"rev9","|
	|                |_pk":1634329528914003,"sentiment":"positive","_v":1}                                                                            |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329527911595|{"uid":"sal","prod":"ipad","msg":"not sure why the product is not yet delivered, it said it will be done 3 days ago","tag":"orde|
	|                |r","revid":"rev8","_pk":1634329527911595,"sentiment":"negative","_v":1}                                                         |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329526909432|{"uid":"rose","prod":"guitar","msg":"not sure if this site works or not, frustating","tag":"order","revid":"rev7","_pk":16343295|
	|                |26909432,"sentiment":"negative","_v":1}                                                                                         |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329525906102|{"uid":"hema","prod":"p3","msg":"the tabla got set very smoothly, thanks for the quality service","tag":"order","revid":"rev6","|
	|                |_pk":1634329525906102,"sentiment":"positive","_v":1}                                                                            |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329524902468|{"uid":"hema","prod":"tabla","msg":"i received the product, it looks awesome","tag":"order","revid":"rev5","_pk":163432952490246|
	|                |8,"sentiment":"positive","_v":1}                                                                                                |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329523899985|{"uid":"rose","prod":"guitar","msg":"order placed, money debited but status is still pending","tag":"order","revid":"rev4","_pk"|
	|                |:1634329523899985,"sentiment":"negative","_v":1}                                                                                |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	total rows retrieved = 10 (10)
	more data to come, continue .... [y/n]: 


	As you see, the attribute "sentiment" is added with the value predicted by the model user_sentiment

	Now let's check out the events in the filter stream. We see that all negative events are also available in the stream
	negtative_reviews

	bangdb> select * from ecomm.negative_reviews
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|key             |val                                                                                                                             |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329532924119|{"uid":"sal","prod":"ipad","msg":"finally the order arrived but i am returning it due to delay","tag":"return","revid":"rev13","|
	|                |_pk":1634329532924119,"_v":1}                                                                                                   |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329529916681|{"uid":"raman","prod":"guitar","msg":"the product is in cart, i want to order but it's not going","tag":"cart","revid":"rev10","|
	|                |_pk":1634329529916681,"_v":1}                                                                                                   |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329527911595|{"uid":"sal","prod":"ipad","msg":"not sure why the product is not yet delivered, it said it will be done 3 days ago","tag":"orde|
	|                |r","revid":"rev8","_pk":1634329527911595,"_v":1}                                                                                |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329526909432|{"uid":"rose","prod":"guitar","msg":"not sure if this site works or not, frustating","tag":"order","revid":"rev7","_pk":16343295|
	|                |26909432,"_v":1}                                                                                                                |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329523899985|{"uid":"rose","prod":"guitar","msg":"order placed, money debited but status is still pending","tag":"order","revid":"rev4","_pk"|
	|                |:1634329523899985,"_v":1}                                                                                                       |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329522897451|{"uid":"sal","prod":"ipad","msg":"even after contacting customer care, we have no update yet","tag":"order","revid":"rev3","_pk"|
	|                |:1634329522897451,"_v":1}                                                                                                       |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329521895545|{"uid":"sal","prod":"ipad","msg":"the order 2 was placed 4 days ago, still there is no response, i am still waiting for any conf|
	|                |irmation","tag":"order","revid":"rev2","_pk":1634329521895545,"_v":1}                                                           |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329520891590|{"uid":"sachin","prod":"cello","msg":"even after calling 20 times, the customer care is not responding at all","tag":"order","re|
	|                |vid":"rev1","_pk":1634329520891590,"_v":1}                                                                                      |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	total rows retrieved = 8 (8)


	As you see, the events got automatically collected in this stream, we can further set notification as well which will allow server to
	take actions / sends notifications in automated manner

	But if you see, we don't have any event in the negative_reviews_pattern stream. This is because we haven't sent the events which could
	have formed the pattern. To remind, pattern is defined as "at least 3 consequtive negative events for the same product but from different
	users within 1000 sec". We sould like to extract these patterns in continuous manner and store these events in the negative_reviews_pattern
	stream

	Let's now add two events which are negative (as you note, the last event is predicted as negative hence we have one negative event
	already so another two more negative event should trigger a pattern)

	bangdb> insert into ecomm.reviews values null {"uid":"alan","prod":"ipad","msg":"finally the order arrived but i am returning it due to delay","tag":"return","revid":"rev14"}
	success

	bangdb> insert into ecomm.reviews values null {"uid":"john","prod":"ipad","msg":"frustating that product is not delievered yet","tag":"return","revid":"rev15"}
	success


	Now select from the pattern stream

	bangdb> select * from ecomm.negative_reviews_pattern
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|key             |val                                                                                                                             |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	|1634329705652574|{"uid":"john","prod":"ipad","sentiment":"negative","revid":"rev15","_pk":1634329705652574,"uid":"sal","prod":"ipad","_jpk1":1634|
	|                |329669688454,"_v":1}                                                                                                            |
	+----------------+--------------------------------------------------------------------------------------------------------------------------------+
	total rows retrieved = 1 (1)

	As you see it has two uids (since we select both as per schema definition - see the ecomm_schema.txt). The first one where the pattern started
	and the one where it got completed.

	You can play with this and see how it works. If another negative event comes for the product which forms the pattern then it will get collected.
	else if broken then next time when the pattern is seen, server will send that event to the stream etc.


	Now, let's see the triples as stored by the server in graph structure, we will run Cypher queries

	bangdb> USE GRAPH ecomm_graph
	USE GRAPH ecomm_graph successful

	bangdb> S=>(@u uid:*)-[POSTS_REVIEWS]->(@p prod:guitar)
	+---------+-------------+-----------+
	|sub      |pred         |        obj|
	+---------+-------------+-----------+
	|uid:raman|POSTS_REVIEWS|prod:guitar|
	+---------+-------------+-----------+
	|uid:raman|POSTS_REVIEWS|prod:guitar|
	+---------+-------------+-----------+
	|uid:rose |POSTS_REVIEWS|prod:guitar|
	+---------+-------------+-----------+
	|uid:rose |POSTS_REVIEWS|prod:guitar|
	+---------+-------------+-----------+

	bangdb>  S1=>(@u uid:hema)-[POSTS_REVIEWS]->(@p prod:*)-[HAS_REVIEWS]->(@r revid:*)
	+----------+-----------+----------+
	|sub       |pred       |       obj|
	+----------+-----------+----------+
	|prod:tabla|HAS_REVIEWS|revid:rev5|
	+----------+-----------+----------+
	|prod:p3   |HAS_REVIEWS|revid:rev6|
	+----------+-----------+----------+


And so on.
Please see https://bangdb.com/developer for more info on stream, graph, ml etc...
you may get help from cli, for ex; help on graph, type "help graph", for ml type "help ml" etc...

Further, you can run for higher volume with high speed and high volume implementation of the use case.
You can train more models, add more triples etc. as required.
