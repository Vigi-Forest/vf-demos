# Yocto 3.1 SDK
PYTHON = python3.8

PYTHON_DIR = $(SDKTARGETSYSROOT)/usr/include/$(PYTHON)

BME68X_DIR= BME68x-Sensor-API
LIBIAQ_DIR= libIAQ

#CFLAGS= -Wall -Wno-unused-but-set-variable -Wno-unused-variable -std=c99 -pedantic -O2 -I$(PYTHON_DIR) -DPF
CFLAGS= -O2 -I=$(PYTHON_DIR) -I$(LIBIAQ_DIR) -DPF

SRCS= $(BME68X_DIR)/bme68x.c bme688.c $(LIBIAQ_DIR)/iaq_eco2.c $(LIBIAQ_DIR)/libiaq.h

PROGS= bme688

$(PROGS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)  -lm -lwiringPi -l$(PYTHON) -o $@

install:
	mkdir -p $(DESTDIR)/usr/bin
	cp $(PROGS) $(DESTDIR)/usr/bin

clean: 
	rm -f *~ $(PROGS)
