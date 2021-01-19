#!/bin/sh

javac -cp .:../../jars/bangdb-client-java.jar testbangdb/GetThread.java testbangdb/PutThread.java testbangdb/Common.java testbangdb/StopWatch.java testbangdb/TestCases.java testbangdb/TestMain.java testbangdb/TestUnits.java
