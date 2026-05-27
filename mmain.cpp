#include "queue.h"
#include <stdio.h>

int main() {
    queue myQueue;
    queue_create(&myQueue);

    printf("=== Демонстрация работы АТД Очередь (Вариант 2) ===\n\n");

    // 1. Наполнение элементами вразнобой
    printf("1. Наполняем очередь элементами:\n");
    data_type items[] = { {30, 300}, {10, 100}, {50, 500}, {20, 200}, {40, 400} };
    for (int i = 0; i < 5; i++) {
        queue_back(&myQueue, items[i]); // имитируем стандартный push_back
        // Но используем имя из нашего интерфейса:
        queue_push_back(&myQueue, items[i]);
        printf("   Добавлен элемент с ключом: %d\n", items[i].key);
    }

    printf("\n2. Текущее состояние очереди: ");
    queue_print(&myQueue);

    // 2. Тестирование сортировки
    printf("\n3. Запуск рекурсивной сортировки простыми вставками:\n");
    insertion_sort(&myQueue);
    printf("   Очередь после сортировки: ");
    queue_print(&myQueue);

    // 3. Тестирование Процедуры №2 (Вставка в упорядоченную структуру)
    printf("\n4. Тестирование Процедуры №2 (Вставка элемента {25, 250} с сохранением порядка):\n");
    data_type newItem = {25, 250};
    queue_insert(&myQueue, newItem);
    printf("   Результат вставки: ");
    queue_print(&myQueue);

    // 4. Демонстрация удаления и проверки свойств
    printf("\n5. Извлечение элементов и проверка АТД:\n");
    printf("   Текущий размер: %zu\n", queue_size(&myQueue));
    
    printf("   Удаляем первый элемент из головы (pop_front): ");
    queue_pop_front(&myQueue);
    queue_print(&myQueue);

    printf("   Удаляем элемент с ключом 40 (queue_erase): ");
    queue_erase(&myQueue, 40);
    queue_print(&myQueue);

    printf("\n=== Тестирование успешно завершено ===\n");

    // Освобождение ресурсов
    free(myQueue.data);
    return 0;
}