#!/bin/sh
#set -x

BOOT="7c 5c 5c 78"
INIT="06 54 04 78"
FIRE="71 10 50 79"

i2c_display()
{
	set $1
	i2cset -y 2 0x71 0x76 0x7b 0x$1 0x7c 0x$2 0x7d 0x$3 0x7e 0x$4 i
}

i2c_display "$BOOT"
sleep 2
i2c_display "$INIT"
sleep 2
i2c_display "$FIRE"
