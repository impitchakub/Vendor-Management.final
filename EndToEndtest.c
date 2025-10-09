#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char SellerName[100];
char ProductType[100];
float Rating;
char EvaluationDate[100];

void Add_menu_file(const char *filename, const char *SellerName, const char *ProductType, float Rating, const char *EvaluationDate) {
    FILE *file = fopen(filename,"a");
    if(!file) return;
    fprintf(file,"%s,%s,%.2f,%s\n", SellerName, ProductType, Rating, EvaluationDate);
    fclose(file);
}

void Search_menu_file_print(const char *filename, const char *keyword) {
    FILE *file = fopen(filename,"r");
    if(!file) return;
    char line[256];
    printf("+----+---------------+----------------+--------+----------------+\n");
    printf("| #  | Seller Name   | Product Type   | Rating | EvaluationDate |\n");
    printf("+----+---------------+----------------+--------+----------------+\n");
    int index = 1;
    while(fgets(line,sizeof(line),file)) {
        char Seller[100], Product[100], Date[100];
        float Rate;
        sscanf(line,"%[^,],%[^,],%f,%s", Seller, Product, &Rate, Date);
        if(strstr(Seller,keyword) || strstr(Product,keyword))
            printf("| %-2d | %-13s | %-14s | %-6.2f | %-14s |\n", index, Seller, Product, Rate, Date);
        index++;
    }
    printf("+----+---------------+----------------+--------+----------------+\n");
    fclose(file);
}

int Search_menu_file(const char *filename, const char *keyword) {
    FILE *file = fopen(filename,"r");
    char line[256];
    int found = 0;
    while(fgets(line,sizeof(line),file)) {
        if(strstr(line,keyword)) { found=1; break; }
    }
    fclose(file);
    return found;
}

void Update_menu_file(const char *filename, const char *target, const char *newProduct, float newRating, const char *newDate) {
    FILE *file = fopen(filename,"r");
    FILE *temp = fopen("temp.csv","w");
    char line[256];
    while(fgets(line,sizeof(line),file)) {
        char Seller[100], Product[100], Date[100];
        float Rate;
        sscanf(line,"%[^,],%[^,],%f,%s", Seller, Product, &Rate, Date);
        if(strcmp(Seller,target)==0) {
            fprintf(temp,"%s,%s,%.2f,%s\n", Seller, newProduct, newRating, newDate);
        } else {
            fprintf(temp,"%s,%s,%.2f,%s\n", Seller, Product, Rate, Date);
        }
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
}

void Delete_menu_file(const char *filename, const char *target) {
    FILE *file = fopen(filename,"r");
    FILE *temp = fopen("temp.csv","w");
    char line[256];
    while(fgets(line,sizeof(line),file)) {
        char Seller[100], Product[100], Date[100];
        float Rate;
        sscanf(line,"%[^,],%[^,],%f,%s", Seller, Product, &Rate, Date);
        if(strcmp(Seller,target)!=0)
            fprintf(temp,"%s,%s,%.2f,%s\n", Seller, Product, Rate, Date);
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
}

void test_Add() {
    const char *filename = "test_add.csv";
    remove(filename);

    Add_menu_file(filename,"Alice","Phone",4.0,"2024-03-01");
    Add_menu_file(filename,"Bob","Laptop",5.0,"2024-04-01");

    assert(Search_menu_file(filename,"Alice")==1);
    assert(Search_menu_file(filename,"Bob")==1);

    printf("Unit Test Add Passed\n");
}

void test_Delete() {
    const char *filename = "test_delete.csv";
    remove(filename);

    Add_menu_file(filename,"Alice","Phone",4.0,"2024-03-01");
    Add_menu_file(filename,"Bob","Laptop",5.0,"2024-04-01");

    Delete_menu_file(filename,"Alice");
    assert(Search_menu_file(filename,"Alice")==0);
    assert(Search_menu_file(filename,"Bob")==1);

    printf("Unit Test Delete Passed\n");
}

void test_Update() {
    const char *filename = "test_update.csv";
    remove(filename);

    Add_menu_file(filename,"Alice","Phone",4.0,"2024-03-01");
    Update_menu_file(filename,"Alice","Tablet",4.5,"2024-05-01");

    assert(Search_menu_file(filename,"Tablet")==1);
    assert(Search_menu_file(filename,"Phone")==0);

    printf("Unit Test Update Passed\n");
}

void test_Search() {
    const char *filename = "test_search.csv";
    remove(filename);

    Add_menu_file(filename,"Alice","Phone",4.0,"2024-03-01");
    Add_menu_file(filename,"Bob","Laptop",5.0,"2024-04-01");

    assert(Search_menu_file(filename,"Alice")==1);
    assert(Search_menu_file(filename,"Laptop")==1);
    assert(Search_menu_file(filename,"NonExist")==0);

    printf("Unit Test Search Passed\n");
}

void test_EndToEnd() {
    const char *filename = "test_system.csv";
    remove(filename);

    Add_menu_file(filename,"Alice","Phone",4.0,"2024-03-01");
    Add_menu_file(filename,"Bob","Laptop",5.0,"2024-04-01");
    assert(Search_menu_file(filename,"Alice")==1);
    assert(Search_menu_file(filename,"Bob")==1);

    Update_menu_file(filename,"Alice","Tablet",4.5,"2024-05-01");
    assert(Search_menu_file(filename,"Tablet")==1);
    assert(Search_menu_file(filename,"Phone")==0);

    Delete_menu_file(filename,"Bob");
    assert(Search_menu_file(filename,"Bob")==0);

    printf("Full End-to-End System Test Passed!\n");
}

int main() {
    test_Add();
    test_Delete();
    test_Update();
    test_Search();
    test_EndToEnd();
    return 0;
}
