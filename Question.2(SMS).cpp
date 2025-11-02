#include <stdio.h>

// Function declarations
void inputInventory();
void getCustomerInfo();
void displayInventory();
void addItemToCart();
void displayTotalBill();
void showInvoice();
int findProductIndex(int code);
void updateInventory(int code, int quantity);

// Declaring global variables
int product_codes[50], stock[50], price[50];
int total_products;

int cart_code[50], cart_qty[50];
int cart_count = 0;
int max_cart;

char name[30];
long long cnic;

float totalBill = 0, discountedBill = 0;

int main()
{
    int choice;

    printf("===== Supermarket Inventory Setup =====\n");
    inputInventory();

    printf("\nEnter maximum number of different products a customer can buy: ");
    scanf("%d", &max_cart);

    while (1)
    {
        printf("\n===== Supermarket Menu =====\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            getCustomerInfo();
            break;

        case 2:
            displayInventory();
            break;

        case 3:
            addItemToCart();
            break;

        case 4:
            displayTotalBill();
            break;

        case 5:
            showInvoice();
            break;

        case 6:
            printf("\nThank you for visiting our Supermarket!\n");
            return 0;

        default:
            printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}

// FUNCTION DEFINITIONS 

void inputInventory()
{
    printf("Enter total number of products in inventory (max 50): ");
    scanf("%d", &total_products);

    for (int i = 0; i < total_products; i++)
    {
        printf("\nEnter product code: ");
        scanf("%d", &product_codes[i]);

        printf("Enter quantity in stock: ");
        scanf("%d", &stock[i]);

        printf("Enter price per product: ");
        scanf("%d", &price[i]);
    }

    printf("\nInventory setup completed!\n");
}

void getCustomerInfo()
{
    printf("\nEnter your name (max 30 characters): ");
    getchar(); // Clear buffer before taking string input
    fgets(name, sizeof(name), stdin);

    // Remove newline from fgets
    int i = 0;
    while (name[i] != '\0')
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';
            break;
        }
        i++;
    }

    printf("Enter CNIC number (without dashes): ");
    scanf("%lld", &cnic);

    printf("\nCustomer information saved successfully!\n");
}

void displayInventory()
{
    printf("\nProduct Code | Quantity | Price\n");
    printf("--------------------------------\n");

    for (int i = 0; i < total_products; i++)
    {
        printf("     %03d      |    %2d     |  %d\n", product_codes[i], stock[i], price[i]);
    }
}

void addItemToCart()
{
    if (cart_count >= max_cart)
    {
        printf("\nCart is full! Cannot add more items.\n");
        return;
    }

    int code, qty, index;

    printf("\nEnter product code to add to cart: ");
    scanf("%d", &code);

    index = findProductIndex(code);
    if (index == -1)
    {
        printf("Invalid product code!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty > stock[index])
    {
        printf("Not enough stock available!\n");
        return;
    }

    cart_code[cart_count] = code;
    cart_qty[cart_count] = qty;
    cart_count++;

    updateInventory(code, qty);

    printf("Item added to cart successfully!\n");
}

void updateInventory(int code, int quantity)
{
    int index = findProductIndex(code);
    if (index != -1)
    {
        stock[index] -= quantity;
    }
}

int findProductIndex(int code)
{
    for (int i = 0; i < total_products; i++)
    {
        if (product_codes[i] == code)
            return i;
    }
    return -1;
}

void displayTotalBill()
{
    totalBill = 0;

    for (int i = 0; i < cart_count; i++)
    {
        int index = findProductIndex(cart_code[i]);
        if (index != -1)
        {
            totalBill += cart_qty[i] * price[index];
        }
    }

    char promoInput[20];
    int hasPromo;

    printf("\nDo you have a promo code? (1 = Yes, 0 = No): ");
    scanf("%d", &hasPromo);

    if (hasPromo == 1)
    {
        printf("Enter promo code: ");
        scanf("%s", promoInput);

        char correctPromo[] = "WASI2025";
        int i = 0, match = 1;

        while (correctPromo[i] != '\0' || promoInput[i] != '\0')
        {
            if (correctPromo[i] != promoInput[i])
            {
                match = 0;
                break;
            }
            i++;
        }

        if (match == 1)
        {
            discountedBill = totalBill * 0.75;
            printf("25%% discount applied successfully!\n");
        }
        else
        {
            discountedBill = totalBill;
            printf("Invalid promo code entered. No discount applied.\n");
        }
    }
    else
    {
        discountedBill = totalBill;
    }

    printf("\nTotal Bill: %.2f\n", totalBill);
    printf("Bill after discount: %.2f\n", discountedBill);
}

void showInvoice()
{
    printf("\n===== Final Invoice =====\n");
    printf("Customer Name: %s\n", name);
    printf("Customer CNIC: %lld\n", cnic);

    printf("\nItems Purchased:\n");
    printf("Code | Quantity | Price | Subtotal\n");
    printf("----------------------------------\n");

    for (int i = 0; i < cart_count; i++)
    {
        int index = findProductIndex(cart_code[i]);
        int subtotal = cart_qty[i] * price[index];
        printf("%03d  |    %2d     |  %4d |  %5d\n", cart_code[i], cart_qty[i], price[index], subtotal);
    }

    printf("----------------------------------\n");
    printf("Total: %.2f\n", totalBill);
    printf("Final Bill (after discount): %.2f\n", discountedBill);
}



