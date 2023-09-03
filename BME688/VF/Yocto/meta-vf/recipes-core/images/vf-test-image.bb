# Base this image on core-image-minimal
include recipes-core/images/core-image-base.bb

IMAGE_INSTALL += "i2c-tools wiringpi kernel-module-i2c-dev kernel-module-i2c-bcm2708 curl ntpdate mosquitto-clients haveged"
IMAGE_INSTALL += "bme688  bme680-python"

DISTRO_FEATURES_append = " wifi"
