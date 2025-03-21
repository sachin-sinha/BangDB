<!--
Copyright (c) 2014 - 2015 YCSB contributors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License"); you
may not use this file except in compliance with the License. You
may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied. See the License for the specific language governing
permissions and limitations under the License. See accompanying
LICENSE file.
-->

## Quick Start

This section describes how to run YCSB on BangDB. 

### 1. Start BangDB

	./bangdb-server-2.0 -d ycsb

### 2. Install Java and Maven

### 3. Set Up YCSB

Git clone YCSB and compile:

    git clone https://github.com/sachin-sinha/YCSB
    cd YCSB
    git checkout db_bangdb
    mvn -pl site.ycsb:bangdb-binding -am clean package

### 4. Provide BangDB Connection Parameters
    
	copy the bangdb.config file at the base folder [ YCSB folder ]

### 5. Load data and run tests

Load the data:

    ./bin/ycsb load bangdb -threads 128 -s -P workloads/workloada

Run the workload test:

    ./bin/ycsb run bangdb -threads 128 -s -P workloads/workloada

and so on...

If you get the error of not finding the bangdb-client-java lib, set following;
export LD_LIBRARY_PATH = /usr/local/lib
etc...

Checkout the https://bangdb.com/ycsb/ for more details

