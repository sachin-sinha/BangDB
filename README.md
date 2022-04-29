# BangDB

Get BangDB 2.0 from;
* Download from https://bangdb.com/download
* Get from github - clone this repo
* wget https://bangdb.com/downloads/bangdb_2.0_centos7.tar.gz
* Take the docker image from https://hub.docker.com/r/bangdb/bangdb

However, it's recommended to register with BangDB (if you download from the website, you will have to register) to get regular updates

It's pretty straight forward to install the server. 
For detail info, please see the README present in the base folder or checkout https://bangdb.com/server-install/



BangDB - nosql database

	 _____________________
	|                     |		BangDB Server (master) ver:2.0 64 bit
	|                     |		IP = 0.0.0.0 : Port = 10101 
	|  BangDB Server 2.0  |		PID = 2658
	|   www.bangdb.com    |
	|__________           |
	|          |          |
	|   BSD    |          |
	| License  |          |
	|__________|__________|



Basic Informantion
------------------

High level features in BangDB includes (not limited to);

* NoSQL database
	* Key value
	* Document
	* Large binary data [ BRS - BangDB Resource Server, deals with large files or objects, exposes S3 like features ]
	* Column [ native types ]
	* Time series

* Stream
	* Ingest any data [ different ways to ingest the data, agents can also be deployed ]
  * Transform [ Transformation before ingestion is not required, can apply this in absolute and probabilistic manner or both ]
  * filter & join [ filter incoming stream on some running conditions and/or join with other to produce another etc. ]
	* aggregate [ slice n dice, groupby etc. ]
	* statistics [ count, unique count, sum, avg, stddev, ex-kurtosis, covar, running stats ]
	* CEP [ Complex event processing, backed by table, scales linearly ]
	* Notifications
	* sliding window (continuous)
	* UDF - [ use default or define your own functions at run time ]
	* Train and predcict on stream

* AI
	* ML
	* IE (Information Extraction)
	* DL (Deep Learning - with Enterprise Edition only)

* Graph
	* Create Graph within BangDB (it's just a table) and store nodes and/or triples (sub-rel-obj)
	* Use Cypher to run query ( little modified version of Cypher for better efficiency, support and speed )
	* Create ontologies and query ( using absolute or probabilistic methods (IE - information extraction))

The db and other components are written in C/C++ and has following core features
to achieve very high performance, efficiency and robustness for scale;

* Buffer pool and page cache
* Adaptive pre-fetch and flushing
* Write ahead log
* transaction (OCC)
* SEDA (Staged Event Driven)
* IO Layer
* primary, secondary, composite, nested, reverse index
* Normal, wide, primitive, sliding window tables
* Fully concurrent read and write

Basic Types
-----------

The db provides simple types, interfaces and APIs, most important types are;

* bangdb_database
* bangdb_table
* bangdb_stream_manager
* bangdb_notification_manager
* bangdb_ml_helper
* bangdb_dl_helper

BangDB Flavors
--------------

BangDB comes in different flavors, namely
* Embedded - BangDB becomes part of the user process. Similar to BerkeleyDB or LevelDB. It can also be run on microprocessors like RaspberryPi etc.
* Server (Client) - BangDB runs as a service and different clients can connect to it for processing. It's a master slave model. Training, BRS etc. could be part of the server or could be deployed as separate instances
* P2P based distributed database - [ Upcoming, later this year ] Implements consistent hashing, Chord+ algo, CAP Knob, high churning, linear scale etc.
Note: API remains same across all flavors [ except in ~5% cases where certain changes are unavoidable ]. This allows portability, one can write app for embedded and deploy for Server or Cluster. In fact I usually write all my apps for embedded as it's easy to debug and test, and then deploy for other flavors

Other Components
----------------

1. Clients - to help user write applications for BangDB, clients are fully concurrent and exposes simple APIs for writing such applications. Please note that the API for BangDB are same for all falvors. The core client is written in C++, it uses TCP socket to communicate. It also implements robust and very efficient message protocol for high performance. Java wrapper is provided for allowing users to write their apps in java/scala

2. Cli - a command line cli to interact with the DB. It uses quasi SQL langauge to interact with the db. It also allows users to deal with streams and draw simple charts in the terminal using Gnuplot for better visualization within terminal. User can also administer agents for streaming data into the BangDB. Further we can also switch the master to slave and vice versa and add slaves etc. and do cluster management work using the cli

3. brs-cli - a command line tool for uploading and downloading large files, much like S3 features


Install and Run
---------------

Running BangDB is very simple

go to the base folder of the bangdb (v2.0/bangdb-2.0_<OS>)

Deal with Prereqs - The binary links with several libraries, few of these are provided along with the server in the lib folder.
However, to ensure you have following libs on the server run the install.sh

   > sudo apt-get update (or sudo yum update)
   > sudo bash install.sh

..................................................................................................................

This will install necessary libs and set the softlinks as well
It also ensures that it has installed java8, python3 (python 3.6 for all, and 3.8 for ubuntu20)

To run IE (information extraction) we need few more lib;
Hence it also installsSPARQLWrapper, wikipedia, html2text

It also sest the PATH and LD_LIBRARY_PATH
libjvm - set the path or create soft link to libjvm which can be found by the server
export LD_LIBRARY_PATH=$JAVA_HOME/jre/lib/amd64/server/
OR
ln -sf $JAVA_HOME/jre/lib/amd64/server/libjvm.so /usr/local/lib/libjvm.so

For Cli, as it needs feedgnuplot which requires gnuplot and perl, hence it brings those as well

..................................................................................................................

That's it. You are ready to run the server in following two ways;

Method 1
--------
>cd bin
>./bangdb-server-2.0

There are many command line args that this can take and ther are defined below in the configuration section

Method 2
--------
>./bangdb-server start

This runs the db in background, you may check the status
./bangdb-server status

and stop the server
>./bangdb-server stop

This method don't allow command line args to be specified, therefore we will need to set those in the bangdb.config file

Configurataion
-------------

Checkout https://www.bangdb.com/bangdb-config for more details on configuring BangDB

There are however several ways to configure for the server, here are the relevant details;

--------------------------------------------------------------------------------------------------------------
	Command line arguments
	----------------------

	There are however several ways to configure for the server through command line arguments, 
	here are the relevant details;

	pls type help to see the options
	./bangdb-server-2.0 -help

	Here are some of the details;

	----------------------------------------------------------------------------------------------------------------------------------------------------------
	Usage: -i [master | slave] -r [yes | no] -t [yes | no] -d [dbname] -s [IP:PORT] -m [IP:PORT] -p [IP] -b [yes | no] -c [tcp | http | hybrid] -w [PORT] -v
	----------------------------------------------------------------------------------------------------------------------------------------------------------
	Options
	-------
	 -i: defines the server's identity [master | slave], default is SERVER_TYPE (master) as defined in bangdb.config
	 -r: defines replication state [yes | no], default is ENABLE_REPLICATION (0) as defined in bangdb.config 
	 -t: defines if transaction is enabled(yes) or disabled(no) [yes | no], default is no 
	 -d: defines the dbname, default is BANGDB_DATABASE_NAME (mydb) as defined in bangdb.config 
	 -s: defines IP:Port of this server, default is SERVER_ID:SERV_PORT as defined in bangdb.config
	 -m: defines IP:Port of the master (required only for slave as it declares master with this option)
	 -p: defines public IP of the server (required for master and slave to expose their own public IP)
	 -b: defines if server to be run in background as daemon, default is foreground
	 -c: defines if server runs as tcp server or http (rest) server or both (hybrid), default is tcp server
	 -w: defines the http port when server runs in http or hybrid mode     default is MASTER_SERVER_ID:MASTER_SERV_PORT as defined in the bangdb.config
	 -v: prints the alpha-numeric version of the executable

	 Hence to run master with other values as defined in the bangdb.config, issue following command
	 ./bangdb-server -s 192.168.1.5:10101

	 To run slave for this master with default other values..
	 ./bangdb-server -i slave -s 192.168.1.6:10102 -m 192.168.1.5:10101
	etc...
	----------------------------------------------------------------------------------------------------------------------------------------------------------


BangDB requires bangdb.config file as an input, you may leave it in the same folder as bangdb-server.

* bangdb.config - using this you can set various run time config for the db. Also it provides
enough hadles with tune the core and internals of db to run in the best possible manner depending upon
the host configuration and boundaries. The config file has details before each of these paramaeters and also
structured in a manner to allow you to pick and modify things in rather confortable way

Please refer www.bangdb.com/developer section to get most of the detail info as needed


Update DB with new version
--------------------------

To update with new version, you won't need 
to do much except,
1. stop the db
2. copy new bangdb-server binary (only one file)
3. re run the db

Hope you find the db useful and it helps you solve some of the problems for you.
Looking forward to connect with you, get your feedback, comments, suggestions etc. soon
I am also going to start the community part here in few weeks

Please feel free to write to me at sachin@bangdb.com for any info, clarity, feedback etc.

Enjoy!
<br>Sachin
 
# Use cases
* I.O.T. vehicle monitoring 
* Analytics from customer reviews 
* Fraud detection 
* Supply chain management 
* and many more...

Check out detailed analysis of all examples here:
https://bangdb.com/docs/bangdb-2-0-use-cases/
