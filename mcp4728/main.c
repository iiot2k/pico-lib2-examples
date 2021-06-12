// Copyright 2021 Ocean (iiot2k@gmail.com) 
// All rights reserved.

#include "sys_fn.h"
#include "sys_i2c.h"
#include "sys_time.h"
#include "dev_mcp4728.h"

#define UPDATE_INTERVAL 100 // 100ms

int main()
{
    // Init system enviroment
    sys_init();

    // init i2c0 with default pins and 100kHz
    sys_i2c_init_def(i2c0, 100000, true);

    uint64_t looptimer = 0; 
    uint16_t dacval = 0;

    // turn led on for ok
    sys_ledon();

    // endless loop
    while(1)
    {
        if (sys_timeout_ms(&looptimer, UPDATE_INTERVAL))
        {
            // set dac output
            if (!dev_mcp4728_set(i2c0, MCP4728_CHA, dacval))
                sys_outerr("Error on set MCP4728");
            
            dacval += 10;

            if (dacval > 4095)
                dacval = 0;
        }

        // system loop
        sys_loop();
    }
}
