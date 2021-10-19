truncate -s 0 mon/car.txt
cp agent/agent.conf.bk agent/agent.conf
cd server
bash clean.sh
cd ..
