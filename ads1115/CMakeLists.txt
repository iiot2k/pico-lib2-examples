add_executable(ads1115 main.c)

target_link_libraries(ads1115
    lib2_sys
    dev_ads1x15
)

# setup stdio 
pico_enable_stdio_usb(ads1115 0)
pico_enable_stdio_uart(ads1115 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(ads1115)
