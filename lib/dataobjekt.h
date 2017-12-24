#ifndef DATAOBJEKT_H
#define DATAOBJEKT_H

class Dataobjekt{
  private:
    int PinEcSensor;
    int PinPhSensor;
    int PinTempSensor;
    float ph;
    float ec;
    float temp;
    float phlow;
    float phhigh;
    float eclow;
    float echigh;

  public:
    Dataobjekt(int PinEcSensor, int PinPhSensor, int PinTempSensor);
    ~Dataobjekt();
    void updateph();
    void updateec();
    void updatetemp();
    float getec();
    float getph();
    float gettemp();
  };

#endif
