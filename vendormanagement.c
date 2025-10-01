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
        scanf("%s",SellerName);//เก็บนามสกุลไม่ได้
        printf("Product Type : ");
        scanf("%s",ProductType);
        printf("Rating : ");
        scanf("%f",&Rating);
        printf("Evaluation Date (YYYY-MM-DD) : ");
        scanf("%s",EvaluationDate);   

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

        FILE*file=fopen("VendorManagement.csv","a");
        if (file == NULL)
        {
                printf("can't open file");   
                
        }  
        fprintf(file,"%s\n,%s\n,%.2f\n,%s\n" ,SellerName,ProductType,Rating,EvaluationDate);   
        fclose(file);

    }

void Search_menu()
    {
        char SearchName[100];
        printf("Please enter Seller name (John ) : ");
        scanf("%s",SearchName);

            FILE*file=fopen("VendorManagement.csv","r");
            char line[256];
            int find = 0;
            const char delimiter[] = ",";
            if (file == NULL)
            {
                printf("can't open file");
            }
            while (fgets(line,sizeof(line),file))
            {
                char*token;
                token=strtok(line,",");
                while (token != NULL) 
                {
                    printf("Seller Name: %s\n", token);
                    token = strtok(NULL,",");
                }
                char sName[100];
                strcpy(sName,token);
                if (strstr(sName,SellerName)!= NULL)
                {
                    printf("Seller: %s\nProduct Type: %s\nRating: %.2f\nDate: %s\n ",sName);
                }
                
                
            }
    

                /* 
                
                

                int found = strcasecmp(SearchName,SellerName);
                {
                    if (found==0)
                    {
                        printf("%s",token);
                    }
                    else(found != 0);
                    {
                        printf("can't found");
                    }
                    
                }*/
            

            fclose(file);

    }

   /* 
void Update_menu()
    {
            char keyword[100];
            printf("Enter Seller name to delete: ");
            scanf(" %s", keyword);
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
