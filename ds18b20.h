
OneWire  ds(17);  // on pin 17 (a 4.7K resistor is necessary)
//DallasTemperature ds(&OW);

byte addr[8];
void ds_init() {
  if (!ds.search(addr)) {
    Serial.println(" No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }
}

float dsRead() {
  byte data[12];

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);
  ds.select(addr);
  ds.write(0xBE);
  int16_t raw = (data[1] << 8) | data[0];

  raw = raw << 3; // 9 bit resolution default
  if (data[7] == 0x10) {
    // "count remain" gives full 12 bit resolution
    raw = (raw & 0xFFF0) + 12 - data[6];
  }
  
  return (float)raw / 16.0;;
}
