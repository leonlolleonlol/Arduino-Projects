#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 5
#define SS_PIN  53
#define BUZZER_PIN 6

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Your valid UID: B3 DA 47 39
const byte validUID[4] = {0xB3, 0xDA, 0x47, 0x39};

void setup() {
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init();   // Init MFRC522
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("Scan an RFID card");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  Serial.print("UID tag : ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (isValidCard(mfrc522.uid.uidByte)) {
    playSuccessTune();
  } else {
    playErrorTone();
  }

  delay(1500); // short delay before next scan
}

// ✅ Check if the UID matches
bool isValidCard(byte *uid) {
  for (int i = 0; i < 4; i++) {
    if (uid[i] != validUID[i]) return false;
  }
  return true;
}

// 🎵 Short melody for valid card
void playSuccessTune() {
  int melody[] = { 262, 330, 392 }; // C, E, G
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, melody[i], 200);
    delay(250);
  }
  noTone(BUZZER_PIN);
}

// ❌ Error tone
void playErrorTone() {
  tone(BUZZER_PIN, 180, 300);
  delay(300);
  noTone(BUZZER_PIN);
  delay(100);
  tone(BUZZER_PIN, 180, 300);
  delay(300);
  noTone(BUZZER_PIN);
}
