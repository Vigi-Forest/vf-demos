//
// Get IAQ + eCO2 from constant values (adapted from PicoAirQuality.py)
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libgen.h>

#include "libiaq.h"

struct self_struct self;

static void usage(char *s)
{
  printf ("Usage: %s -h <humidity> -g <gas-resistance> -t <temperature>\n", s);
  exit (1);
}

void main (int ac, char **av)
{
  char *cp, *progname = basename(av[0]);
  
  while (--ac) {
    if ((cp = *++av) == NULL)
      break;
    if (*cp == '-' && *++cp) {
      switch(*cp) {
      case 'h' :
	self.hRead = atof(*++av); break;

      case 'g' :
	self.gRes = atof(*++av); break;

      case 't' :
	self.tRead = atof(*++av); break;

      default: 
	usage(progname);
	break;
      }
    }
    else
      break;
  }

  if (self.hRead == 0 || self.gRes == 0 || self.tRead == 0)
    usage(progname);

  if (get_iaq_eco2 (&self) == 0) {
    printf ("IAQ = %g\n", self.iaqScore);
    printf ("eCO2 = %g ppm\n", self.eCO2Value);
  } else
    printf ("libIAQ error !\n");
}
