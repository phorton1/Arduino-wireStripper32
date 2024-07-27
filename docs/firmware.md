# wireStripper32 - Installing and Building the Firmware

**[Home](readme.md)** --
**[Design](design.md)** --
**[Electronics](electronics.md)** --
**[Build](build.md)** --
**Firmware** --


## Installing pre-built firmware

I have provided a compiled version of the ESP32 binary program image
in the **/release** folder.

If you do not want to download and install all of the libraries and dependencies
needed to build and upload the firmware, and build it yourself from the Arduino IDE,
you *may* be able to use the pre-built version in the **/release** folder after
you have cloned or copied this repository to your machine someplace.

There are two parts to flashing the firmware to an ESP32.  First there is the
**program binary image** contained in *wireStripper32.ino.bin*. Second, the
ESP32 **SPIFFS filesystem** must contain the webpage (HTML and Javascript) for the
WebUI. A binary image of the SPIFFS file system is contained in *spiffs.bin*.

There is a *Windows* **Batch Fille**, *_upload_firmware.bat_*, that can be
run to upload the firmare.  Open a DOS box and change to the */release* directory,
then run the batch file.

```
	> cd /wherever_you_cloned_this_repo/releases
	> upload_firmware
```

Otherwise, please see the instructions below for how to install the
necessary dependencies, compile, and upload the firmware for the
wireStripper.


**Done!!** Back to the [**beginning**](readme.md) ...