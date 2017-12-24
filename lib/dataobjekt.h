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

  public:
    Dataobjekt(int PinEcSensor, int PinPhSensor, int PinTempSensor);
    ~Dataobjekt();
    void checkph();
    void checkec();
    void checktemp();
  };

#endif
