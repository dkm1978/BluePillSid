
#include <SPI.h>

// SRAM opcodes
// #define WREN  6
// #define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2

// SRAM Hold line override
#define HOLD 1

// SRAM modes
#define BYTE_MODE (0x00 | HOLD)
#define PAGE_MODE (0x80 | HOLD)
#define STREAM_MODE (0x40 | HOLD)

// Clock speeds
#define RAMCLK4M   0
#define RAMCLK1M   1
#define RAMCLK250K 2
#define RAMCLK125K 3

#define CS_RAM PA1

SPIClass SPI_1(2);

//-------------------------------- Enable CS pin's -----------------------------
void RAMenable(int pin)
{
  digitalWrite(pin, LOW);
}
//------------------------------------------------------------------------------

//-------------------------------- Disable CS pin's ----------------------------
void RAMdisable(int pin)
{
  digitalWrite(pin, HIGH);
}
//------------------------------------------------------------------------------

//--- Read memory @address. Return value ---------------------------------------
uint8_t RAMread(uint16_t address)
{
  uint8_t read_byte;

  
      RAMenable(CS_RAM); 
     
      SPI_1.transfer(READ);
      SPI_1.transfer((uint8_t)(address >> 8));
      SPI_1.transfer((uint8_t)address);
      read_byte = SPI_1.transfer(0xFF);
      RAMdisable(CS_RAM);
   
  
  return read_byte;
}
//-----------------------------------------------------------------------------

void RAMwrite(uint16_t address, uint8_t data_byte)
{
  
      RAMenable(CS_RAM);
      SPI_1.transfer(WRITE);
      SPI_1.transfer((uint8_t)(address >> 8));
      SPI_1.transfer((uint8_t)address);
      SPI_1.transfer(data_byte);
      RAMdisable(CS_RAM);
  
}


void StartRAM()
{
  
    SPI_1.begin();
    //SPI_1.setClockDivider(SPI_CLOCK_DIV4);
    SPI_1.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    pinMode(CS_RAM,OUTPUT);
   
    RAMenable(CS_RAM);
    SPI_1.transfer(WRSR);
    SPI_1.transfer(BYTE_MODE);
    RAMdisable(CS_RAM);
    
}

