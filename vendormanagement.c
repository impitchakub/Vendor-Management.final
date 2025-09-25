#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char SellerName[100];
char ProductType[100];
float Rating;
char EvaluationDate[100];

      
void Add_menu()
    {       
        {
            FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","a");
            if (file == NULL)
            {
                printf("can't open file");   
            }  
            fprintf(file,"%s,%s,%f,%s" ,SellerName,ProductType,Rating,EvaluationDate);   
            fclose(file);
        }  

        char collect[10];
        printf("Seller Name : ");
        scanf("%s",SellerName);
        printf("Product Type : ");
        scanf("%s",ProductType);
        printf("Rating : ");
        scanf("%f",&Rating);
        printf("Evaluation Date : (DD/MM/YYYY)");
        scanf("%s",EvaluationDate);
  
    }
    /*  printf("save or not (y,n)");
        scanf("%s",collect);
        //function save yes or no
        if (collect== 'y')
        {
            Rating_table();
        }
        else
        {

        }
        int Rating_table[15][4];
    {
        
    }

    }
*/
/*void Search_menu()
    {
        {
            FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","r");
            if (file == NULL)
            {
                printf("can't open file");
            }   
                fclose(file);
        }     
    }
void Update_menu()
    {
        {
            FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","r");
            if (file == NULL)
            {
                printf("can't open file");
            }   
                fclose(file);
        }  
    }
void Delete_menu()
    {
        {
            FILE*file=fopen("ระบบจัดการข้อมูลการประเมินผู้ขาย.csv","r");
            if (file == NULL)
            {
                printf("can't open file");
            }   
                fclose(file);
        }  
    }

    //unit test 2 function
    //endtoend
    */
void menu()
    {

    int select;
    printf("please select the menu\n");
    printf("1.Add Seller\n");
    printf("2.Search menu\n");
    printf("3.Update menu\n");
    printf("4.Delete menu\n");
    scanf("%d",&select);
    switch (select)
    {
        case 1:Add_menu();
        break;
        //case 2:(Search_menu);
       // break;
       // case 3:(Update_menu);
       // break;
        //case 4:(Delete_menu);
       // break;
    }
    
    }
int main()
{
    menu();
    
return 0;

}
