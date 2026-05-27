#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Типы для ключа и значения
typedef int key_type;
typedef int value_type;

// Структура элемента данных
typedef struct {
    key_type key;
    value_type value;
} data_type;

// Структура очереди на базе динамического массива
typedef struct {
    data_type* data;    // Массив элементов
    size_t size;        // Текущее количество элементов
    size_t capacity;    // Выделенная память
} queue;

// Базовые операции (Интерфейс АТД)
void queue_create(queue* q);
bool queue_is_empty(const queue* q);
void queue_push_front(queue* q, data_type d);
void queue_push_back(queue* q, data_type d);
void queue_pop_front(queue* q);
void queue_pop_back(queue* q);
void queue_print(const queue* q);
size_t queue_size(const queue* q);
void queue_erase(queue* q, const key_type k);

// Процедура №2: Вставка элемента в упорядоченную по возрастанию очередь с сохранением порядка
void queue_insert(queue* q, const data_type d);

// Метод №2: Сортировка простой вставкой (рекурсивная реализация)
void insertion_sort(queue* q);

#endif