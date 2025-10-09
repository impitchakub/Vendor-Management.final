#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void Add_menu_input(const char *SellerName, const char *ProductType, float Rating, const char *EvaluationDate, int confirm, const char *filename) {
    if (!confirm) return;
    FILE *file = fopen(filename, "a");
    if (!file) return;
    fprintf(file, "%s,%s,%.2f,%s\n", SellerName, ProductType, Rating, EvaluationDate);
    fclose(file);
}

void test_addData() {
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

    assert(count == 4);
    remove(file);
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

void test_Search_menu() {
    const char *file = "VendorManagement_test.csv";
    remove(file);

    Add_menu_input("TestSeller", "TestProduct", 3.0, "2024-01-01", 1, file);

    assert(Search_menu_input("TestSeller", file) == 1);
    assert(Search_menu_input("NonExist", file) == 0);

    remove(file);
}

void Update_menu_input(const char *oldName, const char *newName, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;
    FILE *temp = fopen("temp.csv", "w");
    if (!temp) { fclose(file); return; }

    char line[2000];
    while (fgets(line, sizeof(line), file)) {
        char name[100], product[100], date[100];
        float rate;
        sscanf(line, "%[^,],%[^,],%f,%s", name, product, &rate, date);
        if (strcmp(name, oldName) == 0) strcpy(name, newName);
        fprintf(temp, "%s,%s,%.2f,%s\n", name, product, rate, date);
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
}

void test_Update_menu() {
    const char *file = "VendorManagement_test.csv";
    remove(file);

    Add_menu_input("OldSeller", "ProductA", 2.0, "2024-01-01", 1, file);
    Update_menu_input("OldSeller", "NewSeller", file);

    assert(Search_menu_input("NewSeller", file) == 1);
    assert(Search_menu_input("OldSeller", file) == 0);

    remove(file);
}

void Delete_menu_input(const char *delName, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;
    FILE *temp = fopen("temp.csv", "w");
    if (!temp) { fclose(file); return; }

    char line[2000];
    while (fgets(line, sizeof(line), file)) {
        char name[100], product[100], date[100];
        float rate;
        sscanf(line, "%[^,],%[^,],%f,%s", name, product, &rate, date);
        if (strcmp(name, delName) != 0) fprintf(temp, "%s,%s,%.2f,%s\n", name, product, rate, date);
    }
    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
}

void test_Delete_menu() {
    const char *file = "VendorManagement_test.csv";
    remove(file);

    Add_menu_input("SellerToDelete", "ProductA", 2.5, "2024-01-01", 1, file);
    Delete_menu_input("SellerToDelete", file);

    assert(Search_menu_input("SellerToDelete", file) == 0);

    remove(file);
}

int main() {
    test_addData(); printf("test_addData passed\n");
    test_Search_menu();printf("test_Search_menu passed\n");
    test_Update_menu();printf("test_Update_menu passed\n");
    test_Delete_menu();printf("test_Delete_menu passed\n");
    return 0;
}

