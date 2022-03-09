#include <FastLED.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> // https://github.com/nRF24/RF24

#define CE 9 // Pin CE Z NRF24
#define CSN 10 // Pin CSN Z NRF24

#define RVRx A7 // Pin X joysticka 1 (analog)
#define RVRy A6 // pin Y joysticka 1 (analog)
#define RSW 3 // pin "przycisk" joysticka 1
#define LVRx A3 // Pin X joysticka 2 (analog)
#define LVRy A4 // pin Y joysticka 2 (analog)
#define LSW A2 // pin "przycisk" joysticka 2

#define LED_PIN A0
#define NUM_LEDS 5

CRGB leds[NUM_LEDS];

byte measurement[13];

RF24 radio(CE, CSN);
const byte address[1] = "001"; // Adres komunikacji (nie wiem co on oznacza ale tak jest w poradniku)
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(RVRx, INPUT);
  pinMode(RVRy, INPUT);
  pinMode(RSW, INPUT_PULLUP);
  pinMode(LVRx, INPUT);
  pinMode(LVRy, INPUT);
  pinMode(LSW, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  for (int i = 3; i <= 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A1, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.setChannel(0x60);
  radio.setPALevel(RF24_PA_HIGH); // Ustaw wzmocnienie modułu radiowego na wysokie
  radio.setDataRate (RF24_250KBPS);
  radio.stopListening(); // Tryb nadajnika
  radio.powerUp();
  radio.setPayloadSize(32);   // размер пакета, в байтах
}
void loop() {
  measurement[0] = map(analogRead(RVRx), 0, 1023, 0, 255);
  measurement[1] = map(analogRead(RVRy), 0, 1023, 0, 255);
  measurement[2] = !digitalRead(RSW);
  measurement[3] = map(analogRead(LVRx), 0, 1023, 0, 255);
  measurement[4] = map(analogRead(LVRy), 0, 1023, 0, 255);
  measurement[5] = !digitalRead(LSW);
  measurement[6] = !digitalRead(A1);
  measurement[7] = !digitalRead(A5);
  measurement[8] = !digitalRead(7);
  measurement[9] = !digitalRead(8);
  measurement[10] = !digitalRead(6);
  measurement[11] = !digitalRead(5);
  measurement[12] = !digitalRead(4);
  radio.write(&measurement, sizeof(measurement));
  for (int a = 0; a <= NUM_LEDS; a++) {
    if (measurement[a + 8] == HIGH) {
      leds[a] = CRGB(255, 255, 0);
      FastLED.show();
    } else {
      leds[a] = CRGB(0, 0, 0);
      FastLED.show();
    }
  }
  //delay(300);
}
