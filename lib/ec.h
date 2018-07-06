#ifndef EC_H
#define EC_H
#include <OneWire.h>

void ec_lop(OneWire* onewpoint);
float ec_messure(OneWire* onewpoint);
void PrintReadings();

#endif
