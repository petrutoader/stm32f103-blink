# Instructions
```$ git clone https://github.com/libopencm3/libopencm3-template.git stm32f103-blink
$ cd !$
$ git submodule update --init # (Only needed once)
$ pushd libopencm3 && make && popd
$ make -C src
```
# To run with GDB

```$ st-util
$ gdb src/stm32f103-blink.elf
$ > target extended-remote :4242
$ > load
$ > run
```
# To open the serial communication (using tio)

`$ tio --baudrate 115200 --databits 8 --flow none --stopbits 1 --parity none /dev/tty.usbmodemXXXXX`
