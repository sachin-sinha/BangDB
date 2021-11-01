User/customer messages/reviews analysis
---------------------------------------

Find the detail steps to run this usecase on your machine at https://bangdb.com/blog/customer-message-analysis-predictive-streaming/

Please find the video of this demo/usecase at https://www.youtube.com/watch?v=Z4Maz0y_rNk 

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

	Checkout the details at https://bangdb.com/blog/customer-message-analysis-predictive-streaming/

Please let me know if you want more features in the use case to be added or another use case to be implemented and shared.
Also do send me your feedback / comment at sachin@bangdb.com
