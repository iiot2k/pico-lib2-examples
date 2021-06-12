// Copyright 2021 Ocean (iiot2k@gmail.com) 
// All rights reserved.

#include <string.h>

#include "sys_fn.h"
#include "sys_util.h"
#include "sys_i2c.h"
#include "sys_time.h"
#include "dev_ads1115.h"

#define PRINT_INTERVAL 2000 // 2s

int main()
{
    int8_t buffer[30];

    // Init system enviroment
    sys_init();

    // init i2c0 with default pins and 100kHz
    sys_i2c_init_def(i2c0, 100000, true);

    // turn led on for ok
    sys_ledon();
    
    uint64_t looptimer = 0; 

    // endless loop
    while(1)
    {
        // print adc values on timeout
        if (sys_timeout_ms(&looptimer, PRINT_INTERVAL))
        {
            double value;

            // read adc channel 0
            if (!dev_ads1115_read(i2c0, ADS1115_ADDR0, ADS1115_CH0, ADS1115_GAIN_2048, &value))
                sys_outerr("Error on read ADS1115");

            // print value
            sys_logmsg2("CH0:", sys_dbl_str(value, 3, buffer, sizeof(buffer))); 

            // read adc channel 1
            dev_ads1115_read(i2c0, ADS1115_ADDR0, ADS1115_CH1, ADS1115_GAIN_1024, &value);

            // print value
            sys_logmsg2("CH1:", sys_dbl_str(value, 3, buffer, sizeof(buffer))); 

            // read adc channel 2
            dev_ads1115_read(i2c0, ADS1115_ADDR0, ADS1115_CH2, ADS1115_GAIN_2048, &value);

            // print value
            sys_logmsg2("CH2:", sys_dbl_str(value, 3, buffer, sizeof(buffer))); 

            // read adc channel 3
            dev_ads1115_read(i2c0, ADS1115_ADDR0, ADS1115_CH3, ADS1115_GAIN_4096, &value);

            // print value
            sys_logmsg2("CH3:", sys_dbl_str(value, 3, buffer, sizeof(buffer))); 
        }

        // system loop
        sys_loop();
    }
}
