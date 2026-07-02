# Ringkasan Pembelajaran Bab 5

Bab ini membahas struktur data dan konsep dasar C.

## Pembelajaran Utama:

### 1. Enums (Enumerasi)
- Digunakan untuk mendefinisikan sekumpulan konstanta integer bernama.
- Contoh (`enum_test.c`): `unit_of_measure` untuk `COUNT`, `POUNDS`, `PINTS`.

### 2. Unions (Gabungan)
- Memungkinkan tipe data yang berbeda disimpan di lokasi memori yang sama.
- Hanya satu anggota yang dapat menyimpan nilai pada waktu tertentu.
- Contoh (`enum_test.c`): Union `quantity` untuk menyimpan `count` (short), `weight` (float), atau `volume` (float) berdasarkan `unit_of_measure`.

### 3. Structs (Struktur)
- Digunakan untuk mengelompokkan tipe data yang berbeda ke dalam satu unit.
- **Struktur Dasar**:
  - Contoh (`struct-c.c`): `struct fish` untuk `name`, `spesies`, `teeth`, `age`.
- **Struktur Bersarang & Pointer**:
  - Contoh (`enum_test.c`): `fruit_order` menggabungkan `const char *name`, `const char *country`, `quantity amount`, `unit_of_measure measure`.
  - Contoh (`turtle.c`): Struct `turtle` dengan `char *name`, `char *spesis`, `int age`. Mendemonstrasikan pengiriman struct dengan referensi (`turtle *t`) dan mengakses anggota menggunakan operator `->` (misalnya, `t->age`).

### 4. Makefile
- Struktur dasar untuk mengotomatisasi proses build.
- `makefile` yang disediakan memiliki target `goal` yang sederhana tetapi memerlukan definisi lebih lanjut untuk kompilasi yang sebenarnya.

### Tangkapan Layar (Screenshot)
Lihat `Screenshot_2026-07-03_02-14-41.png` untuk konteks visual.