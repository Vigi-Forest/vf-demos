#!/bin/bash
#
# Send an IFTTT event
#
#set -x

# Get location
SENSOR_ID=$(curl -s https://ipinfo.io/$(curl -s https://ipinfo.io/ip) | jq '.city' | tr -d '"')

which bme688

if [ $? -ne 0 ]; then
    # Random value between 100 and 1000
    S=$(echo "$RANDOM / 32768" | bc -l)
    PPM=$(LC_NUMERIC=C printf '%.0f\n' $(echo "100 + $S * (1000-100)" | bc -l))
else
    PPM=$(bme688 | cut -d " " -f18)
fi    

# IFTTT parameters
KEY=nyGTOHaJMnkXJhgIVHrxPaL6CFuCDgLMhcSAbBc7ozr
EVENT=gmail

curl -k -X POST -H "Content-Type: application/json" -d '{"value1":"sensor_id = '$SENSOR_ID'", "value2":"CO2 = '$PPM' ppm"}' https://maker.ifttt.com/trigger/$EVENT/with/key/$KEY
