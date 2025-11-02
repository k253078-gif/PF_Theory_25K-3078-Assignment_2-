#include <stdio.h>

#define ROWS 3
#define COLS 3

// Function declarations
void displayMenu();
void updateSector(int grid[ROWS][COLS]);
void querySector(int grid[ROWS][COLS]);
void runDiagnostic(int grid[ROWS][COLS]);
void printSectorStatus(int status);

int main() {
    int grid[ROWS][COLS] = {0};  // all bits 0 initially (everything OFF and normal)
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSector(grid);
                break;
            case 2:
                querySector(grid);
                break;
            case 3:
                runDiagnostic(grid);
                break;
            case 4:
                printf("\nExiting system. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}

void displayMenu() {
    printf("\n===== IESCO Power Grid Monitoring System =====\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
}

// Update sector status using bitwise logic
void updateSector(int grid[ROWS][COLS]) {
    int row, col, flag, action;

    printf("\nEnter sector coordinates (row and column 0-%d): ", ROWS - 1);
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("Select flag to modify:\n");
    printf("0 = Power (ON/OFF)\n");
    printf("1 = Overload Warning\n");
    printf("2 = Maintenance Required\n");
    printf("Enter flag bit: ");
    scanf("%d", &flag);

    if (flag < 0 || flag > 2) {
        printf("Invalid flag number!\n");
        return;
    }

    printf("Enter action (1 = Set / 0 = Clear): ");
    scanf("%d", &action);

    if (action == 1) {
        grid[row][col] = grid[row][col] | (1 << flag);  // Set bit
        printf("Flag %d SET successfully.\n", flag);
    } else if (action == 0) {
        grid[row][col] = grid[row][col] & ~(1 << flag); // Clear bit
        printf("Flag %d CLEARED successfully.\n", flag);
    } else {
        printf("Invalid action!\n");
    }
}

// Query sector to display human-readable status
void querySector(int grid[ROWS][COLS]) {
    int row, col;

    printf("\nEnter sector coordinates to query (0-%d): ", ROWS - 1);
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSector (%d, %d) status:\n", row, col);
    printSectorStatus(grid[row][col]);
}

// Print readable interpretation of bit flags
void printSectorStatus(int status) {
    if (status & 1)
        printf("- Power: ON\n");
    else
        printf("- Power: OFF\n");

    if (status & 2)
        printf("- Overload: YES\n");
    else
        printf("- Overload: NO\n");

    if (status & 4)
        printf("- Maintenance Required: YES\n");
    else
        printf("- Maintenance Required: NO\n");
}

// Count overloaded and maintenance sectors
void runDiagnostic(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & 2)  // bit 1 = overload
                overloadCount++;
            if (grid[i][j] & 4)  // bit 2 = maintenance
                maintenanceCount++;
        }
    }

    printf("\n===== System Diagnostic Report =====\n");
    printf("Total overloaded sectors: %d\n", overloadCount);
    printf("Total maintenance-required sectors: %d\n", maintenanceCount);
}

