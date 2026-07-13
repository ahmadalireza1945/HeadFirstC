CC = gcc

SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

TARGET = $(BIN_DIR)/my_game

# PERBAIKAN: Sintaks wildcard yang benar
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# PERBAIKAN: Menggunakan SOURCES (jamak) dan ekstensi .o yang benar
OBJECTS = $(SOURCES:.c=.o)

# PERBAIKAN: Menambahkan minus (-) sebelum flag I
CFLAGS = -I$(INCLUDE_DIR) $(shell pkg-config --cflags allegro-5)
LIBS = $(shell pkg-config --libs allegro-5 allegro_image-5) -lm

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "compile selesai =: $(TARGET)"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	# PERBAIKAN: Mengubah TARGETS menjadi TARGET
	rm -f $(OBJECTS) $(TARGET)
	@echo "file berhasil di bersihkan."
