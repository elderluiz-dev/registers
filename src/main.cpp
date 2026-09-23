#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "settings.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

SPIClass loraSPI(VSPI);

int packet_count = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(VEXT_PIN, OUTPUT);
  digitalWrite(VEXT_PIN, LOW);
  delay(100);

  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);

  Wire.begin(I2C_SDA, I2C_SCL);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Falha na configuração do display!"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(2, 24);
  display.println("CETEIA");
  display.display();

  delay(2000);

  display.setTextSize(1);

  // Configures SPI pins
  loraSPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, -1);

  // Configures LoRa SPI interface
  LoRa.setSPI(loraSPI);
  LoRa.setPins(SPI_CS, RESET_PIN, DIO0_PIN);

  // LoRa Radios configuration
  LoRa.setTxPower(TX_PWR);
  LoRa.setSpreadingFactor(SF_VALUE);
  LoRa.setCodingRate4(CR_4_5);

  // Starts LoRa interface
  if(!(LoRa.begin(LORA_433MHZ)))
  {
    Serial.println("Falha ao iniciar o módulo LoRa!");
  }
}

void loop() {
  String packet_data = "Oi";

  Serial.print("Enviando pacote: ");
  Serial.println(packet_count);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.println(" - TRANSMISSOR LoRa -");
  display.drawFastHLine(0, 14, 128, SSD1306_WHITE);
  
  display.setCursor(0, 20);
  display.print("Enviados: ");
  display.print(packet_count);
  display.println(" pkts");

  display.setCursor(0, 28);
  display.print("Tamanho: ");
  display.print(sizeof(packet_data.c_str()));
  display.println(" bytes");

  display.setCursor(0, 38);
  display.print("TX Power: ");
  display.print(TX_PWR);
  display.println(" dBm");

  display.setCursor(0, 48);
  display.print("SF: ");
  display.println(SF_VALUE);

  display.display();

  // send packet
  LoRa.beginPacket();
  LoRa.print(packet_data);
  LoRa.endPacket();

  packet_count++;

  delay(500);
}
