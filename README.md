# Arduino Star-Delta Controller  
**Mode: ON → STAR → DELTA dengan Proteksi Overload**

Sistem ini mengontrol rangkaian motor 3-fase menggunakan metode **Star–Delta** dengan tombol ON, OFF, dan Overload. Urutan kerja:

1. Tekan **ON** → RUN aktif → STAR menyala  
2. Setelah **5 detik** → STAR mati → DELTA menyala  
3. Tekan **OFF** atau **Overload** → Semua output mati

---

## 🧩 Pin Configuration

| Function        | Pin |
|-----------------|-----|
| ON Button       | 11  |
| OFF Button      | 12  |
| Overload Switch | 13  |
| RUN LED         | 5   |
| STAR LED        | 6   |
| DELTA LED       | 7   |

---

## 🧠 Flow Logic

- **motorState = 0** → Motor OFF  
- **motorState = 1** → STAR mode aktif  
- **motorState = 2** → DELTA mode aktif  

---

## 🧪 Arduino Code

```cpp
const int onButton = 11;
const int offButton = 12;
const int overloadButton = 13;

const int runLed = 5;
const int starLed = 6;
const int deltaLed = 7;

unsigned long previousMillis = 0;
const long interval = 5000; // 5 detik

int motorState = 0; // 0: OFF, 1: STAR, 2: DELTA

void setup() {
  pinMode(onButton, INPUT);
  pinMode(offButton, INPUT);
  pinMode(overloadButton, INPUT);

  pinMode(runLed, OUTPUT);
  pinMode(starLed, OUTPUT);
  pinMode(deltaLed, OUTPUT);
}

void loop() {
  // OFF / Overload → Semua OFF
  if (digitalRead(offButton) == HIGH || digitalRead(overloadButton) == HIGH) {
    motorState = 0;
    digitalWrite(runLed, LOW);
    digitalWrite(starLed, LOW);
    digitalWrite(deltaLed, LOW);
  }

  // ON → Masuk mode STAR
  if (digitalRead(onButton) == HIGH && motorState == 0) {
    motorState = 1;
    digitalWrite(runLed, HIGH);
    digitalWrite(starLed, HIGH);
    previousMillis = millis();
  }

  // Pindah STAR → DELTA setelah interval
  if (motorState == 1 && millis() - previousMillis >= interval) {
    motorState = 2;
    digitalWrite(starLed, LOW);
    digitalWrite(deltaLed, HIGH);
  }

  delay(100);
}