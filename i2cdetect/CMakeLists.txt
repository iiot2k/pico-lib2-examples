add_executable(busscan main.c)

target_link_libraries(busscan
    lib2_sys
)

# setup stdio 
pico_enable_stdio_usb(busscan 0)
pico_enable_stdio_uart(busscan 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(busscan)
