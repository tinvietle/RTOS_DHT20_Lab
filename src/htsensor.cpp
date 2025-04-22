#include <Arduino.h>
#include <DHT20.h>
#include <htsensor.h>
#include <heater.h>
#include <cooler.h>
#include <globals.h>


DHT20 dht20;
uint8_t count = 0;
float globalTemperature = 0;
float globalHumidity = 0;

void readDHT()
{
  //  READ DATA
  uint32_t start = micros();
  int status = dht20.read();
  uint32_t stop = micros();

  if ((count % 10) == 0)
  {
    count = 0;
    Serial.println();
    Serial.println("Type\tHumidity (%)\tTemp (°C)\tTime (µs)\tStatus");
  }
  count++;

  globalTemperature = dht20.getTemperature();
  globalHumidity = dht20.getHumidity();

  Serial.print("DHT20 \t");
  //  DISPLAY DATA, sensor has only one decimal.
  Serial.print(globalHumidity, 1);
  Serial.print("\t\t");
  Serial.print(globalTemperature, 1);
  Serial.print("\t\t");
  Serial.print(stop - start);
  Serial.print("\t\t");
  switch (status)
  {
    case DHT20_OK:
      Serial.print("OK");
      break;
    case DHT20_ERROR_CHECKSUM:
      Serial.print("Checksum error");
      break;
    case DHT20_ERROR_CONNECT:
      Serial.print("Connect error");
      break;
    case DHT20_MISSING_BYTES:
      Serial.print("Missing bytes");
      break;
    case DHT20_ERROR_BYTES_ALL_ZERO:
      Serial.print("All bytes read zero");
      break;
    case DHT20_ERROR_READ_TIMEOUT:
      Serial.print("Read time out");
      break;
    case DHT20_ERROR_LASTREAD:
      Serial.print("Error read too fast");
      break;
    default:
      Serial.print("Unknown error");
      break;
  }
  Serial.print("\n");

  // Handle heater based on temperature
}