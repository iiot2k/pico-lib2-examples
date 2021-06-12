add_executable(mcp4728 main.c)

target_link_libraries(mcp4728
    lib2_sys
    dev_mcp472x
)

# setup stdio 
pico_enable_stdio_usb(mcp4728 0)
pico_enable_stdio_uart(mcp4728 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(mcp4728)
