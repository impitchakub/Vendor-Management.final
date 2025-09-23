#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char SellerName[];
char ProductType[];
float Rating;
char EvaluationDate[];
void menu()
    {
    int select;
    printf("please select the menu");
    printf("1.Add Seller");
    printf("2.Search menu");
    printf("3.Update menu");
    printf("4.Delete menu");
    scanf("%d",select);
    switch (select)
    {
        case 1:(Add_menu);
        break;
        case 2:(Search_menu);
        break;
        case 3:(Update_menu);
        break;
        case 4:(Delete_menu);
        break;
    }
    
    }      
void Add_menu()
    {
        printf("Seller Name");
        scanf("%s",SellerName);
        printf("Product Type");
        scanf("%s",ProductType);
        printf("Rating");
        scanf("%f",Rating);
        printf("Evaluation Date");
        scanf("%s",EvaluationDate);
        
    }
void Search_menu()
    {

    }
void Update_menu()
    {

    }
void Delete_menu()
    {

    }
int main()

{
    {
        FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","r");
        if (file == NULL)
        {
           printf("can't open file");
        }   
         fclose(file);
    }

        int Rating_table[15][4];
    {

    }


return 0;
}
