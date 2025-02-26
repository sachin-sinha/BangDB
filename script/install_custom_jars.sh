#!/bin/bash

mvn install:install-file -Dfile=jars/bangdb-client-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-client-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
mvn install:install-file -Dfile=jars/bangdb-embd-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-embd-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
mvn install:install-file -Dfile=jars/bangdb-reverb.jar -DgroupId=com.bangdb -DartifactId=bangdb-reverb -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true

