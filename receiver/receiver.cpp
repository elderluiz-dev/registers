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

  // Starts LoRa interface
  if(!(LoRa.begin(LORA_433MHZ)))
  {
    Serial.println("Falha ao iniciar o módulo LoRa!");
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if(packetSize)
  {
    String incomingMessage = "";

    while(LoRa.available())
    {
      incomingMessage += (char)LoRa.read();
    }

    // Serial
    Serial.print("Received Packet: ");
    Serial.println(incomingMessage);
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
    Serial.println("");

    // Display
    display.clearDisplay();

    display.setCursor(0, 0);
    display.print("Mensagem: ");
    display.println(incomingMessage);
    display.drawFastHLine(0, 12, 128, SSD1306_WHITE);

    display.setCursor(0, 16);
    display.print("RSSI: ");
    display.print(LoRa.packetRssi());
    display.println(" dBm");

    display.setCursor(0, 26);
    display.print("SNR: ");
    display.print(LoRa.packetSnr());
    display.println(" dB");

    display.setCursor(0, 36);
    display.print("FreqErr: ");
    display.print(LoRa.packetFrequencyError());
    display.println(" Hz");

    display.display();
  }
}