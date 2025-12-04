# Waste-Water-Ponds-Controller
This Project for automatic waste water autoflush controller

# 🌊 Auto-Flush Water Waste Pond Controller (Purwarupa Tambak Ikan/Udang)

Prototipe ini adalah solusi otomatisasi biaya rendah (Low-Cost DIY) untuk memantau dan mengontrol ketinggian air di kolam limbah (Water Waste Pond) atau kolam budidaya.

Proyek ini telah berhasil diuji coba dan berjalan stabil selama satu siklus budidaya penuh.

## 🎯 Latar Belakang & Tujuan Utama

Sistem ini dibuat untuk mengurangi beban kerja operator lokal (Lek Suhanda) yang semula harus memeriksa level air kolam limbah secara manual **6 kali sehari**. Dengan sistem ini, frekuensi kunjungan berkurang menjadi **2 kali sehari**. Kontrol pompa pembuangan limbah (flushing) dilakukan secara otomatis berdasarkan jarak yang terukur.

## 🛠️ Komponen Hardware (Bill of Materials) & Desain Purwarupa

| Komponen | Fungsi Utama | Keterangan Desain |
| :--- | :--- | :--- |
| **Microcontroller** | **Kontrol Logika** | **Arduino Uno** (Inti pemrosesan sistem). |
| **Sensor Jarak** | **Input Level Air** | **HC-SR04 (Ultrasonik)**: Mengukur jarak (cm) ke permukaan air. |
| **Aktor** | **Kontrol Pompa** | **Modul Relay (1 Channel)**: Digunakan sebagai sakelar untuk pompa pembuangan. |
| **Display** | **Output *Real-Time*** | **TM1637 (4 Digit 7-Segment)**: Menampilkan nilai jarak aktual ke operator. |
| **Enclosure** | **Daya Apung & Proteksi** | **Bahan *Upcycled*** (Gabus/Pipa PVC Bekas): Solusi *low-cost* untuk membuat sistem mengambang dan kedap air. |
| **Fitur Override** | **Penanganan *Error*** | **Tombol Hard Reset (Manual)**: Memungkinkan operator memulai ulang sistem saat terjadi *bug* pembacaan sensor atau pompa macet. |

## 📌 Rincian Pinout (Koneksi Hardware ke Arduino Uno)

Tabel ini menunjukkan koneksi pin I/O Digital dari komponen ke Arduino Uno. Pin VCC (5V) dan GND dihubungkan ke sumber daya yang sesuai.

| Komponen | Pin di Komponen | Pin di Arduino Uno | Keterangan |
| :--- | :--- | :--- | :--- |
| **Ultrasonik (HC-SR04)** | **Trig** | **Digital Pin 9** | Output Arduino (Memulai Ping) |
| | **Echo** | **Digital Pin 10** | Input Arduino (Menerima Gema) |
| **Display (TM1637)** | **CLK** | **Digital Pin 6** | Clock (Sinkronisasi Data) |
| | **DIO** | **Digital Pin 7** | Data I/O |
| **Modul Relay** | **IN** (Input Sinyal) | **Digital Pin 5** | Kontrol Pompa (LOW = ON) |

---

## 📜 Kode Arduino (Minimalis)

Kode di bawah ini adalah *sketch* Arduino yang paling ringkas dan langsung mencerminkan logika operasi sistem.

```cpp
// ===============================================
//     SKETCH ARDUINO: AUTO-FLUSH (FINAL)
//     Logic: Pompa ON <= 38 cm, Pompa OFF >= 45 cm
// ===============================================

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

## 🚨 Catatan Khusus: Penanganan Error (Hard Reset)

Karena ini adalah purwarupa lapangan, penanganan *error* pada sensor ultrasonik (misalnya, pembacaan macet atau mengembalikan nilai `0`) dilakukan melalui mekanisme **Hard Reset Power**.

Jika pompa menyala secara tidak normal atau tidak mati setelah air surut, operator dapat menekan tombol *reset* fisik (mematikan/menghidupkan daya), memaksa Arduino untuk *reboot* dan kembali ke status awal (Pompa OFF).
