#!/bin/sh

javac -cp .:../lib/bangdb-embd-java.jar testbangdb/GetThread.java testbangdb/PutThread.java testbangdb/Common.java testbangdb/StopWatch.java testbangdb/TestCases.java testbangdb/TestMain.java testbangdb/TestUnits.java
