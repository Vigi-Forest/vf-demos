# The "Vigi-Fire"  project

## Description

### Context

The evolution of the climate leads us to be very attentive to the preservation of our natural heritage. During the
summer 2022, there was an explosion of the number of fires all around the world, including Europe and France. The south west
of France is very famous for the "forêt de Landes" (The Landes Forest) wich is considered as one of the biggest in Europe.

The forest is shared between the departements of Gironde, Landes and Lot-et-Garonne (Nouvelle Aquitaine). The area is about 1000000 ha. In july and August 2022, 3 major fires in Gironde destroyed more than 30000 ha in La Teste-de-Buch, Landiras and Saint-Magne. In september, a new fire in the "Médoc" destroyed about 3500 ha.

### Goal

The the goal of the project is to develop and install a connected system in order to detect a "start of fire" in a forest and send an alarm to the local fire department. In a final version, a dashboard will be provided in order to check the data during a period of time.

Here are the prerequistes:

- Using cheap hardware such as common microcontrollers based boards (ESP32, RP2040) with low power consumption. A solution based on a 8 bits MCU (STM8) is also possible.
- Using a LPWAN network to send the data (LoRA, Sigfox, NB-IOT, LTE-M). A solution based on 169 Mhz modulation is also considered.
- Open source software (and hardware) !

## Current status

The current repository includes some demonstrations on Raspberry Pi :

- ```MPL115A2``` MQTT demo using a MPL115A2 sensor and sending the temperature to "test.mosquitto.org" using the "view-forest" topic (Yocto based)
- ```BME688``` demo using a BME688 sensor and reading  some values (temperature, pressure, hygrometry, gas resistance -> IAQ + eCO2)
- ```IFTTT``` Uses the IFTTT to send a alarm using a "webhook" if the temperature is greater than TMAX
- ```Tago``` is a short demo of the TagoIO service (MQTT) with a simple dashboard

