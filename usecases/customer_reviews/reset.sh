truncate -s 0 mon/prod.txt mon/order.txt mon/reviews.txt
cp agent/agent.conf.bk agent/agent.conf
cd server
bash clean.sh
cd ..
