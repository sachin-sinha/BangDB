#!/bin/bash
usr=bangdb
pawd=bangdbmanu7
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


if [ $osv -eq 2 ]
then

        sudo apt update
	sudo apt-get install -y libssl-dev

	sudo useradd -s /bin/bash -m -p $(openssl passwd -1 $pawd) $usr
	groups $usr
	sudo usermod -aG sudo $usr
fi

if [ $osv -eq 1 ] || [ $osv -eq 3 ]
then

        sudo yum update
	sudo yum install -y openssl

	sudo useradd -s /bin/bash -m -p $(openssl passwd -1 $pawd) $usr
	groups $usr
	sudo usermod -aG wheel $usr
fi

echo 'bangdb ALL=(ALL) NOPASSWD: ALL' | sudo tee -a /etc/sudoers &> /dev/null
sudo sed -i 's/#\?\(Port\s*\).*$/\1 22/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(PermitRootLogin\s*\).*$/\1 yes/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(PasswordAuthentication\s*\).*$/\1 yes/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(TCPKeepAlive\s*\).*$/\1 no/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(ClientAliveInterval\s*\).*$/\1 30/' /etc/ssh/sshd_config
sudo sed -i 's/#\?\(ClientAliveCountMax\s*\).*$/\1 300/' /etc/ssh/sshd_config
sudo sed -i '/^Include \/etc\/ssh\/sshd_config.d\/\*.conf/ s/./#&/' /etc/ssh/sshd_config
sudo service sshd restart
