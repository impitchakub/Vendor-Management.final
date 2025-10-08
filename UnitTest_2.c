#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char SellerName[100];
char ProductType[100];
float Rating;
char EvaluationDate[100];

void Search_menu()
{
    char line[256];
    char search[100];
    int found = 0, count = 0;

    FILE *file = fopen("VendorManagement.csv","r");
    if (file == NULL)
    {
        printf("Can't open file\n");   
        return;
    }

    printf("+----------+----------------+--------+----------------+\n");
    printf("| Name     | Product Type   | Rating | Evaluation date|\n");
    printf("+----------+----------------+--------+----------------+\n");

    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line,"\n")] = 0;
        char *SellerName = strtok(line, ",");
        char *ProductType = strtok(NULL, ",");
        char *Rating = strtok(NULL, ",");
        char *EvaluationDate = strtok(NULL, "\n");

        printf("| %-8s | %-14s | %-6s | %-14s |\n", SellerName, ProductType, Rating, EvaluationDate);
        count++;
    }

    printf("+----------+----------------+--------+----------------+\n");

    rewind(file);

    printf("Search data: ");
    scanf("%s", search);

    found = 0;
    count = 0;
    printf("+----------+----------------+--------+----------------+\n");
    printf("| Name     | Product Type   | Rating | Evaluation date|\n");
    printf("+----------+----------------+--------+----------------+\n");

    while(fgets(line, sizeof(line), file) != NULL)
    {
        char lineCopy[256];
        strcpy(lineCopy, line);

        if(strstr(lineCopy, search))
        {
            char *SellerName = strtok(lineCopy, ",");
            char *ProductType = strtok(NULL, ",");
            char *Rating = strtok(NULL, ",");
            char *EvaluationDate = strtok(NULL, "\n");

            printf("| %-8s | %-14s | %-6s | %-14s |\n", SellerName, ProductType, Rating, EvaluationDate);
            found = 1;
        }
    }

    if(!found) printf("Data is not found.\n");

    printf("+----------+----------------+--------+----------------+\n");
    fclose(file);
}

