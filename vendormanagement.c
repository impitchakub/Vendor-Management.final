#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char SellerName[100];
char ProductType[100];
float Rating;
char EvaluationDate[100];

      
void Add_menu()
    {      
        
        printf("Seller Name : ");
        scanf(" %[^\n]",SellerName);
        printf("Product Type : ");
        scanf("%s",ProductType);
        printf("Rating : ");
        scanf("%f",&Rating);
        printf("Evaluation Date (YYYY-MM-DD) : ");
        scanf("%s",EvaluationDate);   

      

        FILE*file=fopen("VendorManagement.csv","a");
        if (file == NULL)
        {
                printf("can't open file");   
                
        }  
        fprintf(file,"%s,%s,%.2f,%s\n" ,SellerName,ProductType,Rating,EvaluationDate);   
        fclose(file);

    }

void Search_menu()
{
    {
        char line[256];
        char search[100];
        int found = 0, count = 0;
        FILE *file = fopen("VendorManagement.csv", "r");
        printf("Search data: ");
        scanf("%s", search);

        while(fgets(line, sizeof(line), file) != NULL)
        {
                if(strstr(line, search))
            {
                    if(count < 1)
                {
                    printf("+----------+------------+-------------+----------------+\n");
                    printf("| Name     | Product Type   | Rating | Evaluation date  |\n");
                    printf("+----------+------------+-------------+----------------+\n");
                }
            
            char *SellerName = strtok(line, ",");
            char *ProductType = strtok(NULL, ",");
            char *Rating = strtok(NULL, ",");
            char *EvaluationDate = strtok(NULL, "\n");

            printf("| %-8s | %-14s | %-6s | %-16s | %-3d |\n", SellerName, ProductType, Rating, EvaluationDate);
            found = 1;   
            printf("+----------+------------+-------------+----------------+\n");
            }
            count++;
        }
        if(found != 1) printf("Data is not found.\n");
        fclose(file);
    }

}

            fclose(file);

    

  
void Update_menu()
{
    int count = 0, i = 1;
    char updateStatus;
    FILE *file = fopen("VendorManagement.csv", "r");
    int num;
    char line[256];
    printf("Update data");
    while(fgets(line, sizeof(line), file) != NULL)
    {
        if(count < 1){
            printf("+----------+------------+-------------+----------------+\n");
            printf("| Seller Name  | Product Type   | Rating | Evaluation date  |\n");
            printf("+----------+------------+-------------+----------------+\n");
        }
            
        char *SellerName = strtok(line, ",");
        char *ProductType = strtok(NULL, ",");
        char *Rating = strtok(NULL, ",");
        char *EvaluationDate = strtok(NULL, "\n");

        printf("| %-8s | %-14s | %-6s | %-16s | %-3d |\n", SellerName, ProductType, Rating, EvaluationDate, i);
        printf("+----------+------------+-------------+----------------+\n");
        count++;
        i++;
    }
}
 /* 
void Delete_menu()
{
        char line[256];
        char delete[100];
        int found = 0, count = 0;
        FILE *file = fopen("VendorManagement.csv", "r");
        FILE *temp = fopen("VendorManagement.csv", "w");
        printf("Search data: ");
        scanf("%s", search); 
        FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","r");
        if (file == NULL)
        {
            printf("can't open file");
        }   
            fclose(file);
          
}

    //unit test 2 function
    //endtoend
    */
void menu()
{

    int select;
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
            //case 4:(Delete_menu);
            // break;

        }
      
}
int main()
{
    menu();
    return 0;
}
