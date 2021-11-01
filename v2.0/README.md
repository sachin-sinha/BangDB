BangDB 2.0 is supported for centos7, cenots8, ubuntu16, ubuntu18, ubuntu20 and rhel8
For other platform, you may use the docker image https://hub.docker.com/r/bangdb/bangdb (see  https://bangdb.com/docker for more info )

Get BangDB from https://bangdb.com/download
It's better to get from the website as you can get update from us as necessary.

Or, You can also get from this repo (clone it)

Or, simply use wget;

wget https://bangdb.com/downloads/bangdb_2.0_rhel8.tar.gz

go to the base folder and follow the README to install the db


About BangDB 2.0
----------------

BangDB 2.0 is a stable release.

BangDB is a converged nosql database which natively integrates machine learning, stream processing within the database, which makes the data ingestion, processing and actions relatively simple and scalable.

BangDB supports multi-model data structure. Document, Key/Val, Time-series, Graph are supported models.

BangDB is a persistent database with options to rin-in-memory as well. It implements its own buffer pool, page cache, write ahead logging, IO Layer, transaction for durability, high performance and scaling purposes. BangDB 2.0 is one of the fastest databases in the world.

BangDB stream processing is suitable for high speed event analysis for fast moving time-series data. It supports sliding window, complex event processing, join and many other features to enable continuous intelligence

BangDB has machine learning, Information extraction directly integrated within it. This makes enabling predictive use cases on data being ingested rather simple and in time accelerated manner. At the same time it allows users to leverage external frameworks (ex; tensor-flow, pytorch etc.) or import externally trained model or even the python file for training and prediction. BangDB achieves these with a simple interface and abstraction that it offers which is consistent for all frameworks

BangDB also implements BRS (BangDB Resource Server) to handle large files. It mimics S3 interface to do so. This helps in deploying BangDB within the local area network without having to leave the boundary even for tasks which requires S3 features. Moreover, this is also helpful for storing large binary files in scalable and high performance manner

BangDB can be deployed in different manner. It can be embedded within a process (device), or in client server model or even in p2p way. The client code is independent of the deployment model, hence same app can work for one deployment model or the other

BangDB implements several indexes. Primary, secondary, nested, composite, geospatial, reverse are examples here. This allows user to write complex queries and execute with very low latency and in scalable manner

BangDB supports different kinds of table (for different model), namely key value, document and graph. BangDB also supports Cypher query language for graph processing and query

BangDB is suitable as high performance multi-model nosql database which scales linearly. Or it can also be used for data analysis purposes especially for real time data processing

You can find more info at https://bangdb.com/developer
You can write directly to me at sachin@bangdb.com

Kindly let me know you feedback, thoughts and what do you think we should add further and it will be a great help.

Enjoy!
Sach
