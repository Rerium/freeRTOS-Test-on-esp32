
#define NUM_LEDS 1
#define DATA_PIN 33
CRGB leds[NUM_LEDS];


void init_led(){
  
  }

void ledOff() {
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(50);
  }
}

void ledTick() {
  /*FastLED.setBrightness(data.br);
  CRGB ncol = CHSV(data.col, 255, data.br);
  CRGB ccol = leds[0];
  if (ccol != ncol) ccol = blend(ccol, ncol, 17);
  // выводим на ленту
  fill_solid(leds, led_num, ccol);
  FastLED.show();*/
}
