#include <stdio.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
void toggleBits(char str[]);

int main() {
    char message[200];
    int choice;

    while (1) {
        printf("\n===== TCS Secure Message Utility =====\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
            case 1:
                printf("\nEnter the message to encode: ");
                fgets(message, sizeof(message), stdin);

                // Remove newline if present
                for (int i = 0; message[i] != '\0'; i++) {
                    if (message[i] == '\n') {
                        message[i] = '\0';
                        break;
                    }
                }

                encodeMessage(message);
                break;

            case 2:
                printf("\nEnter the message to decode: ");
                fgets(message, sizeof(message), stdin);

                // Remove newline if present
                for (int i = 0; message[i] != '\0'; i++) {
                    if (message[i] == '\n') {
                        message[i] = '\0';
                        break;
                    }
                }

                decodeMessage(message);
                break;

            case 3:
                printf("\nExiting program. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to reverse a string
void reverseString(char str[]) {
    int i, j;
    for (i = 0; str[i] != '\0'; i++); // find length

    for (j = 0, i = i - 1; j < i; j++, i--) {
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
}

// Function to toggle 2nd and 5th bits
void toggleBits(char str[]) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] ^ (1 << 1);
        str[i] = str[i] ^ (1 << 4);
    }
}

// Encode message 
void encodeMessage(char message[]) {
    reverseString(message);
    toggleBits(message);
    printf("\nEncoded Message: %s\n", message);
}

// Decode message 
void decodeMessage(char message[]) {
    toggleBits(message);
    reverseString(message);
    printf("\nDecoded Message: %s\n", message);
}

