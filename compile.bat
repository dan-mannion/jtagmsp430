set LIB_DIR= msp430lib\obj
msp430-elf-gcc -mmcu=msp430g2553 -L C:\ti\msp430-gcc\include -I C:\ti\msp430-gcc\include -I msp430lib %LIB_DIR%\system.o %LIB_DIR%\watchdog.o %LIB_DIR%\clocks.o %LIB_DIR%\gpio.o %1 -o %~dpn1.o
