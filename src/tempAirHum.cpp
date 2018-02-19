#include "../lib/DHT.h" //DHT Bibliothek laden
#include "../lib/tempAirHum.h"

#define DHTPIN 3

#define DHTTYPE DHT22    // Es handelt sich um den DHT22 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

void airtemphum_messure() {
  dht.begin(); //DHT22 Sensor starten

  delay(2000);//Zwei Sekunden bis zur Messung warten damit der Sensor etwas //messen kann weil er relativ langsam ist


  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern

  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern

  Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und
  Serial.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
  Serial.println(" %");
  Serial.print("Temperatur: ");
  Serial.print(Temperatur);
  Serial.println(" Grad Celsius");

}
