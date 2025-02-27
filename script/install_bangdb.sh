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

alias brc='source ~/.bashrc'

ubuntu18=bangdb_2.0_ubuntu18
ubuntu20=bangdb_2.0_ubuntu20
ubuntu22=bangdb_2.0_ubuntu22
ubuntu23=bangdb_2.0_ubuntu23
ubuntu24=bangdb_2.0_ubuntu24
rhel9=bangdb_2.0_rhel9
rhel8=bangdb_2.0_rhel8
rhel7=bangdb_2.0_rhel7
centos9=bangdb_2.0_centos9
centos8=bangdb_2.0_centos8
centos7=bangdb_2.0_centos7



# install key and certificate
ssl_configure() {
	openssl req -nodes -newkey rsa:2048 -keyout example.key -out example.csr -subj "/C=IN/ST=Bangalore/L=Bangalore/O=Global Security/OU=BangDB/CN=bangdb.com"
	openssl x509 -req -in example.csr -signkey example.key -out example.crt
	openssl rsa -in example.key -text > key.pem
	openssl x509 -inform PEM -in example.crt > cert.pem
	cat cert.pem key.pem example.crt > bundle.pem
	mv example.crt myca.crt
	mkdir certificate
	mv key.pem cert.pem myca.crt bundle.pem certificate
	mv certificate bin	
	# cleanup
	rm example.crt example.csr example.key
}

#get the bangdb now
v=$(awk -F= '/^VERSION_ID/{print $2;exit}' /etc/os-release)

if [ $osv -eq 2 ]
then
	if [ $v = '"18.04"' ]; then
		echo "installing for ubuntu 18 ..."
		binary=$ubuntu18
	fi
	if [ $v = '"20.04"' ]; then
		echo "installing for ubuntu 20 ..."
		binary=$ubuntu20
	fi
	if [ $v = '"22.04"' ]; then
		binary=$ubuntu22
	fi
	if [ $v = '"23.10"' ]; then
		binary=$ubuntu23
	fi
	if [ $v = '"24.04"' ]; then
  		binary=$ubuntu24
        fi
fi
if [ $osv -eq 3 ]
then
	if [ $v = '"9.3"' ] || [ $v = '"9.2"' ] || [ $v = '"9.1"' ] || [ $v = '"9.0"' ] || [ $v = '"9"' ]; then
		echo "installing for rhel 9 ..."
		binary=$rhel9
	fi
	if [ $v = '"8.9"' ] || [ $v = '"8.8"' ] || [ $v = '"8.7"' ] || [ $v = '"8.6"' ] || [ $v = '"8.5"' ] || [ $v = '"8.4"' ] || [ $v = '"8.3"' ] || [ $v = '"8.2"' ] || [ $v = '"8.1"' ] || [ $v = '"8.0"' ] || [ $v = '"8"' ]; then
		binary=$rhel8
	fi
	if [ $v = '"7.9"' ] || [ $v = '"7.8"' ] || [ $v = '"7.7"' ] || [ $v = '"7.6"' ] || [ $v = '"7.5"' ] || [ $v = '"7.4"' ] || [ $v = '"7.3"' ] || [ $v = '"7.2"' ] || [ $v = '"7.1"' ] || [ $v = '"7.0"' ] || [ $v = '"7"' ]; then
		binary=$rhel7
	fi
fi
if [ $osv -eq 3 ]
then
	if [ $v = '"9"' ]; then
		binary=$centos9
	fi
	if [ $v = '"8"' ]; then
		binary=$centos8
	fi
	if [ $v = '"7"' ]; then
		binary=$centos7
	fi
fi

i=0
validate_password() {
    local password
    read -sp "Enter the password (min 8 chars) for user 'bangdb': " password
    echo
    if [[ ${#password} -lt 8 ]]; then
        echo "❌ Password must be at least 8 characters long."
        i=`expr $i + 1`
        if [ $i -eq 4 ]; then
                echo "Too many wrong inputs. Exiting .. try again"
                exit
        fi
        validate_password  # Recursive call until valid input
    else
        pawd=$password
        echo "✅ Password accepted."
    fi
}


i=0
# Function to validate either a domain name or an IP address
validate_domain_ip() {
    local input
    read -p "Enter a domain name or IPv4 address: " input

    # Regular expressions for validation
    local domain_regex="^([a-zA-Z0-9.-]+\.[a-zA-Z]{2,})$"
    local ip_regex="^([0-9]{1,3}\.){3}[0-9]{1,3}$"

    if [[ $input =~ $ip_regex ]]; then
        # Check if each octet in the IP is in range (0-255)
        IFS='.' read -r -a octets <<< "$input"
        for octet in "${octets[@]}"; do
            if ((octet < 0 || octet > 255)); then
                i=`expr $i + 1`
                if [ $i -eq 4 ]; then
                        echo "Too many wrong inputs. Exiting .. try again"
                        exit
                fi

                echo "❌ Invalid IP: Each octet must be between 0 and 255."
                validate_domain_ip  # Retry
                return
            fi
        done
        echo "✅ Valid IPv4 address: $input"

    elif [[ $input =~ $domain_regex ]]; then
        echo "✅ Valid domain name: $input"

    else
        i=`expr $i + 1`
        if [ $i -eq 4 ]; then
                echo "Too many wrong inputs. Exiting .. try again"
                exit
        fi

        echo "❌ Invalid input. Please enter a valid domain or IPv4 address."
        validate_domain_ip  # Retry
    fi
}


validate_password
validate_domain_ip

create_user() {
	sudo apt update
	usr=bangdb
	sudo useradd -s /bin/bash -m -p $(openssl passwd -1 $pawd) $usr
	groups $usr
	if [ $osv -eq 2 ]; then
	        sudo apt update
        	sudo apt-get install -y libssl-dev
        	sudo useradd -s /bin/bash -m -p $(openssl passwd -1 $pawd) $usr
        	groups $usr
        	sudo usermod -aG sudo $usr
	else
		sudo yum update
	        sudo yum install -y openssl
	        sudo useradd -s /bin/bash -m -p $(openssl passwd -1 $pawd) $usr
        	groups $usr
        	sudo usermod -aG wheel $usr
	fi
	echo 'bangdb ALL=(ALL:ALL) ALL' | sudo tee -a /etc/sudoers &> /dev/null
	sudo sed -i 's/#\?\(Port\s*\).*$/\1 22/' /etc/ssh/sshd_config
	sudo sed -i 's/#\?\(PermitRootLogin\s*\).*$/\1 yes/' /etc/ssh/sshd_config
	sudo sed -i 's/#\?\(PasswordAuthentication\s*\).*$/\1 yes/' /etc/ssh/sshd_config
	sudo sed -i 's/#\?\(TCPKeepAlive\s*\).*$/\1 no/' /etc/ssh/sshd_config
	sudo sed -i 's/#\?\(ClientAliveInterval\s*\).*$/\1 30/' /etc/ssh/sshd_config
	sudo sed -i 's/#\?\(ClientAliveCountMax\s*\).*$/\1 300/' /etc/ssh/sshd_config
	sudo sed -i '/^Include \/etc\/ssh\/sshd_config.d\/\*.conf/ s/./#&/' /etc/ssh/sshd_config
	sudo service sshd restart
}

#create user bangdb
create_user

#now install bangdb finally
presentdir=source pwd
cd /opt
sudo wget https://bangdb.com/downloads/$binary.tar.gz
sudo tar -xzvf $binary.tar.gz
sudo chown -R bangdb:bangdb /opt/$binary
cd $binary 
bash install.sh $DNS
sudo chown -R bangdb:bangdb /opt/$binary
ulimit -n 900000
ulimit -Hn 900000
ulimit -c unlimited
#ulimit -a
#sudo -Hu bangdb ./bangdb-server-ssl start
pwd $presentdir
echo "bangdb-agent install done! ✅ "
