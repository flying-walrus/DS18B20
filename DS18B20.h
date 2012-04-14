#ifndef DS18B20_h
#define DS18B20_h

class DS18B20
{
  private:
  OneWire* OW;

  public:
  DS18B20( int );
  ~DS18B20();
  float getTemp();
  float getTempF();
};

#endif
