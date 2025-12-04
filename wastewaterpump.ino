// 1. LIBRARY
#include <NewPing.h>      
#include <TM1637Display.h> 

// 2. DEFINISI PIN & PARAMETER
#define TRIGGER_PIN  9    
#define ECHO_PIN     10   
#define MAX_DISTANCE 200  
#define CLK 6             
#define DIO 7             
#define RELAY_PIN    5    

// 3. INISIALISASI OBJEK
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
TM1637Display display(CLK, DIO);

// ===============================================
//     SETUP
// ===============================================
void setup() {
  // Atur Pin Relay sebagai Output dan kondisi awal OFF (HIGH = OFF untuk Active LOW relay)
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 
  
  // Atur kecerahan display
  display.setBrightness(0x0a); 
}

// ===============================================
//     LOOP
// ===============================================
void loop() {
  // --- 1. Pembacaan Ultrasonik ---
  delay(50); 
  int jarak_cm = sonar.ping_cm();

  // --- 2. Tampilkan Nilai ke Display TM1637 ---
  // Angka 0 akan ditampilkan jika terjadi error baca sensor
  display.showNumberDec(jarak_cm, false, 4, 0); 
  
  // --- 3. LOGIKA KONTROL POMPA ---
  
  // LOGIC 1: AKTIVASI POMPA (Air Penuh)
  // Jarak ke sensor LEBIH KECIL atau sama dengan 38 cm
  if (jarak_cm <= 38) {
    digitalWrite(RELAY_PIN, LOW); // AKTIFKAN Pompa
  }

  // LOGIC 2: DEAKTIVASI POMPA (Air Rendah)
  // Jarak ke sensor LEBIH BESAR atau sama dengan 45 cm
  else if (jarak_cm >= 45) {
    digitalWrite(RELAY_PIN, HIGH); // MATIKAN Pompa
  }

  delay(2000); 
}