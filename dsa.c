#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Product {
    int id;
    char name[50];
    int stock;
    struct Product *left, *right;
} Product;


typedef struct Transaction {
    int id;
    char type;  // P = purchase, S = sale
    int qty;
    struct Transaction *next;
} Transaction;

Product* createProduct(int id, char name[], int stock) {
    Product* newNode = (Product*)malloc(sizeof(Product));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->stock = stock;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Product* insertProduct(Product* root, int id, char name[], int stock) {
    if (root == NULL) return createProduct(id, name, stock);
    if (id < root->id)
        root->left = insertProduct(root->left, id, name, stock);
    else if (id > root->id)
        root->right = insertProduct(root->right, id, name, stock);
    return root;
}

Product* searchProduct(Product* root, int id) {
    if (root == NULL || root->id == id) return root;
    if (id < root->id) return searchProduct(root->left, id);
    else return searchProduct(root->right, id);
}

void displayProducts(Product* root) {
    if (root != NULL) {
        displayProducts(root->left);
        printf("ID: %d | Name: %s | Stock: %d\n", root->id, root->name, root->stock);
        displayProducts(root->right);
    }
}


Transaction* addTransaction(Transaction* head, int id, char type, int qty) {
    Transaction* newNode = (Transaction*)malloc(sizeof(Transaction));
    newNode->id = id;
    newNode->type = type;
    newNode->qty = qty;
    newNode->next = head;
    return newNode;
}

void displayTransactions(Transaction* head) {
    Transaction* temp = head;
    while (temp != NULL) {
        printf("Product ID: %d | Type: %c | Qty: %d\n", temp->id, temp->type, temp->qty);
        temp = temp->next;
    }
}

int main() {
    Product* root = NULL;
    Transaction* history = NULL;
    int ch, id, stock, qty;
    char name[50];

    while (1) {
        printf("\n--- Inventory Menu ---\n");
        printf("1. Add Product\n");
        printf("2. Search Product\n");
        printf("3. Update Stock\n");
        printf("4. View Products\n");
        printf("5. View Transactions\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %s", name);
                printf("Enter Stock: ");
                scanf("%d", &stock);
                root = insertProduct(root, id, name, stock);
                printf("Product added.\n");
                break;

            case 2:
                printf("Enter ID: ");
                scanf("%d", &id);
                {
                    Product* p = searchProduct(root, id);
                    if (p)
                        printf("Found -> ID: %d, Name: %s, Stock: %d\n", p->id, p->name, p->stock);
                    else
                        printf("Not Found.\n");
                }
                break;

            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);
                {
                    Product* p = searchProduct(root, id);
                    if (p) {
                        printf("Enter quantity (+ to add, - to sell): ");
                        scanf("%d", &qty);
                        if (p->stock + qty >= 0) {
                            p->stock += qty;
                            char type = (qty > 0) ? 'P' : 'S';
                            history = addTransaction(history, id, type, abs(qty));
                            printf("Stock updated.\n");
                        } else {
                            printf("Not enough stock!\n");
                        }
                    } else {
                        printf("Product not found.\n");
                    }
                }
                break;

            case 4:
                printf("\n--- Product List ---\n");
                displayProducts(root);
                break;

            case 5:
                printf("\n--- Transactions ---\n");
                displayTransactions(history);
                break;

            case 6:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
