Monitoring vehicle using various sensors data
---------------------------------------------

Scenario
--------
	
	Today's vehicle has lots of sensors generating lots of different data which if captured could be used
	for vehicle monitoring, predictive analytics, finding anomalies and taking corrective actions as needed
	either locally, remotely or in self healing mannner

	The various data points (sensors) are as follows;
		time
		car
		coolant_temp
		intake_air_temp
		intake_air_flow_speed
		battery_percentage
		battery_voltage
		current_draw
		speed
		engine_vibration_amplitude
		throttle_pos
		tire_pressure_1_1
		tire_pressure_1_2
		tire_pressure_2_1
		tire_pressure_2_2
		accelerometer_1_1_value
		accelerometer_1_2_value
		accelerometer_2_1_value
		accelerometer_2_2_value
		control_unit_firmware

	In this demo, we will stream data for many cars into the system, each car sending one event per sec or more.
	We will use BangDB agent to stream the data into BangDB, and use streaming analysis for these events with 1 day
	as sliding window length (continuous window). Further we will use BangDB ML abstractions to train two models, one
	using existing file and other on data which have been streamed into the database. These models will help us find
	certain anomalies for further action

Solution overview
-----------------

	We intend to do following here;
	
	a. Find anomaly for battery_voltage for any event. This we wish to do by projecting the battery_voltage based
	   on number of past data (train a model for this), then finding the difference with the actual data. 
	   Then we wish to compute the running average of the this difference and when the difference is more than 
	   10% in last 5 min then it's an anomaly. As you see, it's not just a simple computation but rather quite comprehensive

	b. Train a model to predict the speed of the vehicle, note this is different from projection as done in previous case.
	   Then follow the same steps as in (a) above to compute anomaly. In this case the model is trained using following
	   attributes : 
	   coolant_temp,intake_air_temp,intake_air_flow_speed,battery_percentage,battery_voltage,current_draw,engine_vibration_amplitude,throttle_pos

	c. Find a pattern using CEP (complex event processing). The pattern is following;
	   Speed of a car is more than 35 unit and is increasing continuously. And if we observe this for 3 consicutive times in last 1000 sec, then this is a pattern for us and we should keep finding this pattern continuously for all cars	  

	All of these anomalies should be pushed to different streams for notifications or further analysis or action need to be taken as required

	d. Compute running statistics for several attributes, like coolant_temp, battery_voltage, cuurent_draw, speed, emgine_vibration_amplitude etc.

Steps to run the demo
---------------------

	1. Install BangDB. There are many ways to do this, check out https://bangdb.com/download 
	   You may checkout this repo as well and you get BangDB binaries as well with a install.sh file

	2. cd to the usecases/iot-car-sensor-analysis

	3. copy bangdb-server-2.0 into the server/ folder
	   copy bangdb-agent-2.0 into the agent/ folder
	   copy bangdb-cli-2.0 into cli/ folder

	4. run reset.sh to ensure we start from scratch. Each time you wish to start from scratch, run this

	5. Run the server, agent and cli

		> cd  server
		> ./bangdb-server-2.0 -c hybrid -w 18080
		
		> cd ..
		> cd  agent
		> ./bangdb-agent-2.0

		> cd ..
		> cd  cli
		> ./bangdb-cli-2.0

		When you run the cli, you will get a command prompt like following
		note: we will do most of the activities using the cli
	
	sachin@bangdb:/mnt/test/iot_vehicle_monitoring/cli$ ./bangdb-cli-2.0 
	server [ 127.0.0.1 : 10101 ] is master with repl = OFF

	 __     _    _   _   ____   ___    ___
	|   \  / \  | \ | | | ___\ |   \  |   \
	|   / /   \ |  \| | | | __ |    | |   /
	|   \/ ___ \| | \ | | |__|||    | |   \
	|___/_/   \_|_| |_| |_____||___/  |___/
	
	command line tool for db+stream+ai+graph

	please type 'help' to get more info, 'quit' or 'exit' to return

	bangdb>

	
	5. Register the schema (schema is a set of streams and processing/actions that could be done/taken as event arrives)
		
	bangdb> register schema car_sensor_schema.txt

	6. Train battery_voltage_model. Command train model, initiates a workflow and cli will ask several questions and finally
	   schedules the training, see below to get the details

	bangdb> train model battery_voltage_model
	what's the name of the schema for which you wish to train the model?: cars
	do you wish to read earlier saved ml schema for editing/adding? [ yes |  no ]: 


		BangDB supports following algorithm, pls select from these
		Classification (1) | Regression (2) | Lin-regression/Classification (3) | Kmeans (4) | Custom (5)
		| IE - ontology (6) | IE - NER (7) | IE - Sentiment (8) | IE - KB (9) | TS - Forecast (10) 
		| DL - resnet (11) | DL - lenet (12) | DL - face detection (13) | DL - shape detection (14) | SL - object detection (15)

	what's the algo would you like to use (or Enter for default (1)): 10
	do you wish to select details of algo and params for the forecast model training? [ yes |  no ]: yes


		For forecast, pls select algo from these
		Regression (2) | Lin-regression/Classification (3))

	what's the algo would you like to use (or Enter for default (2)): 3


		available solver type for libliner
		L2R_LR, L2R_L2LOSS_SVC_DUAL, L2R_L2LOSS_SVC, L2R_L1LOSS_SVC_DUAL, MCSVM_CS, 	

		1R_L2LOSS_SVC, L1R_LR, L2R_LR_DUAL, L2R_L2LOSS_SVR = 11, L2R_L2LOSS_SVR_DUAL, L2R_L1LOSS_SVR_DUAL



		tuning of params is only available for solver L2R_LR (0), L2R_L2LOSS_SVC (2) and L2R_L2LOSS_SVR (11)

		solver type [ 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 11 | 12 | 13 ] (press enter for default (0)): 11
		enter C (or press enter for default): 
		enter nr_weight (or press enter for default(1)): 
		enter p, epslon_svr (or press enter for default(0.1)): 
		enter bias (or press enter for default (0)): 
		enter fold (or press enter for default (5)): 
		what's the stopping criteria (or press enter for default (0.001)): 
	enter the input file for forecast training (along with full path): ../data/train.txt
	what's the format of the file [ CSV (1) | JSON (2) ] (or Enter for default (1)): 1
	enter the time-stamp field name: time
	enter the time-stamp field datatype [ string (5) | long (9) | double (11) ] (or Enter for default (9)): 9
	what's the position of timestamp field in the csv (count starts with 0): 0
	do you wish to use entity for groupby? [ yes |  no ]: yes
	enter the entity (group by) field name: car
	enter the entity (group by) field datatype [ string (5) | long (9) | double (11) ] (or Enter for default (9)): 9
	what's the position of entity (group by) field in the csv (count starts with 0, enter -1 ignore): 1
	enter the quantity field name: battery_voltage
	what's the position of quantity field in the csv (count starts with 0): 6
	do you wish to ignore grouping by entity? [ yes |  no ]: 
	what's the granularity [ day (1) | week (2) | month (3) | year (4) | no_rollup(5) ] for aggregation during rollup of quantity (default is day(1)): 5
	what's the lag for data to be selected for prediction (default is 2)?: 5
	what's the offset for data to be selected for prediction (default is 0)?: 0
	
	do you wish to schedule for the training of the forecast model now? [ yes |  no ]: yes


	you can check the status of model by typing
	bangdb> show models


	7. Ingest the data (from train.txt file)

	> cd ../mon
	> bash sendfile ../data/train.txt car.txt 100 1
	> cd ../cli

	The above command will simulate 100 cars sending data every second

	Wait until it sends 7000 events.

	8. Train model speed_pred_model. This will predict the speed of the car


	bangdb> train model speed_pred_model
	what's the name of the schema for which you wish to train the model?: cars
	do you wish to read earlier saved ml schema for editing/adding? [ yes |  no ]: 


		BangDB supports following algorithm, pls select from these
		Classification (1) | Regression (2) | Lin-regression/Classification (3) | Kmeans (4) | Custom (5)
		| IE - ontology (6) | IE - NER (7) | IE - Sentiment (8) | IE - KB (9) | TS - Forecast (10) 
		| DL - resnet (11) | DL - lenet (12) | DL - face detection (13) | DL - shape detection (14) | SL - object detection (15)

	what's the algo would you like to use (or Enter for default (1)): 3


		available solver type for libliner
		L2R_LR, L2R_L2LOSS_SVC_DUAL, L2R_L2LOSS_SVC, L2R_L1LOSS_SVC_DUAL, MCSVM_CS, 	

		1R_L2LOSS_SVC, L1R_LR, L2R_LR_DUAL, L2R_L2LOSS_SVR = 11, L2R_L2LOSS_SVR_DUAL, L2R_L1LOSS_SVR_DUAL



		tuning of params is only available for solver L2R_LR (0), L2R_L2LOSS_SVC (2) and L2R_L2LOSS_SVR (11)

		solver type [ 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 11 | 12 | 13 ] (press enter for default (0)): 11
		enter C (or press enter for default): 
		enter nr_weight (or press enter for default(1)): 
		enter p, epslon_svr (or press enter for default(0.1)): 
		enter bias (or press enter for default (0)): 
		enter fold (or press enter for default (5)): 
		what's the stopping criteria (or press enter for default (0.001)): 
	what's the input (training data) source? [ local file (1) | file on BRS (2) | stream (3) ] (press enter for default (1)): 3
	enter the name of the stream from which the data should be uploaded: sensor
	enter the approx of the size of the file in MB(enter for default): 10
	enter the duration is seconds upto which the data will be selected from the stream for training (enter for default 3600 sec): 
	what is the target index (to select the target attribute/val): 0
	what's the training speed you wish to select [ Very fast (1) | fast (2) | medium (3) | slow (4) | very slow (5) ] (or Enter for default (1)): 3
	what's the attribute type [ NUM (1) | STRING (2) | HYBRID (3) ] (press enter for default (1): 
		do you wish to scale the data? [ yes |  no ]: no
		do you wish to tune the params? [ yes |  no ]: yes


		we need to do the mapping so it can be used on streams later
		This means we need to provide attr name and its position in the training file

	attr name: speed
	attr position: 0
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: coolant_temp
	attr position: 1
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: intake_air_temp
	attr position: 2
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: intake_air_flow_speed
	attr position: 3
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: battery_percentage
	attr position: 4
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: battery_voltage
	attr position: 5
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: current_draw
	attr position: 6
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: engine_vibration_amplitude
	attr position: 7
	do you wish to add more attributes? [ yes |  no ]: yes
	attr name: throttle_pos
	attr position: 8
	do you wish to add more attributes? [ yes |  no ]: 
	do you wish to add external udf to do some computations before the training? [ yes |  no ]: 

	do you wish to start training now? [ yes |  no ]: yes

	you can check the status of the model by typing
	bangdb> show models

	+--------------------------+---------------------+----+------------+-----------+------------------------+------------------------+
	|key                       |model name           |algo|train status|schema name|train start time        |train end time          |
	+--------------------------+---------------------+----+------------+-----------+------------------------+------------------------+
	|cars:speed_pred_model     |speed_pred_model     | LIN|passed      |cars       |Mon Oct 18 14:57:38 2021|Mon Oct 18 14:57:38 2021|
	+--------------------------+---------------------+----+------------+-----------+------------------------+------------------------+
	|cars:battery_voltage_model|battery_voltage_model| LIN|passed      |cars       |Mon Oct 18 14:52:01 2021|Mon Oct 18 14:52:01 2021|
	+--------------------------+---------------------+----+------------+-----------+------------------------+------------------------+


	9. now start ingesting data from other file, this time ingest slowly to see some results
	
        > cd ../mon
        > bash sendfile ../data/test.txt car.txt 10 1
        > cd ../cli


	to see summary of events in different streams
	bangdb> select stream from cars

	to select data from sensors stream
	bangdb> select * from cars.sensor

	to see aggregated data for coolant_temp
	bangdb> select aggr(coolant_temp) from cars.sensor rollup 0

	you can also plot the data in the terminal 
	bangdb> select * from cars.sensor where _pk > 1 plot {"type":"line","attrs":["speed","speed_pred"],"just_plot":1} limit 25

                                                                               
	                                bangdb_plot scan                               
                                                                               
	  40 +-+---------+----------+-----------+-----------+----------+---------+-+   
	     +           +          +  *      * +           +      *** +           +   
	  35 +-+                       **     **                   *# **         +-+   
	     |                         **     * *                  *    ***        |   
	  30 +-+                       *#*    * *                  *       *     +-+   
	     |                         * *    * *                  *        *      |   
	     |                    *    * *    * *                  *        *  *   |   
	  25 +-+                  **   * *    * #*          *      *        * *  +-+   
	     |                    * *  * *    *  #*  #      **     *        **     |   
	  20 +-+         ** ***   * *  * *    *   *  *#     *#*    *        * ## +-+   
	     |          *# *###*  *  **  *   #*   *  **#    * *    *               |   
	  15 +-+       *#      #* *  **  *   *    *  * *   *  *    *             +-+   
	     |        * #       **   *   *## *     * * ****   # * #*               |   
	  10 +-+      #         **        **#*     * * *       #* *              +-+   
	     |                  *           *      *#* *        #**                |   
	     |                                     **            **                |   
	   5 +-+                                   **            *               +-+   
	     +           +          +           +  *        +          +           +   
	   0 +-+---------+----------+-----------+-----------+----------+---------+-+   
        	    1.63455e+1 1.63455e+15 1.63455e+15 1.63455e+1 1.63455e+ 1.63455e+15
                                                                               
	total rows retrieved = 25 (25)
	more data to come, continue .... [y/n]: n

	Note: as you see, the speed and predicted speed are close most of the time
	and so on ...

	10. to similate the pattern, insert following events (cut and paste on the cli prompt one by one)

insert into cars.sensor values null  {"time":1567607187,"car":100,"coolant_temp":191.3604,"intake_air_temp":19.891075,"intake_air_flow_speed":9.86402,"battery_percentage":-18.83759,"battery_voltage":242.07639,"current_draw":15.151241,"speed":35.703476,"engine_vibration_amplitude":2570.3477,"throttle_pos":0.6609447000000001,"tire_pressure_1_1":22,"tire_pressure_1_2":34,"tire_pressure_2_1":31,"tire_pressure_2_2":33,"accelerometer_1_1_value":0.0812409499999999,"accelerometer_1_2_value":3.3291862,"accelerometer_2_1_value":3.0881116,"accelerometer_2_2_value":0.033119857,"control_unit_firmware":1000}


insert into cars.sensor values null {"time":1567607187,"car":100,"coolant_temp":191.3604,"intake_air_temp":19.891075,"intake_air_flow_speed":9.86402,"battery_percentage":-18.83759,"battery_voltage":242.07639,"current_draw":15.151241,"speed":36.703476,"engine_vibration_amplitude":2570.3477,"throttle_pos":0.6609447000000001,"tire_pressure_1_1":22,"tire_pressure_1_2":34,"tire_pressure_2_1":31,"tire_pressure_2_2":33,"accelerometer_1_1_value":0.0812409499999999,"accelerometer_1_2_value":3.3291862,"accelerometer_2_1_value":3.0881116,"accelerometer_2_2_value":0.033119857,"control_unit_firmware":1000}


insert into cars.sensor values null {"time":1567607187,"car":100,"coolant_temp":191.3604,"intake_air_temp":19.891075,"intake_air_flow_speed":9.86402,"battery_percentage":-18.83759,"battery_voltage":242.07639,"current_draw":15.151241,"speed":37.703476,"engine_vibration_amplitude":2570.3477,"throttle_pos":0.6609447000000001,"tire_pressure_1_1":22,"tire_pressure_1_2":34,"tire_pressure_2_1":31,"tire_pressure_2_2":33,"accelerometer_1_1_value":0.0812409499999999,"accelerometer_1_2_value":3.3291862,"accelerometer_2_1_value":3.0881116,"accelerometer_2_2_value":0.033119857,"control_unit_firmware":1000}


insert into cars.sensor values null {"time":1567607187,"car":100,"coolant_temp":191.3604,"intake_air_temp":19.891075,"intake_air_flow_speed":9.86402,"battery_percentage":-18.83759,"battery_voltage":242.07639,"current_draw":15.151241,"speed":38.703476,"engine_vibration_amplitude":2570.3477,"throttle_pos":0.6609447000000001,"tire_pressure_1_1":22,"tire_pressure_1_2":34,"tire_pressure_2_1":31,"tire_pressure_2_2":33,"accelerometer_1_1_value":0.0812409499999999,"accelerometer_1_2_value":3.3291862,"accelerometer_2_1_value":3.0881116,"accelerometer_2_2_value":0.033119857,"control_unit_firmware":1000}



	If you run "select stream from cars" you will see one event there in the cep output stream.
	Basically we simulated continulously increasing speed of a particular car for 3 times in 1000 sec window

	Please go to https://bangdb.com/developer for more info on BangDB

	Please subsribe to our channel for more videos on different real world use cases
	Please follow us on twitter at https://twitter.com/iqlect
