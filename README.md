# stm32f103-blink

Inspired from Arduino's Blink, this time for a STM32F103 MCU!

## Installing ARM GNU Toolchain on Mac

If you don't already have the ARM GNU Toolchain, then you can install it via `brew`.

```
$ brew tap osx-cross/arm
$ brew install arm-gcc-bin
```

## Cloning and compiling libopencm3

```$ git clone https://github.com/libopencm3/libopencm3-template.git stm32f103-blink
$ cd !$
$ git submodule update --init # (Only needed once)
$ pushd libopencm3 && make && popd
```

## Compiling the software

`$ make -C src`

# To run with GDB (ARM GNU GDB)

```$ st-util
$ arm-none-eabi-gdb src/stm32f103-blink.elf
$ > target extended-remote :4242
$ > load
$ > run
```
# To open the serial communication (using tio)

`$ tio --baudrate 115200 --databits 8 --flow none --stopbits 1 --parity none /dev/tty.usbmodemXXXXX`
