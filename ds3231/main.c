// Copyright 2021 Ocean (iiot2k@gmail.com) 
// All rights reserved.

#include <string.h>
#include <stdio.h>

#include "sys_fn.h"
#include "sys_time.h"
#include "sys_i2c.h"
#include "dev_ds3231.h"
#include "dev_hd44780.h"

#define PRINT_INTERVAL 100 // 100ms
#define LCD_ADDR 0x27
#define LCD_PORT i2c0
#define RTC_PORT i2c1

int main()
{
    int8_t buffer[30];
    int8_t buffer_time[30];
    int8_t buffer_date[30];

    // init buffer
    memset(buffer_time, 0, sizeof(buffer_time));
    memset(buffer_date, 0, sizeof(buffer_date));

    // Init system enviroment
    sys_init();

    // init i2c0 with default pins and 100kHz
    sys_i2c_init_def(LCD_PORT, 100000, true);

    // init i2c1 with default pins and 100kHz
    sys_i2c_init_def(RTC_PORT, 100000, true);

    // init hd4447780 (lcd)
    dev_hd44780_init(LCD_PORT, LCD_ADDR);
    
    datetime_t dt;

    // get date time from DS3231 
    if (!dev_ds3231_getdatetime(RTC_PORT, &dt))
        sys_outerr("Error on read DS3231");

    // check if date-time set
    if (dt.year == 2000)
    {
        // set datetime struct (set your actual date-time)
        dt.sec = 0;
        dt.min = 12;
        dt.hour = 14;
        dt.day = 5;
        dt.month = 6;
        dt.year = 2021;
        dt.dotw = sys_dayOfWeek(&dt);

        // set DS3231
        dev_ds3231_setdatetime(RTC_PORT, &dt);
    }

    // set Pico RTC from DS3231
    if (!dev_ds3231_setrtc(RTC_PORT))
        sys_outerr("Error on read DS3231 or not set");

    // turn led on for ok
    sys_ledon();

    uint64_t looptimer = 0; 

    // endless loop
    while(1)
    {
        // print RTC values on timeout
        if (sys_timeout_ms(&looptimer, PRINT_INTERVAL))
        {
            // get time
            sys_getrtc_format("%H:%M:%S", buffer, sizeof(buffer));

            // check if time changed
            if (strncmp(buffer_time, buffer, sizeof(buffer)) != 0)
            {
                // save time
                strncpy(buffer_time, buffer, sizeof(buffer_time));

                // send time to first line
                dev_hd44780_text(LCD_PORT, LCD_ADDR, 0, false, buffer); 
            }

            // get date
            sys_getrtc_format("%d.%m.%Y %a", buffer, sizeof(buffer));

            // check if date changed
            if (strncmp(buffer_date, buffer, sizeof(buffer)) != 0)
            {
                // adjust date/time RTC from DS3231 
                dev_ds3231_setrtc(i2c1);

                // save date
                strncpy(buffer_date, buffer, sizeof(buffer_date));
                
                // send date to second line
                dev_hd44780_text(LCD_PORT, LCD_ADDR, 1, false, buffer);
            }
        }

        // system loop
        sys_loop();
    }
}
