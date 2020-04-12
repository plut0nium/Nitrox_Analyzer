# ADS1115
> Arduino library for TI ADS1115 16-bit ADC

## Description

Inspired by Adafruit_ADS1X15, this library is specificaly written for the 16-bit version ADS1115.
It allows to easily use the chip in continuous conversion mode, as well as helper functions to set MUX, GAIN and sampling rate.

## Usage

```C++
#include <ADS1115.h>

(...)

ADS1115 ads;

(...)

void setup()
{
    (...) // include Serial initialization if needed

	ads.begin();
	ads.setGain(GAIN_SIXTEEN); // +/- 256mV FSR = 7.812µV resolution
	ads.setDataRate(DR_16SPS); // 16 sps
	ads.setMux(MUX_DIFF_0_1);  // sensor is connected between AIN0 (P) and AIN1 (N)
	ads.writeConfig();
#ifdef DEBUG
	Serial.print("ADS config: "); Serial.println(ads.readConfig());
#endif
	ads.startContinuousConversion();

    (...)
}
```

In your main loop, you can now read the ADC measurements at regular interval:
```C++
int16_t measurement = ads.readLastConversion()
```

## License

Copyright (c) 2020, Charles Fourneau

Copyright (c) 2012, Adafruit Industries

BSD License. See `LICENSE` for more information.

## Credits

- https://github.com/adafruit/Adafruit_ADS1X15