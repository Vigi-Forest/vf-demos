//
// IAQ + eCO2 library (adapted from PicoAirQuality.py)
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libgen.h>

#include "libiaq.h"

int get_iaq_eco2 (struct self_struct *self)
{
  double humidityScore, gasScore, humidityOffset, ambTemp, temperatureOffset, humidityRatio, temperatureRatio, gasRatio;
  int i;

  if (self->hRead == 0 || self->gRes == 0 || self->tRead == 0)
    return -1;
  
  /*
    # A baseline gas resistance is required for the IAQ calculation - it should be taken in a well ventilated area without obvious air pollutants
    # Take 60 readings over a ~5min period and find the mean
    # Establish the baseline gas resistance reading and the ambient temperature.
    # These values are required for air quality calculations
    # When the baseline process is complete, values for gBase and tAmbient are stored in a file (baselines.txt)
    # On subsequent power cycles of the board, this function will look for that file and take the baseline values stored there
  */

  // FIXME: constant values right now
  // GSR base
  self->gBase = GBASE;

  // Ambient temperature
  self->tAmbient = AMBIENT_T;

  //
  // Calculation
  //

  //  Humidity contributes 25% to the IAQ score, gas resistance is 75%
  self->hWeight = 0.25;

  // Between 30% & 50% is a widely recognised optimal indoor humidity, 40% is a good middle ground
  self->hBase = 40;       

  humidityScore = 0;
  gasScore = 0;
  // Calculate the humidity offset from the baseline setting
  humidityOffset = self->hRead - self->hBase;  
  ambTemp = self->tAmbient;

  // Calculate the temperature offset from the ambient temperature
  temperatureOffset = self->tRead - ambTemp; 
  humidityRatio = ((humidityOffset / self->hBase) + 1);
  temperatureRatio = (temperatureOffset / ambTemp);

  // IAQ Calculations
  if (humidityOffset > 0)
    humidityScore = (100 - self->hRead) / (100 - self->hBase);
  else
    humidityScore = self->hRead / self->hBase;

  // 25% for humidity
  humidityScore = humidityScore * self->hWeight * 100;
  gasRatio = (self->gRes / self->gBase);

  if ((self->gBase - self->gRes) > 0) 
    gasScore = gasRatio * (100 * (1 - self->hWeight));
  else {
    gasScore = floor(70 + (5 * (gasRatio - 1)));
    if (gasScore > 75)
      gasScore = 75;
  }

  // IAQ
 
  // Air quality percentage is the sum of the humidity (25% weighting)
  // and gas (75% weighting) scores
  self->iaqPercent = trunc(humidityScore + gasScore);
  // Air quality percentage is the sum of the humidity (25% weighting)
  // and gas (75% weighting) scores
  //
  // Final air quality score is in range 0 - 500 (see BME688 datasheet page 11 for details)
  self->iaqScore = (100 - self->iaqPercent) * 5; 

  // eCO2 Calculations

  //  Exponential curve equation to calculate the eCO2 from an iaqScore input
  self->eCO2Value = 250 * exp(0.012 * self->iaqScore);

  // Adjust eCO2Value for humidity and/or temperature greater than the baseline values
  if (humidityOffset > 0) {
    if (temperatureOffset > 0)
      self->eCO2Value = self->eCO2Value * (humidityRatio + temperatureRatio);
    else
      self->eCO2Value = self->eCO2Value * humidityRatio;
  }
  else if (temperatureOffset > 0)
    self->eCO2Value = self->eCO2Value * (temperatureRatio + 1);

  self->eCO2Value = trunc(self->eCO2Value);

  // TBD
  // If measurements are taking place rapidly, breath detection is possible due to the sudden increase in humidity (~7-10%)
  // If this increase happens within a 5s time window, 1200ppm is added to the eCO2 value
  // (These values were based on 'breath-testing' with another eCO2 sensor with algorithms built-in)
  //  if ((self->measTime - self->measTimePrev) <= 5000):
  //      if ((self->hRead - self->hPrev) >= 3):
  //          self->eCO2Value = self->eCO2Value + 1500
  //

  return 0; // OK
}
