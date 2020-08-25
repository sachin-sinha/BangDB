# BangDB
BangDB - nosql database


	 _____________________
	|                     |		BangDB Server (master) ver:0.9 64 bit
	|                     |		IP = 0.0.0.0 : Port = 10101 
	|  BangDB Server 2.0  |		PID = 1597
	|   www.iqlect.com    |
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

Basic Types
-----------

The db provides simple types, interfaces and APIs, most important types are;

* bangdb_database
* bangdb_table
* bangdb_stream_manager
* bangdb_notificatin_manager
* bangdb_ml_helper
* bangdb_dl_helper

BangDB flavors
--------------

BangDB comes in different flavors, namely
* Embedded - BangDB becomes part of the user process. Similar to BerkeleyDB or LevelDB. It can also be run on microprocessors like RaspberryPi etc.
* Server (Client) - BangDB runs as a service and different clients can connect to it for processing. It's a master slave model. Training, BRS etc. could be part of the server or could be deployed as separate instances
* P2P based distributed database - [ Upcoming, later this year ] Implements consistent hashing, Chord+ algo, CAP Knob, high churning, linear scale etc.
Note: API remains same across all flavors [ except in ~5% cases where certain changes are unavoidable ]. This allows portability, one can write app for embedded and deploy for Server or Cluster. In fact I usually write all my apps for embedded as it's easy to debug and test, and then deploy for other flavors

Other components
----------------

1. Clients - to help user write applications for BangDB, clients are fully concurrent and exposes simple APIs for writing such applications. Please note that the API for BangDB are same for all falvors. The core client is written in C++, it uses TCP socket to communicate. It also implements robust and very efficient message protocol for high performance. Java wrapper is provided for allowing users to write their apps in java/scala

2. Cli - a command line cli to interact with the DB. It uses quasi SQL langauge to interact with the db. It also allows users to deal with streams and draw simple charts in the terminal using Gnuplot for better visualization within terminal. User can also administer agents for streaming data into the BangDB. Further we can also switch the master to slave and vice versa and add slaves etc. and do cluster management work using the cli

3. brs-cli - a command line tool for uploading and downloading large files, much like S3 features


Install and run
---------------

Running BangDB is 3 steps process (first time, after that it's simply single step flow)

Step1 - Deal with Prereqs - The binary links with several libraries, few of these are provided along with the server in the lib folder.
However, please ensure you have following libs on the server (most of these might already be there or 
simply get from appropriate repo(apt, yum etc.)

First install "build-essential" (ubuntu) or "Development Tools" on centos 
sudo apt-get install build-essential [ ubuntu]
sudo yum groupinstall 'Development Tools' [ centos ]

Second, ensure that you have installed java8, python3

Then it needs certain other libs to be installed
ssl, crypto, curl, rt, dl, X11, pthread, lapack, blas, python3 
Note: for python, pls pick the right binary based on which version you would like to link with 3.5, 3.6, 3.8 so on..

Finally it also needs lib mitie, dlib which is present in the download folder

Step2 - Create a base folder/dir, untar the download file there, let's say we are trying to run server, take server binary and keep it in a folder.

Step3 - Run install.sh to have several soft links configured as required

That's it. You are ready to run the server by simply typing following

./bangdb-server-2.0


Configurtaion
-------------

There are however several ways to configure for the server, here are the relevant details;

* configure how server should be run [ master, slave, isolated, foreground, background etc ... ]
pls type help to see the options
./bangdb-server-2.0 -help

Here are some of the details;

Usage: -i [master | slave] -r [yes | no] -t [yes | no] -d [dbname] -s [IP:PORT] -m [IP:PORT] -b [yes | no] -v

Options

 * -i: defines the server's identity [master | slave], default is SERVER_TYPE as defined in bangdb.config
 * -r: defines replication state [yes | no], default is ENABLE_REPLICATION as defined in bangdb.config 
 * -t: defines if transaction is enabled(yes) or disabled(no) [yes | no], default is no 
 * -d: defines the dbname, default is BANGDB_DATABASE_NAME as defined in bangdb.config 
 * -s: defines IP:Port of this server, default is SERVER_ID:SERV_PORT as defined in bangdb.config
 * -m: defines IP:Port of the master (required only for slave as it declares master with this option)
 * -b: defines if server to be run in background as daemon
     default is MASTER_SERVER_ID:MASTER_SERV_PORT as defined in the bangdb.config
 * -v: prints the alpha-numeric version of the executable

 Hence to run master with other values as defined in the bangdb.config, issue following command
 ./bangdb-server -s 192.168.1.5:7887

 To run slave for this master with default other values..
 ./bangdb-server -i slave -s 192.168.1.6:7887 -m 192.168.1.5:7887
etc...

BangDB requires bangdb.config file as an input, you may leave it in the same folder as bangdb-server.

* bangdb.config - using this you can set various run time config for the db. Also it provides
enough hadles with tune the core and internals of db to run in the best possible manner depending upon
the host configuration and boundaries. The config file has details before each of these paramaeters and also
structured in a manner to allow you to pick and modify things in rather confortable way

Please refer www.bangdb.com/developer section to get most of the detail info as needed

We are working hard to provide more help and information on our website and also for next 3 months,
we will be releasing and updating BangDB on weekly basis. 

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
Sachin
 
