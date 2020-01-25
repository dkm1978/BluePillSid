# BluePillSid
STM32 player for Commodore 64 SID files. (6581/8580)

Used :

      1)    Stm32F103C8T6 board ( aka BLuePill ) prince $2
      
      2)    SwinSID Nano - replacement for SID 6581 8580 chip ( used for testing ) price $15
      
      3)    Microchip 23LC512 : 512Kbit SPI Serial SRAM with SDI and SQI Interface $2.5
      
      4)    Cheap SC Card rader form Aliexpress  $0.5
      

In action : https://youtu.be/oHyz87CWHZA - without SPI Ram

In action : https://youtu.be/LYUZpmviRTI - 64KB SPI Ram

Programmed using Arduino.
The project uses a 6502 processor emulator "fake6502" available at http://rubbermallet.org/fake6502.c

The connection diagram is very simple and everything is in the program code.

The SD card uses  :SPI1

Serial memory     :SPI2

The prototype uses a MOS8580 / 6581 SwinSID system replacement, it does not require any additional external components for proper operation. _RES signal pulled up to 5v. The R / _W signal is pulled up to GND and the system is controlled using the _CS signal.

Thanks to Branko Simic (https://github.com/Bakisha) for support and help in the project.
