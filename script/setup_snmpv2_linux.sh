#!/bin/bash



sudo apt-get install snmpd
sudo mv /etc/snmp/snmpd.conf /etc/snmp/snmpd.conf.org
sudo touch /etc/snmp/snmpd.conf
sudo sh -c "echo 'rocommunity bangdb' > /etc/snmp/snmpd.conf"
sudo sh -c "echo 'includeAllDisks 10% for all partitions and disks' > /etc/snmp/snmpd.conf"
sudo sed -e '/SNMPDOPTS/ s/^#*/#/' -i /etc/default/snmpd
sudo sed -i "/#SNMPDOPTS/a SNMPDOPTS='-Lsd -Lf /dev/null -u snmp -I -smux -p /var/run/snmpd.pid -c /etc/snmp/snmpd.conf'" /etc/default/snmpd
sudo service snmpd restart

