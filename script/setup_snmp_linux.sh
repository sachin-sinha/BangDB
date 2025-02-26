#!/bin/bash

# todo: check for 3 args

userid=$1
authpass=$2
privpass=$3

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


if [ $osv -eq 2 ]
then
	sudo apt-get install -y snmp snmpd libsnmp-dev
	sudo service snmpd stop
	sudo net-snmp-config --create-snmpv3-user -ro -A $authpass -X $privpass -a SHA -x AES $userid
	sudo systemctl restart snmpd
	sudo systemctl enable snmpd
	sudo service snmpd start
else
	sudo yum install -y net-snmp
	sudo yum install -y net-snmp-utils
	sudo service snmpd stop
	sudo net-snmp-create-v3-user -ro -A $authpass -X $privpass -a SHA -x AES $userid
	sudo systemctl restart snmpd.service
	sudo systemctl enable snmpd.service
	sudo service snmpd start 
fi

# todo: check for port 161 open - else open it, setup firewall
