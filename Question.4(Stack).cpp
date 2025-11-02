#include <stdio.h>

#define MAX_SIZE 100

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main()
{
    int stack[MAX_SIZE];
    int top = -1;   // Stack starts empty
    int choice;

    printf("===== Stack Implementation using Arrays =====\n");

    do
    {
        printf("\n1. PUSH (Insert)\n");
        printf("2. POP (Remove)\n");
        printf("3. PEEK (View Top Element)\n");
        printf("4. DISPLAY (Show All Elements)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                push(stack, &top, MAX_SIZE);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program... Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Push function
void push(int stack[], int *top, int maxSize)
{
    if (*top == maxSize - 1)
    {
        printf("Stack Overflow! Cannot add more elements.\n");
        return;
    }

    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);

    (*top)++;
    stack[*top] = value;
    printf("%d pushed onto the stack.\n", value);
}

//  Pop function
void pop(int stack[], int *top)
{
    if (*top == -1)
    {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }

    printf("Popped element: %d\n", stack[*top]);
    (*top)--;
}

//Peek function
void peek(int stack[], int top)
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", stack[top]);
}

// Display function
void display(int stack[], int top)
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("\nStack elements (Top to Bottom):\n");
    for (int i = top; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
}

