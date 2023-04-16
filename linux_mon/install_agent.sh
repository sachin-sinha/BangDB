#!/bin/bash
## find os type
        ip=$1
        port=$2
	echo "ip = $ip, port = $port"
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
fi

name=bangdb-agent-ssl
binary="./${name}"
ubuntu16=https://github.com/sachin-sinha/BangDB/raw/master/linux_mon/all/bangdb-agent-ubuntu16.tar.gz
ubuntu18=https://github.com/sachin-sinha/BangDB/raw/master/linux_mon/all/bangdb-agent-ubuntu18.tar.gz

# install key and certificate
ssl_configure() {
	openssl req -nodes -newkey rsa:2048 -keyout example.key -out example.csr -subj "/C=IN/ST=Bangalore/L=Bangalore/O=Global Security/OU=BangDB/CN=bangdb.com"
	openssl x509 -req -in example.csr -signkey example.key -out example.crt
	openssl rsa -in example.key -text > key.pem
	openssl x509 -inform PEM -in example.crt > cert.pem
	mkdir bin/certificate
	mv key.pem cert.pem bin/certificate	
	# cleanup
	rm example.crt example.csr example.key
}

configure_ip_port() {
	sed -i -e "s/\(\"server_ip\":\).*/\1\"$ip\",/" \
	-e "s/\(\"server_port\":\).*/\1\"$port\",/"  bin/linux_agent.conf
}

#get the agent now
v=$(awk -F= '/^VERSION_ID/{print $2;exit}' /etc/os-release)

if [ $osv -eq 2 ]
then
	if [ $v = '"16.04"' ]; then
		echo "installing for ubuntu 16 ..."
		wget --no-check-certificate $ubuntu16
		tar -xzvf bangdb-agent-ubuntu16.tar.gz
		cd bangdb-agent-ubuntu16
		ssl_configure
		configure_ip_port
		${binary} start
	fi
	if [ $v = '"18.04"' ]; then
		echo "installing for ubuntu 18 ..."
		wget --no-check-certificate $ubuntu18
		tar -xzvf bangdb-agent-ubuntu18.tar.gz
		cd bangdb-agent-ubuntu18
		ssl_configure
		configure_ip_port
		${binary} start
	fi
fi
echo "bangdb-agent install done!"
