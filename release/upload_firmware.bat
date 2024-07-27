@ECHO.
@ECHO ----------------------------------------
@ECHO Upload the wireStripper32 firmware
@ECHO ----------------------------------------
@ECHO You will likely need to change the COM port and
@ECHO You may need to change these paths if your Arduino
@ECHO installation is different
@ECHO.
@ECHO OFF

set ESP_PATH=%USERPROFILE%\AppData\Local\Arduino15\packages\esp32
set ESP_TOOL=%ESP_PATH%\tools\esptool_py\3.0.0\esptool.exe
set ESP_SPIFF_TOOL=%ESP_PATH%\tools\mkspiffs\0.2.3\mkspiffs
set ESP_BOOT_BIN=%ESP_PATH%\hardware\esp32\1.0.6/tools/partitions/boot_app0.bin
set ESP_BOOTLOADER_BIN=%ESP_PATH%\hardware\esp32\1.0.6/tools/sdk/bin/bootloader_qio_80m.bin

REM You should not need to change these

set ESP_ARGS=--chip esp32 ^
--port COM14 ^
--baud 921600 ^
--before default_reset ^
--after hard_reset write_flash ^
-z ^
--flash_mode dio ^
--flash_freq 80m ^
--flash_size detect

@ECHO ON
@ECHO ----- UPLOAD THE BINARY IMAGE ...

%ESP_TOOL% %ESP_ARGS% ^
0xe000 %ESP_BOOT_BIN% ^
0x1000 %ESP_BOOTLOADER_BIN% ^
0x10000 wireStripper32.ino.bin ^
0x8000 wireStripper32.ino.partitions.bin


@ECHO.
@ECHO ----- CREATE THE SPIFFS IMAGE

%ESP_SPIFF_TOOL% -c "..\data" -p 256 -b 4096 -s 1505280 ./spiffs.bin


@ECHO.
@ECHO ----- UPLOAD THE SPIFFS IMAGE

%ESP_TOOL% %ESP_ARGS% ^
2686976 ./spiffs.bin


@ECHO.
@ECHO Done.
@ECHO.
