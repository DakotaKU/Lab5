#include <stdio.h>
#include <string.h>

// Number of months
#define NUM_MONTHS 12

// Function declarations
void displayMonthlySales(const double sales[], const char months[][12]);
void displaySalesSummary(const double sales[], const char months[][12]);
void displaySixMonthMovingAverage(const double sales[], const char months[][12]);
void displaySalesHighToLow(const double sales[], const char months[][12]);

int main() {
    // Sales data
    double sales[NUM_MONTHS];
    char months[NUM_MONTHS][12] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Read sales from file (or you can hardcode them for testing)
    FILE *file = fopen("sales.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open sales data file.\n");
        return 1;
    }

    // Load sales data into array
    for (int i = 0; i < NUM_MONTHS; i++) {
        fscanf(file, "%lf", &sales[i]);
    }
    fclose(file);

    // Generate reports
    displayMonthlySales(sales, months);
    displaySalesSummary(sales, months);
    displaySixMonthMovingAverage(sales, months);
    displaySalesHighToLow(sales, months);

    return 0;
}

// Function to display the monthly sales report
void displayMonthlySales(const double sales[], const char months[12][12]) {
    printf("Monthly Sales Report for 2024\n");
    printf("%-10s Sales\n", "Month");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%-10s %.2lf\n", months[i], sales[i]);
    }
    printf("\n");
}

// Function to display the sales summary (minimum, maximum, average)
void displaySalesSummary(const double sales[], const char months[][12]) {
    double minSales = sales[0], maxSales = sales[0], sum = 0;
    int minIndex = 0, maxIndex = 0;

    for (int i = 0; i < NUM_MONTHS; i++) {
        sum += sales[i];
        if (sales[i] < minSales) {
            minSales = sales[i];
            minIndex = i;
        }
        if (sales[i] > maxSales) {
            maxSales = sales[i];
            maxIndex = i;
        }
    }
    double averageSales = sum / NUM_MONTHS;

    printf("Sales Summary Report:\n");
    printf("Minimum sales: %.2lf (%s)\n", minSales, months[minIndex]);
    printf("Maximum sales: %.2lf (%s)\n", maxSales, months[maxIndex]);
    printf("Average sales: %.2lf\n\n", averageSales);
}

// Function to calculate and display the six-month moving average
void displaySixMonthMovingAverage(const double sales[], const char months[][12]) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 0; i <= NUM_MONTHS - 6; i++) {
        double sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        printf("%s-%s: %.2lf\n", months[i], months[i + 5], sum / 6);
    }
    printf("\n");
}

// Function to display the sales report sorted from highest to lowest
void displaySalesHighToLow(const double sales[], const char months[][12]) {
    // Create arrays to store the sorted data
    double sortedSales[NUM_MONTHS];
    char sortedMonths[NUM_MONTHS][12];

    // Copy original sales data
    for (int i = 0; i < NUM_MONTHS; i++) {
        sortedSales[i] = sales[i];
        strcpy(sortedMonths[i], months[i]);
    }

    // Sort the sales in descending order
    for (int i = 0; i < NUM_MONTHS - 1; i++) {
        for (int j = i + 1; j < NUM_MONTHS; j++) {
            if (sortedSales[i] < sortedSales[j]) {
                // Swap sales
                double tempSales = sortedSales[i];
                sortedSales[i] = sortedSales[j];
                sortedSales[j] = tempSales;
                // Swap months
                char tempMonth[12];
                strcpy(tempMonth, sortedMonths[i]);
                strcpy(sortedMonths[i], sortedMonths[j]);
                strcpy(sortedMonths[j], tempMonth);
            }
        }
    }

    // Print the sorted sales report
    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%-10s %.2lf\n", sortedMonths[i], sortedSales[i]);
    }
    printf("\n");
}
