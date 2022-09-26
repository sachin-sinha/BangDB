README

bangdb_rest_cli.py is a simple command for executing REST APIs for BangDB. Here are some details;

1. GET and POST APIs are supported for now
2. The end point in the python file should be changed to point as per need
3. Following options are supported in the command line arguments

   -m : method  [ GET | POST ]
   -u : uri     [ uri of the resource, ex; /db]
   -p : payload [ in case of POST call, provide the payload within '' quote]

   Example:
   A. to get the name of the db;
      python3 bangdb_rest_cli.py -m GET -u /db

      output:
      200
      {"dbname":"mydb"}

It prints return code (error or success) and then the actual value returned

  B. to query a Graph or run cypher query
     The uri structure is /graph/<graph_name>/query

     Therefore, for graph name "myg", we can execute the cypher query like following;
     python3 bangdb_rest_cli.py -m POST -u /graph/myg/query -p 'S=>(@p Person:*); RETURN p.name AS Person'

To see most of the REST API supported by BangDB, please visit https://bangdb.com/docs/bangdb-2-0-rest-api/api-2-0/introduction/

please send me feedback or comments or if you need to see more features here
