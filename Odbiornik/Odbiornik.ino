#define CE 9 // Pin CE Z NRF24
#define CSN 10 // Pin CSN Z NRF24

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> // https://github.com/nRF24/RF24

RF24 radio(CE, CSN);
const byte address[1] = "001"; // Adres komunikacji (nie wiem co on oznacza ale tak jest w poradniku)
float measurement[13];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[0]);
  radio.setChannel(0x60);
  radio.setPALevel(RF24_PA_HIGH);           // Ustaw wzmocnienie modułu radiowego na wysokie
  radio.setDataRate (RF24_250KBPS);
  radio.startListening(); // Tryb odbiornika
  radio.powerUp();
  radio.setPayloadSize(32);   // размер пакета, в байтах
}
void loop() {
  byte pipeNo;
  if (radio.available(&pipeNo)) {                   //jeżeli są jakieś dane do odczytu
    radio.read(&measurement, sizeof(measurement)); //czytaj dane
  }

  /* LVRx=measurement[0];
    LVRy=measurement[1];
    LSW=measurement[2];
    RVRx=measurement[3];
    RVRy=measurement[4];
    RSW=measurement[5];
    Button1=measurement[6];
    Button2=measurement[7];
    Button3=measurement[8];
    Button4=measurement[9];
    Button5=measurement[10];
    Button6=measurement[11];
    Button7=measurement[12]; */

  Serial.print("1VRx = ");
  Serial.print(measurement[0]);
  Serial.print(" | 1VRy = ");
  Serial.print(measurement[1]);
  Serial.print(" | 1SW = ");
  Serial.print(measurement[2]);
  Serial.print(" | 2VRx = ");
  Serial.print(measurement[3]);
  Serial.print(" | 2VRy = ");
  Serial.print(measurement[4]);
  Serial.print(" | 2SW = ");
  Serial.print(measurement[5]);
  Serial.print(" | LP = ");
  Serial.print(measurement[12]);
  Serial.print(" | PP = ");
  Serial.print(measurement[6]);
  Serial.print(" | B1 = ");
  Serial.print(measurement[10]);
  Serial.print(" | B2 = ");
  Serial.print(measurement[9]);
  Serial.print(" | B3 = ");
  Serial.print(measurement[7]);
  Serial.print(" | B4 = ");
  Serial.print(measurement[11]);
  Serial.print(" | B5 = ");
  Serial.println(measurement[8]);
}
