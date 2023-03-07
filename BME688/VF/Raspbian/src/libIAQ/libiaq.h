#ifndef _iaq_eco2_h
#define _iaq_eco2_h

// FIXME: constant values right now

// "baseline gas resistance" to be read from baselines.txt
#define GBASE     13478.33; 

// Ambient temperature to be read from baselines.txt
#define AMBIENT_T  24.74;

struct self_struct {
  double hRead;
  double hBase;
  double gBase;
  double tAmbient;
  double tRead;
  double hWeight;
  double gRes;
  double iaqPercent;
  double iaqScore;
  double eCO2Value;
};

int get_iaq_eco2 (struct self_struct *);

#endif /* _iaq_eco2_h */
