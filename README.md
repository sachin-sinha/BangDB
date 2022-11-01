# BangDB REST CLI

BangDB REST CLI is a python based REST CLI which can be used to perform multiple operations on BangDB Server.

Following arguments are accepted:<br>
	-m : method [GET | POST] (Required)<br>
	-u : uri (Required)<br>
	-p : payload [Required only for POST calls, input data or file path]<br>
	-e : endpoint [Endpoint with Port] (Optional)<br>
	-z : Insert Event [True | False] [Required for inserting multiple records from specified file]
