#include <OneWire.h>
#include <DS18B20.h>


// this is lifted straight from the bildr example. at some point
// i'll want to go through it and try to understand WTF all the magic
// numbers and etc do.

DS18B20::DS18B20( int pin )
{
  OW = new OneWire( pin );

}

DS18B20::~DS18B20()
{
  delete OW;

}

float DS18B20::getTemp()
{
  int returnme = 0;
  byte data[12];
  byte addr[8];
  byte present;
  byte MSB;
  byte LSB;
  float tempRead;
  float TemperatureSum;

  if ( ! OW->search(addr))
  {
    //no more sensors on chain, reset search
    OW->reset_search();
    return -1000;
  }

  if ( OneWire::crc8( addr, 7 ) != addr[7] )
  {
    Serial.println("CRC is not valid");
    return -1001;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28 )
  {
    Serial.println( "Device is not recognized" );
    return -1002;
  }

  OW->reset();
  OW->select(addr);
  OW->write(0x44,1); // start conversion with parasite power on at the end

  present = OW->reset();
  OW->select(addr);
  OW->write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++ )
  {
    data[i] = OW->read();

  }

  OW->reset_search();
  
  MSB = data[1];
  LSB = data[0];

  tempRead = ((MSB << 8) | LSB); // using two's compliment
  TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}

float DS18B20::getTempF()
{
  return getTemp() *9/5 + 32;

}
