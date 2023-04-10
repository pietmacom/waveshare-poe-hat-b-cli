# Waveshare PoE HAT CLI
Small command line interface for Waveshare PoE HAT B with OLED Display. 

Do whatever you like in shell (no need to recompile).

![](doc/PoE-HAT-B-details-5.png)

## Features

 - Do whatever you like in shell (no need to recompile)
   - Control FAN
   - Control OLED (1 line, 2 lines, 3 lines and 4 lines)
 - Small binary

## Examples

Control FAN
```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli fan on
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli fan off
```

```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1"
```

![](doc/example-1rows.png)

```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2"
```

![](doc/example-2rows.png)

```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2" "row3"
```

![](doc/example-3rows.png)

```shell
foo@bar:~$ sudo ./waveshare-poe-hat-b-cli oled "row1" "row2" "row3" "row4"
```

![](doc/example-4rows.png)

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
