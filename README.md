# Biomechatronics-MCU

K64F program for the Biomechatronics course.

## How to use

 * Connect the board. The blue LED will start to blink, indicating it's waiting for user input.
    * Press the left button (marked "SW2") to set the board in IMU mode. A constant pink-ish LED will show.
    * Alternatively, press the right button (marked "SW3") to set the board in EMG mode. A constant yellow-ish LED will show.
 * To switch mode, reset the board (with the button marked "RESET") and select the desired mode.

Note: you will need to hold the buttons down for a fraction of a second.

Connect the second USB port (marked "K64 USB") to your computer to get started.  
If no USB is connected, the program will wait after the mode selection, showing a constant green LED. Continue by connecting the USB.

## LED Reference

| Colour         | Meaning                    |
| -------------- | -------------------------- |
| Blue, blinking | Mode selection             |
| Green          | Waiting for USB connection |
| Pink           | IMU Mode                   |
| Yellow         | EMG Mode                   |
| Red, blinking  | Passive mode               |

## Troubleshooting

**After selecting IMU mode with the USB connected, the board jumps to passive mode (red blinking led)**

 * The expected signature was not received from the IMU sensor. Make sure the sensor is connected properly.

## Compile

You can compile the program for the MBED controller using MBED Studio.

## Update Firmware

To update the firmware on your board either, either installed MBED Studio and compile and write the software, or download a precompiled image and write it the MCU.

To install a precompiled image, download an image from the releases section. Then connect your MUC to your computer using the "SDA USB" port. The device will appear in your file browser as removable storage named "DAPLINK". Now simply copy or move the *.bin file unto the device and wait for any blinking to stop. Then click the "Reset" button or reconnect it entirely.
