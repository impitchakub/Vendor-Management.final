#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>

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


void Search_menu()
{
    char line[256];
    char search[100];
    int found = 0,index;
    FILE *file = fopen("VendorManagement.csv","r");
    if (file == NULL) return;


    printf("Search by Name or Product Type: ");
    scanf(" %[^\n]", search);

    found = 0;
    index = 1;
    printf("+----+---------------+----------------+--------+----------------+\n");
    printf("| #  | Seller Name   | Product Type   | Rating | EvaluationDate |\n");
    printf("+----+---------------+----------------+--------+----------------+\n");

    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line,"\n")] = 0;
        char lineCopy[256];
        strcpy(lineCopy, line);

        char *SellerName = strtok(lineCopy, ",");
        char *ProductType = strtok(NULL, ",");
        char *Rating = strtok(NULL, ",");
        char *EvaluationDate = strtok(NULL, "\n");

        if(strstr(SellerName, search) || strstr(ProductType, search))
        {
            printf("| %-2d | %-13s | %-14s | %-6s | %-3s |\n", index, SellerName, ProductType, Rating, EvaluationDate);
            found = 1;
        }
        index++;
    }

    if(!found) printf("Data not found.\n");
    printf("+----+---------------+----------------+--------+----------------+\n");

    fclose(file);
}


void Update_menu()
{
    char line[256];
    char SelectSellername[100];
    char newValue[100];
    int choiceUpdate, found;
    int year, month, day, valid;

    FILE *file = fopen("VendorManagement.csv","r");
    if (!file) 
    {
        printf("Can't open file\n");   
        return;
}
    int i = 1;
    printf("+----+---------------+----------------+--------+----------------+\n");
    printf("| #  | Seller Name   | Product Type   | Rating | EvaluationDate |\n");
    printf("+----+---------------+----------------+--------+----------------+\n");

    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line,"\n")] = 0;
        char name[100], product[100], date[100];
        float rate;
        sscanf(line, "%[^,],%[^,],%f,%s", name, product, &rate, date);
        printf("| %-2d | %-13s | %-14s | %-6.2f | %-14s |\n", i, name, product, rate, date);
        i++;
    }
    printf("+----+---------------+----------------+--------+----------------+\n");
    fclose(file);

    do
    {
        printf("Please enter Seller name you want to update (q to quit): ");
        scanf(" %[^\n]", SelectSellername);
        if(strcmp(SelectSellername,"q")==0) break;

        file = fopen("VendorManagement.csv","r");
        FILE *temp = fopen("temp.csv","w");
        if(!file || !temp) 
        { if(file) fclose(file); 
            if(temp) fclose(temp); 
            break; 
        }

        found = 0;
        int currentRecord = 0;

    while(fgets(line,sizeof(line),file))
    {
        line[strcspn(line,"\n")] = 0;
        char name[100], product[100], date[100];
        float rate;
        sscanf(line,"%[^,],%[^,],%f,%s", name, product, &rate, date);

        if(strcmp(name, SelectSellername) == 0 && found == currentRecord)
        {
            printf("Record #%d found for %s:\n", currentRecord+1, name);
            printf("1. Seller Name: %s\n2. Product Type: %s\n3. Rating: %.2f\n4. Evaluation Date: %s\n", name, product, rate, date);
            printf("Select field to update (or 'q' to skip this record): ");

            char input[10];
            scanf(" %[^\n]", input);
            if(strcmp(input,"q")==0)
            {
                currentRecord++;
                fprintf(temp,"%s,%s,%.2f,%s\n", name, product, rate, date);
                continue;
            }

            choiceUpdate = atoi(input);
            if(choiceUpdate == 4)
            {
                do
                {
                    printf("Enter new Evaluation Date (YYYY-MM-DD): ");
                    scanf(" %10s", newValue);
                    valid = sscanf(newValue,"%4d-%2d-%2d",&year,&month,&day);
                    if(valid != 3 || strlen(newValue) != 10 || day < 1 || day > 31 || month < 1 || month > 12 || year > 2025) valid = 0;
                } 
                while(!valid);
            }
            else 
            {
            printf("New Update : ",newValue);
            scanf(" %[^\n]", newValue);
            }
            if(choiceUpdate == 1) strcpy(name,newValue);
            else if(choiceUpdate == 2) strcpy(product,newValue);
            else if(choiceUpdate == 3) rate = atof(newValue);
            else if(choiceUpdate == 4) strcpy(date,newValue);

            currentRecord++;
        }

        fprintf(temp,"%s,%s,%.2f,%s\n", name, product, rate, date);
        }

        fclose(file);
        fclose(temp);

        if(currentRecord > 0)
        {
            remove("VendorManagement.csv");
            rename("temp.csv","VendorManagement.csv");
            printf("%d record(s) processed.\n", currentRecord);
        }
        else
        {
            remove("temp.csv");
            printf("Seller name not found. Please try again.\n");
        }

    } while(1);
}




  
void Delete_menu()
{
    char line[256];
    char deleteName[100];
    int found, i;

    FILE *file;
    
    while(1)
    {
        file = fopen("VendorManagement.csv", "r");
        if (!file) return;

        printf("\nCurrent Vendor List:\n");
        printf("+----+---------------+----------------+--------+----------------+\n");
        printf("| #  | Seller Name   | Product Type   | Rating | EvaluationDate |\n");
        printf("+----+---------------+----------------+--------+----------------+\n");

        i = 1;
        while(fgets(line, sizeof(line), file))
        {
            line[strcspn(line,"\n")] = 0;
            char name[100], product[100], date[100];
            float rate;
            sscanf(line, "%[^,],%[^,],%f,%s", name, product, &rate, date);
            printf("| %-2d | %-13s | %-14s | %-6.2f | %-14s |\n", i, name, product, rate, date);
            i++;
        }
        printf("+----+---------------+----------------+--------+----------------+\n");
        fclose(file);

        printf("Enter Seller Name to delete (or 'q' to quit): ");
        scanf(" %[^\n]", deleteName);
        if(strcmp(deleteName,"q")==0) break;

        file = fopen("VendorManagement.csv", "r");
        FILE *temp = fopen("temp.csv", "w");
        if(!file || !temp) return;

        found = 0;
        int deleteCount = 0;
        while(fgets(line,sizeof(line),file))
        {
            line[strcspn(line,"\n")] = 0;
            char name[100], product[100], date[100];
            float rate;
            sscanf(line,"%[^,],%[^,],%f,%s", name, product, &rate, date);

            if(strcmp(name, deleteName) == 0 && deleteCount == 0)
            {
                deleteCount++;
                found = 1;
                continue;
            }

            fprintf(temp, "%s,%s,%.2f,%s\n", name, product, rate, date);
        }

        fclose(file);
        fclose(temp);

        if(found)
        {
            remove("VendorManagement.csv");
            rename("temp.csv","VendorManagement.csv");
            printf("Seller '%s' deleted successfully.\n", deleteName);
        }
        else
        {
            remove("temp.csv");
            printf("Seller name not found.\n");
        }
    }
}
void Add_menu_input(const char *inSellerName, const char *inProductType, float inRating, const char *inEvaluationDate, int confirm, const char *filename) {
    if (!confirm) return;

    char SellerName[100];
    char ProductType[100];
    char EvaluationDate[100];
    float Rating = inRating;

    strncpy(SellerName, inSellerName, sizeof(SellerName)-1);
    SellerName[sizeof(SellerName)-1] = '\0';

    strncpy(ProductType, inProductType, sizeof(ProductType)-1);
    ProductType[sizeof(ProductType)-1] = '\0';

    strncpy(EvaluationDate, inEvaluationDate, sizeof(EvaluationDate)-1);
    EvaluationDate[sizeof(EvaluationDate)-1] = '\0';

    FILE *file = fopen(filename, "a");
    if (!file) return;

    fprintf(file, "%s,%s,%.2f,%s\n", SellerName, ProductType, Rating, EvaluationDate);
    fclose(file);
}


void test_addData() 
{
    const char *file = "VendorManagement_test.csv";
    remove(file);

    Add_menu_input("BoundaryLow", "ProductA", 0.0, "2024-01-01", 1, file);
    Add_menu_input("BoundaryHigh", "ProductB", 5.0, "2024-01-01", 1, file);

    char longName[101];
    memset(longName, 'A', 100);
    longName[100] = '\0';
    Add_menu_input(longName, "ProductC", 3.5, "2024-01-01", 1, file);

    char extremeName[1005];
    memset(extremeName, 'X', 1004);
    extremeName[1004] = '\0';
    Add_menu_input(extremeName, "ExtremeProduct", 4.2, "2024-01-01", 1, file);

    FILE *f = fopen(file, "r");
    char line[2000];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        count++;
    }
    fclose(f);
}

int UnitTest_addData()
{
    test_addData();
    return 0;
}

int Search_menu_input(const char *search, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    char line[2000];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char copy[2000];
        strcpy(copy, line);
        char *SellerName = strtok(copy, ",");
        char *ProductType = strtok(NULL, ",");
        if ((SellerName && strstr(SellerName, search)) || (ProductType && strstr(ProductType, search))) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

void test_Search_menu() 
{
    const char *file = "VendorManagement_test.csv";
    remove(file);

    Add_menu_input("TestSeller", "TestProduct", 3.0, "2024-01-01", 1, file);

    assert(Search_menu_input("TestSeller", file) == 1);
    assert(Search_menu_input("NonExist", file) == 0);

    remove(file);
}
int UnitTest_searchData()
{
    test_Search_menu();
    return 0;
}
   


    
    //unit test 2 function
    //endtoend
    
void Display_menu()
{
    int select;
    do
    {
        printf("\n=== Vendor Management ===\n");
        printf("1. Add Seller\n");
        printf("2. Search menu\n");
        printf("3. Update menu\n");
        printf("4. Delete menu\n");
        printf("5. Exit\n");
        printf("6. testAdd\n");
        printf("7. testDelete\n");
        printf("8. EndtoEnd\n");
        printf("Please select the menu: ");
        scanf("%d",&select);

        switch (select)
        {
            case 1: Add_menu(); 
            break;
            case 2: Search_menu(); 
            break;
            case 3: Update_menu(); 
            break;
            case 4: Delete_menu(); 
            break;
            case 5: 
                printf("Exiting program...\n");
                break;
            default: printf("Invalid selection. Please try again.\n");
            case 6: UnitTest_addData();
            break;
            case 7: UnitTest_searchData();
            break;
        }
    } while(select != 8);
}

int main()
{

    Display_menu();
    return 0;
}

