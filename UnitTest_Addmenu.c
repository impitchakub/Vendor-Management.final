#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char SellerName[100];
char ProductType[100];
float Rating;
char EvaluationDate[100];

void Add_menu()
{      
    char confirmStatus;
    int year, month, day, valid;        
    FILE *file = fopen("VendorManagement.csv","a");
    if (file == NULL)
    {
        printf("Can't open file\n");   
        return;
    } 

    do {
        printf("Seller Name : ");
        scanf(" %[^\n]", SellerName);
    } while(strlen(SellerName) == 0);

    do {
        printf("Product Type : ");
        scanf(" %[^\n]", ProductType);
    } while(strlen(ProductType) == 0);

    do {
        printf("Rating (0.0 - 5.0): ");
        if(scanf("%f", &Rating) != 1) {
            while(getchar() != '\n');
            Rating = -1;
        }
    } while(Rating < 0.0 || Rating > 5.0);

    do 
    {
        printf("Evaluation Date (YYYY-MM-DD) : ");
        scanf(" %10s", EvaluationDate);

        valid = sscanf(EvaluationDate, "%4d-%2d-%2d", &year, &month, &day);

        if (valid != 3 || strlen(EvaluationDate) != 10 || 
            day < 1 || day > 31 || 
            month < 1 || month > 12 || 
            year > 2025)
        {
            printf("Invalid format! Please enter again.\n");
            valid = 0;
        }
    } 
    while (!valid);

    printf("Confirm data (y/n): ");
    scanf(" %c", &confirmStatus);

    if (confirmStatus == 'y' || confirmStatus == 'Y')
    {
        fprintf(file, "%s,%s,%.2f,%s\n", SellerName, ProductType, Rating, EvaluationDate);   
        printf("Data saved successfully.\n");
    }
    else
    {
        printf("Data not saved.\n");
    }

    fclose(file);
}

void Display_menu()
{

    int select = 2;
    printf("\n=== Vendor Management ===\n");
    printf("1.Add Seller\n");
    printf("2.Search menu\n");
    printf("3.Update menu\n");
    printf("4.Delete menu\n");
    printf("please select the menu : ");
    scanf("%d",&select);
        switch (select)
        {
            case 1:Add_menu();
            break;
            case 2:Search_menu();
            break;
            case 3:Update_menu();
            break;
            case 4:Delete_menu();
            break;

        }
      
}

int main()
{
    Display_menu();
    return 0;
}
