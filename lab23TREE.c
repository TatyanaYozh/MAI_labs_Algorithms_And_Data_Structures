//
// Created by YOJ on 12.05.2026.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    Peony = 1,
    Rose,
    Dandelion,
    Tulip,
    Carnation,
    Jasmine,
    Narcissus
} Flowers;

// структура Node
typedef struct Node {
    Flowers data;
    struct Node *left;
    struct Node *right;
} Node;

// enum в строку
const char* stringFlowers(Flowers c) {
    switch (c) {
        case Peony:
            return "Peony";
        case Rose:
            return "Rose";
        case Dandelion:
            return "Dandelion";
        case Tulip:
            return "Tulip";
        case Carnation:
            return "Carnation";
        case Jasmine:
            return "Jasmine";
        case Narcissus:
            return "Narcissus";
        default:
            return "None";
    }
}

// Создание нового Node
Node* makeNewNode(Flowers value) {
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL) {
        return NULL;
    }
    new->data = value;
    new->left = NULL;
    new->right = NULL;
    return new;
}

// Добавление Node
Node* addNewNode(Node* root, Flowers value) {
    if (root == NULL) {
        return makeNewNode(value);
    }
    if (value < root->data) {
        root->left = addNewNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = addNewNode(root->right, value);
    }
    else {
        printf("This element is already present in the tree.\n");
    }
    return root;
}

// Поиск минимального Node
Node* findMinNode(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Удаление Node
Node* deleteNode(Node* root, Flowers value) {
    if (root == NULL) {
        printf("The element was not found.\n");
        return NULL;
    }
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Потомки
        Node* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Текстовая визуализация дерева
void Visual(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    Visual(root->right, depth + 1);
    for (int i = 0; i < depth; i++){
        printf("    ");
    }
    printf("%s\n", stringFlowers(root->data));
    Visual(root->left, depth + 1);
}

// Освобождение памяти
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Проверка, является ли дерево линейным списком
int isALine(Node* root) {
    // Пустое дерево
    if (root == NULL) {
        return 1;
    }
    // Два потомка
    if (root->left != NULL && root->right != NULL) {
        return 0;
    }
    // Ноль потомков
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    // Один потомок
    if (root->left != NULL) {
        return isALine(root->left);
    } else {
        return isALine(root->right);
    }
}


int main() {
    Node* root = NULL;
    int inpt;
    inpt = 0;
    int input;
    Flowers value;
    while (inpt != 5) {
        printf("1 -- to add a node to the tree.\n");
        printf("2 -- to remove a node and all its descendants from the tree.\n");
        printf("3 -- to visualize a text tree.\n");
        printf("4 -- to check if the tree is a linear list.\n");
        printf("5 -- to finish the work.\n");
        printf("Enter a number: ");
        scanf("%d", &inpt);

        switch (inpt) {
            case 1:
                printf("\nEnter the number corresponding to the node.\n");
                printf("1 -- Peony, 2 -- Rose, 3 -- Dandelion, 4 -- Tulip,\n");
                       printf("5 -- Carnation, 6 -- Jasmine, 7 -- Narcissus)\n");
                scanf("%d", &input);
                root = addNewNode(root, input);
                break;
            case 2:
                printf("\nEnter the number corresponding to the value to be deleted from the tree.\n");
                printf("1 -- Peony, 2 -- Rose, 3 -- Dandelion, 4 -- Tulip,\n");
                printf("5 -- Carnation, 6 -- Jasmine, 7 -- Narcissus)\n");
                scanf("%d", &input);
                root = deleteNode(root, input);
                break;
            case 3:
                printf("\nThe text visualization of a tree:\n");
                Visual(root, 0);
                printf("\n");
                break;
            case 4:
                if (isALine(root)) {
                    printf("\nYes, the tree is a linear list.\n");
                } else {
                    printf("\nNo, a tree is not a linear list.\n");
                }
                break;
            case 5:
                printf("The end of work.\n");
                freeTree(root);
                break;
            default:
                printf("Incorrect data, please try again.\n");
        }
    }
    return 0;
}



