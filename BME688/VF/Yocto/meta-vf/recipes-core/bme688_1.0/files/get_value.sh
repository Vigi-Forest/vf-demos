#!/bin/sh

SERVER=test.mosquitto.org
TOPIC=vigi-forest-pf

while [ 1 ]
do
    B=$(bme688)
    T=$(echo $B | cut -d " " -f4)
    CO2=$(echo $B | cut -d " " -f18)
    mosquitto_pub -h $SERVER -t $TOPIC -m "{\"time\":\"$(date +"%x %X")\", \"temp\":\"$T\", \"CO2\":\"$CO2\"}"
    sleep 5
done
