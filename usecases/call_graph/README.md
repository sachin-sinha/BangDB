Let's say we need to store call data such that it can be analysed in different ways using set of queries.
There are people calling each other and we capture name of the caller, callee, phone number, location, gender of both caller and callee along with timestamp of call start and end.
Following queries we would be interested in

 A. list of persons calling others
 B. list of persons calling each other, person A calls B and B calls A
 C. list of persons not calling each other, person A calls B but B doesn't call A
 D. list of persons with gender 'Man' calling other persons
 E. list of persons with gender 'Man' calling 'Woman'
 F. list of persons with gender 'Man' and from 'Pattaya' calling other persons with gender 'Man'
 G. person who received call from 'Henry' in month of Jan

The datafile : log_of_calls.csv
Schema : calls_schema.txt
Agent config :agent.conf

Step 1: Run server, agent and cli
	cd server/	
	./bangdb-server-2.0

	cd ../agent/
	./bangdb-agent-2.0

	cd ../cli/
	./Run bangdb-cli-2.0

Step 2: Register schema calls_schema.txt

	bangdb> register schema calls_schema.txt

Step 3: ingest data using sendline.sh

	cd ../mon/
	bash sendline.sh ../data/log_of_calls.csv log_calls.csv 1 1

	This would ingest few events into the stream

Step 4: We would like to run following queries using cli

	cd ../cli/
	bangdb> USE GRAPH cdr_graph

	A. list of persons calling others
		S=>(person:*)-[CALLS]->(person:*)

	+---------------+-----+----------------+
	|sub            |pred |             obj|
	+---------------+-----+----------------+
	|person:Henry   |CALLS|    person:Micah|
	+---------------+-----+----------------+
	|person:Gabriel |CALLS|   person:Jaziel|
	+---------------+-----+----------------+
	|person:Dominick|CALLS|    person:Kenna|
	+---------------+-----+----------------+
	|person:Aleena  |CALLS|person:Antonella|
	+---------------+-----+----------------+
	|person:Nayeli  |CALLS|    person:Freya|
	+---------------+-----+----------------+
	|person:Jaziel  |CALLS|  person:Gabriel|
	+---------------+-----+----------------+



	B. list of persons calling each other, person A calls B and B calls A
		S{SYMM}=>(person:*)-[CALLS]->(person:*)

	+--------------+-----+--------------+
	|sub           |pred |           obj|
	+--------------+-----+--------------+
	|person:Gabriel|CALLS| person:Jaziel|
	+--------------+-----+--------------+
	|person:Jaziel |CALLS|person:Gabriel|
	+--------------+-----+--------------+


	C. list of persons not calling each other, person A calls B but B doesn't call A
		S{ASYMM}=>(person:*)-[CALLS]->(person:*)

	+---------------+-----+----------------+
	|sub            |pred |             obj|
	+---------------+-----+----------------+
	|person:Henry   |CALLS|    person:Micah|
	+---------------+-----+----------------+
	|person:Dominick|CALLS|    person:Kenna|
	+---------------+-----+----------------+
	|person:Aleena  |CALLS|person:Antonella|
	+---------------+-----+----------------+
	|person:Nayeli  |CALLS|    person:Freya|
	+---------------+-----+----------------+


	D. list of persons with gender 'Man' calling other persons
		S=>(@p1 person:* {from_gender = "Man"})-[@c CALLS]->(@p2 person:*); RETURN p1.name AS p1name, p2.name AS p2name

	+--------+-------+
	|p1name  |p2name |
	+--------+-------+
	|Henry   |Micah  |
	+--------+-------+
	|Dominick|Kenna  |
	+--------+-------+
	|Jaziel  |Gabriel|
	+--------+-------+


	E. list of persons with gender 'Man' calling 'Woman'
		S=>(@p1 person:* {from_gender = "Man"})-[@c CALLS]->(@p2 person:* {to_gender = "Woman"}); RETURN p1.name AS p1name, p2.name AS p2name

	+--------+------+
	|p1name  |p2name|
	+--------+------+
	|Dominick|Kenna |
	+--------+------+


	F. list of persons with gender 'Man' and from 'Pattaya' calling other persons with gender 'Man'
		S=>(@p1 person:* {from_gender = "Man" AND from_city = "Pattaya"})-[@c CALLS]->(@p2 person:* {to_gender = "Man"}); RETURN p1.name AS p1name, p1.from_city AS fcity, p2.name AS p2name, p2.to_city AS tcity

	+------+-------+-------+------------+
	|p1name|fcity  | p2name|tcity       |
	+------+-------+-------+------------+
	|Henry |Pattaya|  Micah|Bangkok     |
	+------+-------+-------+------------+
	|Jaziel|Pattaya|Gabriel|Kanchanaburi|
	+------+-------+-------+------------+


	G. person who received call from 'Henry' in month of Jan
		S=>(@p1 person:Henry)-[@c CALLS {from_month = 0}]->(@p2 person:*); RETURN p2.name AS p2name

	+------+
	|p2name|
	+------+
	|Micah |
	+------+


