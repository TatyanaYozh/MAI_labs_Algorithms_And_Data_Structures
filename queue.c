#include "queue.h"

#define INIT_CAPACITY 10

// Создание очереди
void queue_create(queue* q) {
    q->data = (data_type*)malloc(INIT_CAPACITY * sizeof(data_type));
    q->size = 0;
    q->capacity = INIT_CAPACITY;
}

// Проверка на пустоту
bool queue_is_empty(const queue* q) {
    return q->size == 0;
}

// Вспомогательная процедура автоматического расширения массива
static void ensure_capacity(queue* q) {
    if (q->size >= q->capacity) {
        q->capacity *= 2;
        q->data = (data_type*)realloc(q->data, q->capacity * sizeof(data_type));
    }
}

// Добавление в начало (сдвиг элементов вправо)
void queue_push_front(queue* q, data_type d) {
    ensure_capacity(q);
    for (size_t i = q->size; i > 0; i--) {
        q->data[i] = q->data[i - 1];
    }
    q->data[0] = d;
    q->size++;
}

// Добавление в конец
void queue_push_back(queue* q, data_type d) {
    ensure_capacity(q);
    q->data[q->size++] = d;
}

// Удаление из начала (сдвиг элементов влево)
void queue_pop_front(queue* q) {
    if (q->size == 0) return;
    for (size_t i = 0; i < q->size - 1; i++) {
        q->data[i] = q->data[i + 1];
    }
    q->size--;
}

// Удаление из конца
void queue_pop_back(queue* q) {
    if (q->size > 0) {
        q->size--;
    }
}

// Вывод содержимого очереди в стандартный поток
void queue_print(const queue* q) {
    printf("[");
    for (size_t i = 0; i < q->size; i++) {
        printf("(%d,%d)", q->data[i].key, q->data[i].value);
        if (i < q->size - 1) printf(" ");
    }
    printf("]\n");
}

// Получение текущего размера очереди
size_t queue_size(const queue* q) {
    return q->size;
}

// Удаление элемента по ключу
void queue_erase(queue* q, const key_type k) {
    size_t pos = 0;
    while (pos < q->size && q->data[pos].key != k) {
        pos++;
    }
    if (pos < q->size) {
        for (size_t i = pos; i < q->size - 1; i++) {
            q->data[i] = q->data[i + 1];
        }
        q->size--;
    }
}

// Процедура №2: Вставка элемента в упорядоченную по возрастанию структуру
void queue_insert(queue* q, const data_type d) {
    ensure_capacity(q);
    size_t pos = 0;
    // Ищем позицию для вставки (первый элемент, чей ключ больше ключа d)
    while (pos < q->size && q->data[pos].key < d.key) {
        pos++;
    }
    // Освобождаем место под новый элемент, сдвигая хвост вправо
    for (size_t i = q->size; i > pos; i--) {
        q->data[i] = q->data[i - 1];
    }
    q->data[pos] = d;
    q->size++;
}

// Метод №2: Рекурсивная сортировка простыми вставками
void insertion_sort(queue* q) {
    // Базовый случай рекурсии: очередь из 0 или 1 элемента уже отсортирована
    if (q->size <= 1) return;

    // Шаг 1: "Вытаскиваем" последний элемент из очереди
    data_type last_element = q->data[q->size - 1];
    q->size--; // Временно уменьшаем размер (аналог pop_back)

    // Шаг 2: Рекурсивно сортируем оставшуюся усеченную очередь
    insertion_sort(q);

    // Шаг 3: Вставляем извлеченный элемент на его законное место с помощью Процедуры №2
    queue_insert(q, last_element);
}