# Waveshare PoE HAT CLI
Small command line interface for Waveshare PoE HAT B with OLED Display

![](doc/PoE-HAT-B-details-5.png)

## Features

 - Small
 - Control OLED (1 line, 2 lines, 3 lines and 4 lines)
 - Control FAN

## Examples

```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli fan on
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli fan off
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1"
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2"
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2" "row3"
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2" "row3" "row4"
```

## Enable I2C Interface

I2C interface is required for the OLED display, you need to first enable the i2c interface for properly work.
Open a terminal of Raspberry Pi and configure:

```shell
foo@bar:~$ sudo raspi-config
Interfacing Options -> I2C -> Yes
```

![](doc/enable-i2c.png)

And then reboot the system.

```shell
foo@bar:~$ sudo reboot
```

## Compile

```shell
foo@bar:~$ cd src
foo@bar:~$ ./make clean
foo@bar:~$ ./make
```
 
## References

Documentation (https://www.waveshare.com/wiki/PoE_HAT_(B))[https://www.waveshare.com/wiki/PoE_HAT_(B)]
