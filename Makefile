# Makefile для лабораторных работ №25 и №26
# Вариант: Очередь + Сортировка простыми вставками

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS =

# Целевой исполняемый файл
TARGET = prog

# Объектные файлы
OBJS = main.o queue.o

# Правило по умолчанию
all: $(TARGET)

# Компоновка
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Компиляция main.o
main.o: main.c queue.h
	$(CC) $(CFLAGS) -c main.c

# Компиляция queue.o
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

# Очистка временных файлов
clean:
	rm -f $(OBJS) $(TARGET)

# Полная пересборка проекта
rebuild: clean all

.PHONY: all clean rebuild