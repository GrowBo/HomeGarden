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
    //messureup
    void updateph();
    void updateec();
    void updatetemp();
    //GET
    float getec();
    float getph();
    float gettemp();
    float getphlow();
    float getphhigh();
    float geteclow();
    float getechigh();
    //SET
    void setec(float ec);
    void setph(float ph);
    void settemp(float temp);
    void setphlow(float phlow);
    void setphhigh(float phhigh);
    void seteclow(float eclow);
    void setechigh(float echigh);
  };

#endif
