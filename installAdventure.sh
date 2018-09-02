#!/usr/bin/env bash

make adventure

chmod +x removeAdventure.sh

sudo cp adventure removeAdventure.sh /usr/local/bin

cd ../

rm -rf /adventure
