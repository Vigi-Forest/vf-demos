#
# BME688 utilities
#
DESCRIPTION = "BME688 utilies"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=8ca43cbc842c2336e835926c2166c28b"

INSANE_SKIP_${PN} += "ldflags"

SRC_URI = "http://pficheux.free.fr/pub/tmp/bme688-1.0.tar.gz file://init file://get_value.sh"

DEPENDS += "python3 wiringpi"

inherit update-rc.d

INITSCRIPT_NAME = "bme688"
INITSCRIPT_PARAMS = "defaults 99"

do_install() {
        oe_runmake install DESTDIR=${D}
	install -m 0755 ${WORKDIR}/get_value.sh ${D}${bindir}
        install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/init ${D}${sysconfdir}/init.d/bme688
}

SRC_URI[md5sum] = "9ce23abda63449079c8850b9c65b2cab"

