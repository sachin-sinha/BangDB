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
echo 'export PATH=/usr/local/bin:/usr/local/include:/usr/lib:/usr/lib64:$PATH' >> ~/.bash_profile
echo 'export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/lib64:$LD_LIBRARY_PATH' >> ~/.profile

echo 'LC_ALL="en_US.utf8"' | sudo tee -a /etc/environment  &> /dev/null
echo 'LC_CTYPE="en_US.utf8"' | sudo tee -a /etc/environment &> /dev/null
echo 'LANGUAGE="en_US.utf8"' | sudo tee -a /etc/environment &> /dev/null

alias brc='source ~/.bashrc'

#### installing necessary packages and libs
if [ $osv -eq 2 ]
then
	sudo apt-get install -y build-essential

lib=libopenssl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
	echo "$lib is not installed, installing ... "
	sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi
lib=libcurl4-openssl-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
	sudo apt-get install -y libcurl
else
        echo "$lib is installed"
fi
lib=python3.6
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
   	sudo apt-get install -y $lib
	sudo apt install -y python3-pip
else
        echo "$lib is installed"
	sudo apt install -y python3-pip
fi
lib=liblapack-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi
lib=libblas-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
	echo "$lib is installed"
fi

lib=libreadline-dev
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi

lib=openjdk-8-jdk
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi
lib=gnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi
lib=feedgnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo apt-get install -y $lib
else
        echo "$lib is installed"
fi

#else for centos and rhel
else
	sudo yum -y group install 'Development Tools'
	sudo yum -y install curl-devel
lib=openssl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
	echo "$lib is not installed, installing ... "
	sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=curl
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=python36
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
	sudo ln -sf /usr/bin/python2.7 /usr/bin/python
else
        echo "$lib is installed"
fi
lib=lapack
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=blas
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
	echo "$lib is installed"
fi

lib=readline-devel
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi

lib=java-1.8.0-openjdk-devel
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
#### needed for cli, for feedgnuplot
lib=gnuplot
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-core
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-JSON-PP
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-CPAN
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-String-ShellQuote
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-IPC-Run
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
lib=perl-List-MoreUtils
v=$(ldconfig -p | grep $lib)
if [ -z "$v" ]
then
        echo "$lib is not installed, installing ... "
        sudo yum -y install $lib
else
        echo "$lib is installed"
fi
#$(perl -MCPAN -e install Time::Piece)

sudo cp helpers/feedgnuplot /usr/local/bin

fi


# copy cmd line for cli
#sudo cp cli/bdbc_s /usr/local/bin/
#sudo cp cli/bdbc /usr/local/bin/

# common
#sudo pip3 install SPARQLWrapper
sudo pip3 install urllib3
#sudo pip3 install wikipedia
sudo pip3 install HtmlParser
sudo pip3 install html2text
pip3 install langchain-community
pip3 install tiktoken
pip3 install docx2txt
pip3 install pypdf

###### installing bangdb libs now

USR_LIB_LOC=/usr/local/lib
USR_INC_LOC=/usr/local/include
USR_BIN_LOC=/usr/local/bin
#USR_LIB64=/usr/lib64
#USR_INC64=/usr/include

#if [ -d "/usr/lib64" ]
#then
#	USR_LIB64=/usr/lib64
#else
#	USR_LIB64=/usr/lib
#fi

sudo cp $PWD/libs/libbangdb-client-cpp.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client-cpp_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client-java.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-client_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-cpp.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-cpp_s.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd-java.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libbangdb-embd.so.2.0 $USR_LIB_LOC/
sudo cp $PWD/libs/libdlib.so $USR_LIB_LOC/
sudo cp $PWD/libs/libmitie.so $USR_LIB_LOC/
sudo cp $PWD/cli/bangdb-cli_s-2.0 $USR_BIN_LOC/
sudo cp $PWD/cli/bdbc $USR_BIN_LOC/


sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp.so.2.0 $USR_LIB_LOC/libbangdb-client-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp_s.so.2.0 $USR_LIB_LOC/libbangdb-client-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client-java.so.2.0 $USR_LIB_LOC/libbangdb-client-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client.so.2.0 $USR_LIB_LOC/libbangdb-client.so
sudo ln -sf $USR_LIB_LOC/libbangdb-client_s.so.2.0 $USR_LIB_LOC/libbangdb-client_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp.so.2.0 $USR_LIB_LOC/libbangdb-embd-cpp.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp_s.so.2.0 $USR_LIB_LOC/libbangdb-embd-cpp_s.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd-java.so.2.0 $USR_LIB_LOC/libbangdb-embd-java.so
sudo ln -sf $USR_LIB_LOC/libbangdb-embd.so.2.0 $USR_LIB_LOC/libbangdb-embd.so

sudo ln -sf $USR_BIN_LOC/bangdb-cli_s-2.0 $USR_BIN_LOC/bangdb-cli


#sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp.so.2.0 $USR_LIB64/libbangdb-client-cpp.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-client-cpp_s.so.2.0 $USR_LIB64/libbangdb-client-cpp_s.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-client-java.so.2.0 $USR_LIB64/libbangdb-client-java.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-client.so.2.0 $USR_LIB64/libbangdb-client.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-client_s.so.2.0 $USR_LIB64/libbangdb-client_s.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp.so.2.0 $USR_LIB64/libbangdb-embd-cpp.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-embd-cpp_s.so.2.0 $USR_LIB64/libbangdb-embd-cpp_s.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-embd-java.so.2.0 $USR_LIB64/libbangdb-embd-java.so
#sudo ln -sf $USR_LIB_LOC/libbangdb-embd.so.2.0 $USR_LIB64/libbangdb-embd.so

#sudo ln -sf $USR_LIB_LOC/libdlib.so $USR_LIB64/libdlib.so
#sudo ln -sf $USR_LIB_LOC/libmitie.so $USR_LIB64/libmitie.so

<<NO_JAVA
jv=$(echo $JAVA_HOME)
if [ -z "$jv" ]
then
	echo "JAVA_HOME is not set up, pls set it up. right now using hard link"
	#sudo ln -sf /lib/jvm/java-1.8.0/jre/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
	if [ -d "/lib/jvm" ]
	then
		if [ -d "/lib/jvm/jre-1.8.0" ]
		then
			sudo ln -sf /lib/jvm/jre-1.8.0/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
			sudo ln -sf /lib/jvm/jre-1.8.0/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
		else
			sudo ln -sf /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
			sudo ln -sf /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
		fi
	else
		sudo ln -sf /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
		sudo ln -sf /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
	fi
else
	sudo ln -sf $JAVA_HOME/jre/lib/amd64/server/libjvm.so $USR_LIB64/libjvm.so
	sudo ln -sf $JAVA_HOME/jre/lib/amd64/server/libjvm.so $USR_LIB_LOC/libjvm.so
fi
NO_JAVA

sudo ldconfig

echo "created env vars, soft links for the libs for bangdb"

sudo cp -r bangdb_udf $USR_INC_LOC/
sudo cp -r include/bangdb-embd $USR_INC_LOC/
sudo cp -r include/bangdb-client $USR_INC_LOC/

#sudo ln -sf $USR_INC_LOC/bangdb_udf $USR_INC64/bangdb_udf
#sudo ln -sf $USR_INC_LOC/bangdb-embd $USR_INC64/bangdb-embd
#sudo ln -sf $USR_INC_LOC/bangdb-client $USR_INC64/bangdb-client

echo "copied the include folders for bangdb"

#iv=$(whereis mvn)
#if [ -z "$v" ]
#then
#	echo "mvn is not installed"
	if [ $osv -eq 2 ]
	then
		sudo apt-get install -y maven
	else
		sudo yum -y install maven
	fi	
#fi

#mvn install:install-file -Dfile=jars/bangdb-client-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-client-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
#mvn install:install-file -Dfile=jars/bangdb-embd-java.jar -DgroupId=com.bangdb -DartifactId=bangdb-embd-java -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true
#mvn install:install-file -Dfile=jars/gson-2.6.2.jar -DgroupId=com.google -DartifactId=gson-2.6.2 -Dversion=2.6.2 -Dpackaging=jar -DgeneratePom=true
#mvn install:install-file -Dfile=jars/bangdb-reverb.jar -DgroupId=com.bangdb -DartifactId=bangdb-reverb -Dversion=2.0.0 -Dpackaging=jar -DgeneratePom=true

if [ $osv -eq 3 ]
then
	sudo yum -y install wget
	mkdir perl_module
	cd perl_module
	wget https://cpan.metacpan.org/authors/id/T/TO/TOBYINK/Exporter-Tiny-1.002002.tar.gz
	tar -xzvf Exporter-Tiny-1.002002.tar.gz
	cd Exporter-Tiny-1.002002
	perl Makefile.PL prefix=/usr/local
	make
	sudo make install
	cd ..
	
	wget https://cpan.metacpan.org/authors/id/T/TO/TODDR/IPC-Run-20200505.0.tar.gz
	tar -xzvf IPC-Run-20200505.0.tar.gz
	cd IPC-Run-20200505.0
	perl Makefile.PL prefix=/usr/local
	make
	sudo make install
	cd ..

	wget https://cpan.metacpan.org/authors/id/R/RE/REHSACK/List-MoreUtils-0.430.tar.gz
	tar -xzvf List-MoreUtils-0.430.tar.gz
	cd List-MoreUtils-0.430
	perl Makefile.PL prefix=/usr/local
	make
	sudo make install
	cd ..
	cd ..
fi
<<NO_SSL_3
opsv=$(openssl version -a | nawk '{print substr($2,1,1);exit}')
if [ "$opsv" = '3' ]; then
        echo "openssl 3 is already installed"
else
        echo "openssl installed version is $opsv"
        echo "installing openssl 3"

        if [ $osv -eq 2 ]; then
                sudo apt install -y build-essential checkinstall zlib1g-dev wget
                sudo apt remove -y openssl
        else
                sudo yum install -y gcc gcc-c++ kernel-devel make zlib-devel perl-IPC-Cmd perl-Pod-Html
                sudo yum remove -y openssl
        fi

        wget https://www.openssl.org/source/openssl-3.0.7.tar.gz
        tar -xzvf openssl-3.0.7.tar.gz
        cd openssl-3.0.7
        sudo apt install build-essential checkinstall zlib1g-dev -y
        sudo ./config --prefix=/usr/local --openssldir=/usr/local shared zlib
        sudo make
        #sudo make test
        sudo make install
        sudo touch /etc/ld.so.conf.d/openssl-3.0.7.conf

        echo "/usr/local/lib64" | sudo tee -a /etc/ld.so.conf.d/openssl-3.0.7.conf &> /dev/null
        sudo ldconfig -v
        echo "Cleaning up"
        cd .. && sudo rm -rf openssl-3.0.7/ && sudo rm openssl-3.0.7.tar.gz
fi
NO_SSL_3

echo "setting limits ..."
echo "* soft core unlimited" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "* hard core unlimited" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "* soft nproc 100000" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "* hard nproc 100000" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "* soft nofile 900000" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "root soft nofile 900000" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "* hard nofile 900000" | sudo tee -a /etc/security/limits.conf &> /dev/null
echo "root hard nofile 900000" | sudo tee -a /etc/security/limits.conf &> /dev/null

ulimit -n 900000
ulimit -Hn 900000


sudo sed -i 's/#\?\(Port\s*\).*$/\1 22/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(PermitRootLogin\s*\).*$/\1 yes/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(PasswordAuthentication\s*\).*$/\1 yes/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(TCPKeepAlive\s*\).*$/\1 no/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(ClientAliveInterval\s*\).*$/\1 30/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(ClientAliveCountMax\s*\).*$/\1 300/' /etc/ssh/sshd_config
sudo service sshd restart

echo "setting core path ..."
echo "/var/crash/core.%e.%p.%h.%t" | sudo tee /proc/sys/kernel/core_pattern &> /dev/null

BANGDB_CFG_FILE=etc/bangdb.config
if [ -f "bin/bangdb.config" ]; then
	BANGDB_CFG_FILE=bin/bangdb.config
fi
if [ $# -eq 1 ]; then
	dns=$1
	echo "setting dns in bangdb.config ..."
	echo "SERVER_PUBLIC_IP = $1" | tee -a $BANGDB_CFG_FILE &> /dev/null
	echo "MASTER_SERVER_ID = $1" | tee -a $BANGDB_CFG_FILE &> /dev/null
fi

echo "installing bdb agent"
wget https://github.com/sachin-sinha/BangDB/raw/master/agent/install_bdbagent.sh && bash install_bdbagent.sh && rm install_bdbagent.sh

echo "bangdb install done!"

#exec bash
