#!/bin/bash

DNS=$1


curl -sL https://deb.nodesource.com/setup_20.x -o /tmp/nodesource_setup.sh
sudo bash /tmp/nodesource_setup.sh
sudo apt install nodejs

node -v
sudo node -v

curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add -
echo "deb https://dl.yarnpkg.com/debian/ stable main" | sudo tee /etc/apt/sources.list.d/yarn.list
sudo apt update
sudo apt install -y yarn
sudo apt install --no-install-recommends yarn

yarn --version
source ~/.profile

cat .env | sed -e "s/<DNS>/$DNS/" > .env2 && mv .env2 .env
