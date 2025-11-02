#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define TITLE_LEN 50

void addBook(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int *currentCount);
void processSale(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int currentCount);
void lowStockReport(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int currentCount);
int findBookIndexByISBN(int isbns[], int currentCount, int isbn);
void flushStdin(void);

int main(void) {
    int isbns[MAX_BOOKS] = {0};
    char titles[MAX_BOOKS][TITLE_LEN];
    float prices[MAX_BOOKS] = {0.0f};
    int quantities[MAX_BOOKS] = {0};
    int currentCount = 0;
    int choice;

    /* Initialize titles to empty strings */
    for (int i = 0; i < MAX_BOOKS; ++i) titles[i][0] = '\0';

    do {
        printf("\n--- Liberty Books Inventory ---\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { //if input value is integer the code will continue
            printf("Invalid input. Try again.\n"); 
            flushStdin(); 
            continue; 
        }

        switch (choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &currentCount);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, currentCount);
                break;
            case 3:
                lowStockReport(isbns, titles, prices, quantities, currentCount);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    } while (choice != 4);

    return 0;
}

/* Finds index of a book by ISBN returns -1 if not found */
int findBookIndexByISBN(int isbns[], int currentCount, int isbn) {
    for (int i = 0; i < currentCount; ++i) {
        if (isbns[i] == isbn) return i;
    }
    return -1;
}

/* Adds a new book if ISBN doesn't already exist and space available */
void addBook(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int *currentCount) {
    if (*currentCount >= MAX_BOOKS) {
        printf("Inventory full. Cannot add more books.\n");
        return;
    }

    int isbn;
    char tempTitle[TITLE_LEN];
    float price;
    int qty;

    printf("Enter ISBN (integer): ");
    if (scanf("%d", &isbn) != 1)
	{ printf("Invalid ISBN input.\n"); flushStdin();
	return; 
	}

    if (findBookIndexByISBN(isbns, *currentCount, isbn) != -1) {
        printf("Error: A book with ISBN %d already exists. Duplicate not allowed.\n", isbn);
        return;
    }

    flushStdin(); /* clear newline before using fgets */
    printf("Enter Title (max %d chars): ", TITLE_LEN - 1);
    if (fgets(tempTitle, TITLE_LEN, stdin) == NULL) {
        printf("Title input failed.\n");
        return;
    }
    /* Remove trailing newline */
    tempTitle[strcspn(tempTitle, "\n")] = '\0';

    printf("Enter Price: ");
    if (scanf("%f", &price) != 1) { printf("Invalid price.\n"); flushStdin(); return; }

    printf("Enter Quantity: ");
    if (scanf("%d", &qty) != 1) { printf("Invalid quantity.\n"); flushStdin(); return; }

    /* Store into parallel arrays at index currentCount */
    int idx = *currentCount;
    isbns[idx] = isbn;
    strncpy(titles[idx], tempTitle, TITLE_LEN - 1);
    titles[idx][TITLE_LEN - 1] = '\0';
    prices[idx] = price;
    quantities[idx] = qty;

    (*currentCount)++;
    printf("Book added successfully. Current total books: %d\n", *currentCount);
}

/* Process a sale: decrease quantity if enough stock available */
void processSale(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int currentCount) {
    if (currentCount == 0) {
        printf("Inventory empty. No books to sell.\n");
        return;
    }

    int isbn, sold;
    printf("Enter ISBN to sell: ");
    if (scanf("%d", &isbn) != 1) { printf("Invalid ISBN.\n"); flushStdin(); return; }

    int idx = findBookIndexByISBN(isbns, currentCount, isbn);
    if (idx == -1) {
        printf("Book with ISBN %d not found.\n", isbn);
        return;
    }

    printf("Book found: '%s' | Price: %.2f | Available Qty: %d\n", titles[idx], prices[idx], quantities[idx]);
    printf("Enter number of copies sold: ");
    if (scanf("%d", &sold) != 1) { printf("Invalid quantity.\n"); flushStdin(); return; }

    if (sold <= 0) {
        printf("Number of copies sold must be positive.\n");
        return;
    }

    if (sold > quantities[idx]) {
        printf("Error: Not enough stock. Available: %d, Requested: %d\n", quantities[idx], sold);
        return;
    }

    quantities[idx] -= sold;
    printf("Sale processed. Remaining quantity for ISBN %d is %d.\n", isbn, quantities[idx]);
}

/* List all books with quantity < 5 */
void lowStockReport(int isbns[], char titles[][TITLE_LEN], float prices[], int quantities[], int currentCount) {
    printf("\n--- Low Stock Report (quantity < 5) ---\n");
    int found = 0;
    for (int i = 0; i < currentCount; ++i) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Qty: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }
    if (!found) printf("No low-stock books found.\n");
}

/* Helper to clear stdin buffer when needed */
void flushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}


