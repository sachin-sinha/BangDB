#!/bin/bash
## find os type
osv=0
x=$(awk -F= '/^ID/{print $2;exit}' /etc/os-release)
if [ "$x" = '"centos"' ]; then
	echo "installing for centos"
	osv=1
elif [ "$x" = 'ubuntu' ]; then
	echo "installing for ubuntu"
	osv=2
elif [ "$x" = '"rhel"' ]; then
	echo "installing for red hat"
	osv=3
else
	echo "unkown os [ $x ] , quitting..."
	osv=0
	exit
fi

# common
echo 'export PATH=/usr/local/bin:/usr/local/include:$PATH' >>~/.bash_profile
echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >>~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >>~/.profile

sudo echo 'LC_ALL="en_US.utf8"' >> /etc/environment
sudo echo 'LC_CTYPE="en_US.utf8"' >> /etc/environment
sudo echo 'LANGUAGE="en_US.utf8"' >> /etc/environment


#### installing necessary packages and libs
if [ $osv -eq 2 ]
then
	sudo apt-get install build-essential

lib=libopenssl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
	echo "$lib is not installed, installing ... "
	sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=libcurl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=python3.8
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
    	sudo apt-get update
   	sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=liblapack-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=libblas-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
	echo "$lib is installed"
fi

lib=libreadline-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi

lib=openjdk-8-jdk
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=gnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi
lib=feedgnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install $lib
else
        echo "$lib is installed"
fi

#else for centos and rhel
else
	sudo yum group install 'Development Tools'
	sudo yum install curl-devel
lib=openssl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
	echo "$lib is not installed, installing ... "
	sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=curl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=python36
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
	sudo ln -sf /usr/bin/python2.7 /usr/bin/python
else
        echo "$lib is installed"
fi
lib=lapack
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=blas
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
	echo "$lib is installed"
fi

lib=readline-devel
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi

lib=java-1.8.0-openjdk-devel
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
#### needed for cli, for feedgnuplot
lib=gnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl-JSON-PP
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl-CPAN
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl-String-ShellQuote
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl-IPC-Run
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
lib=perl-List-MoreUtils
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum install $lib
else
        echo "$lib is installed"
fi
#$(perl -MCPAN -e install Time::Piece)

sudo cp helpers/feedgnuplot /usr/local/bin

fi


# common
sudo pip3 install SPARQLWrapper
sudo pip3 install urllib3
sudo pip3 install wikipedia
sudo pip3 install HtmlParser
sudo pip3 install html2text

###### installing bangdb libs now

USR_LIB_LOC=/usr/local/lib
USR_INC_LOC=/usr/local/include
USR_LIB64=/usr/lib64
USR_INC64=/usr/include

if [ -d "/usr/lib64" ]
then
	USR_LIB64=/usr/lib64
else
	USR_LIB64=/usr/lib
fi

sudo cp $PWD/libs/libbangdb-client-cpp.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client-cpp_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client-java.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-cpp.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-cpp_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-java.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libdlib.so.19.20.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libmitie.so $USR_LIB_LOC/


sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp.so.2.0 $USR_LIB_LOC/libbangdb-client-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp_s.so.2.0 $USR_LIB_LOC/libbangdb-client-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-java.so.2.0 $USR_LIB_LOC/libbangdb-client-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client.so.2.0 $USR_LIB_LOC/libbangdb-client.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client_s.so.2.0 $USR_LIB_LOC/libbangdb-client_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp.so.2.0 $USR_LIB_LOC/libbangdb-embd-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp_s.so.2.0 $USR_LIB_LOC/libbangdb-embd-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-java.so.2.0 $USR_LIB_LOC/libbangdb-embd-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd.so.2.0 $USR_LIB_LOC/libbangdb-embd.so


sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp.so.2.0 $USR_LIB64/libbangdb-client-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp_s.so.2.0 $USR_LIB64/libbangdb-client-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-java.so.2.0 $USR_LIB64/libbangdb-client-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client.so.2.0 $USR_LIB64/libbangdb-client.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client_s.so.2.0 $USR_LIB64/libbangdb-client_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp.so.2.0 $USR_LIB64/libbangdb-embd-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp_s.so.2.0 $USR_LIB64/libbangdb-embd-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-java.so.2.0 $USR_LIB64/libbangdb-embd-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd.so.2.0 $USR_LIB64/libbangdb-embd.so

sudo ln -sf $USR_LIB_LOC/libdlib.so.19.20.0 $USR_LIB64/libdlib.so.19.20.0
sudo ln -sf $USR_LIB_LOC/libmitie.so $USR_LIB64/libmitie.so


jv=$(echo $JAVA_HOME)
if [ -z "$jv" ]
then
	echo "JAVA_HOME is not set up, pls set it up. right now using hard link"
	#sudo ln -sf /lib/jvm/java-1.8.0/jre/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
	sudo ln -sf /lib/jvm/jre-1.8.0/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
else
	sudo ln -sf $JAVA_HOME/jre/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
fi
sudo ldconfig

echo "created env vars, soft links for the libs for bangdb"

sudo cp -r bangdb_udf $USR_INC_LOC/
sudo cp -r include/bangdb-embd $USR_INC_LOC/
sudo cp -r include/bangdb-client $USR_INC_LOC/

sudo ln -sf $USR_INC_LOC/bangdb_udf $USR_INC64/bangdb_udf
sudo ln -sf $USR_INC_LOC/bangdb-embd $USR_INC64/bangdb-embd
sudo ln -sf $USR_INC_LOC/bangdb-client $USR_INC64/bangdb-client

echo "copied the include folders for bangdb"

v=$(whereis mvn)
if [ -z "$v" ]
then
	echo "mvn is not installed"
	if [ $osv -eq 2 ]
	then
		sudo apt-get install maven
	else
		sudo yum install maven
	fi	
fi
mvn install:install-file -Dfile=jars/bangdb-client-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-client-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
mvn install:install-file -Dfile=jars/bangdb-embd-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-embd-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
mvn install:install-file -Dfile=jars/gson-2.6.2.jar -DgroupId=com.google -DartifactId=gson-2.6.2 -Dversion=2.6.2 -Dpackaging=jar -DgeneratePom=true
mvn install:install-file -Dfile=jars/bangdb-reverb.jar -DgroupId=com.bangdb -DartifactId=bangdb-reverb -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
echo "bangdb install done!"

