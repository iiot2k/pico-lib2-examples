add_executable(ds3231 main.c)

target_link_libraries(ds3231
    lib2_sys
    dev_ds3231
    dev_hd44780
)

# setup stdio 
pico_enable_stdio_usb(ds3231 0)
pico_enable_stdio_uart(ds3231 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(ds3231)
