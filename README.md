📌 Panduan Debug & Import Library NewPing di Android (Bluino Loader)

1️⃣ Download Library

Akses halaman resmi Arduino Library via browser Android.

Cari library NewPing.

Download file .zip library.

Pastikan semua file library berada dalam satu folder supaya mudah dipindahkan.


2️⃣ Extract File

Extract zip library ke folder sementara yang sudah kamu siapkan di Android.

Hasil ekstraksi akan berupa folder berisi .h dan .cpp files.


3️⃣ Pindahkan ke Folder Bluino

Cut folder hasil ekstraksi, pindahkan ke bluino-libraries di storage Android.

Bisa pakai file manager bawaan Android untuk memindahkan folder.

Catatan: Folder harus benar-benar berada di dalam bluino-libraries agar Bluino Loader bisa mengenalinya.


4️⃣ Buka Library di Bluino Loader

Jalankan Bluino Loader app.

Pilih menu File → Libraries.

Folder library yang baru ditambahkan akan muncul.

Pilih file .ino yang ingin kamu buka.


5️⃣ Compile Tanpa Arduino

Setelah file .ino terbuka, tap ikon Upload tanpa menyambungkan Arduino.

Bluino Loader akan melakukan compile dan menampilkan notice:

Tidak ada board terhubung

Artinya compile sukses. Nanti, begitu Arduino dicolok, kode akan langsung jalan.



---
