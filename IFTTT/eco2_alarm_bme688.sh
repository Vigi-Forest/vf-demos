#!/bin/sh
#set -x

# IFTTT parameters
KEY=nyGTOHaJMnkXJhgIVHrxPaL6CFuCDgLMhcSAbBc7ozr
EVENT=gmail


SLEEP_T=5
DATE_ALARM=0
DATE_C=0
SEND_DELAY=60
PPM_O=0
PPM_MAX=500


# Sensor ID
SENSOR_ID=$(hostname)

while [ 1 ]
do
    # Get values
    TEMP=$(bme688 | cut -d " " -f4)
    GSR=$(bme688 | cut -d " " -f13)
    IAQ=$(bme688 | cut -d " " -f16)
    PPM=$(bme688 | cut -d " " -f18)
    echo "$TEMP C $GSR kOhms IAQ $IAQ $PPM ppm"

    # 4 digits for the eCO2
    M=$(($PPM/1000))
    R=$(($PPM%1000))
    C=$(($R/100))
    R=$(($R%100))
    D=$(($R/10))
    U=$(($R%10))
    i2cset -y 2 0x71 0x76 $M $C $D $U i

    # Check for alarm
    PPM_O=$PPM
    DATE_C=$(date +%s)

    if [ $PPM -gt $PPM_MAX ]; then
	D=$(expr $DATE_C - $DATE_ALARM)
	echo "Delay since last alarm is $D / $SEND_DELAY"
	# Send an alarm if delay > (alarm time - current time)
	if [ $D -gt $SEND_DELAY ]; then
  	    echo "*** Sending ALARM ($PPM / $PPM_O ppm) !!!"
	    DATE_ALARM=$(date +%s)
	    curl -k -X POST -H "Content-Type: application/json" -d '{"value1":"sensor_id = '$SENSOR_ID'", "value2":"eCO2 = '$PPM' ppm"}' https://maker.ifttt.com/trigger/$EVENT/with/key/$KEY
	else
	    echo "alarm already sent !"
	fi
    else
	echo "OK :-) ($PPM / $PPM_O ppm)"
    fi 

    sleep $SLEEP_T
done

    

