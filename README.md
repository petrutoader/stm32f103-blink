# Instructions
 1. git clone https://github.com/libopencm3/libopencm3-template.git stm32f103-blink 
 2. cd !$
 3. git submodule update --init # (Only needed once)
 4. pushd libopencm3 && make -C libopencm3 && popd
 5. make -C src


# To run with GDB

1. st-util
2. gdb src/stm32f103-blink.elf
3. - target extended-remote :4242
4. - load
5. - run

# To open the serial communication (using tio)

1. tio --baudrate 115200 --databits 8 --flow none --stopbits 1 --parity none /dev/tty.usbmodemXXXXX
