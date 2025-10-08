#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

extern void Add_menu();
extern void Search_menu();
extern void Update_menu();
extern void Delete_menu();

void prepareTestData() {
    FILE *file = fopen("VendorManagement.csv", "w");
    fprintf(file, "Alice,Book,4.5,2024-10-09\n");
    fprintf(file, "Bob,Electronics,3.0,2024-05-01\n");
    fclose(file);
}

void checkVendorExists(const char *name, int expected) {
    FILE *file = fopen("VendorManagement.csv", "r");
    char line[256];
    int found = 0;
    while(fgets(line, sizeof(line), file)) {
        if(strstr(line, name)) { found = 1; break; }
    }
    fclose(file);
    assert(found == expected);
}

int main() {
    prepareTestData();
    checkVendorExists("Alice", 1);
    Add_menu();
    checkVendorExists("Charlie", 1);
    Update_menu();
    checkVendorExists("Bob", 1);
    Delete_menu();
    checkVendorExists("Alice", 0);
    printf("All E2E tests passed!\n");
    return 0;
}
