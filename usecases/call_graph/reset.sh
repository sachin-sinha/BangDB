truncate -s 0 mon/log_calls.csv
cp agent/agent.conf.bk agent/agent.conf
cd server
bash clean.sh
cd ..
