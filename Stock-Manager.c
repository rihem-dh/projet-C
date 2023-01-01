#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct prduct{
  int id;
  char productname[50];
  int quantity ;
  char date[12];
}p;

 FILE *fp;


 void ajouter(){
     char mydate[12];
     time_t t= time(NULL);
     struct tm tm = *localtime(&t);
     sprintf(mydate,"%02d/%02d/%d ",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
     strcpy(p.date,mydate);

     fp=fopen("product.txt","ab");

     printf("Enter product id :");
     scanf("%d",&p.id);

     printf("Enter product name : ");
     fflush(stdin);
     gets(p.productname);

     printf("Enter product quantity : ");
     fflush(stdin);
     scanf("%d",&p.quantity);
     printf("\nProduct Added Successfully");

     fwrite(&p,sizeof(p),1,fp);
     fclose(fp);
 }
void afficher(){ 
 	int id;
 	int f=0;
 	fp=fopen("product.txt","rb");
	printf("Enter product id to display :");
	scanf("%i",&id);
	 while (fread(&p,sizeof(p),1,fp) == 1){
        if(id==p.id){
            f=1;
            	printf("<== Product  ==>\n\n");
   				printf("%-10s %-20s %-20s  %s \n","Id","Product Name","Quantity","Date");
   				printf("--------------------------------------------------------------------------------\n");
                printf("%-10d %-20s %-20d  %s\n",p.id,p.productname,p.quantity,p.date);
                break;


        }

    }
	
    if(f==0){
    	printf("\n\n Product Not Found !");
	}
 	
    
    fclose(fp);}
 void modifier(){
    int id,f;
    printf("Update Product \n");
    printf("Enter product id to update : ");
    scanf("%d",&id);

    FILE *ft;

    fp=fopen("product.txt","rb+");

    while (fread(&p,sizeof(p),1,fp) == 1){
        if(id==p.id){
            f=1;
                printf("Enter new product name : ");
                fflush(stdin);
                gets(p.productname);


                printf("Enter new product quantity : ");
                fflush(stdin);
                scanf("%d",&p.quantity);

                fseek(fp,-sizeof(p),1);
                fwrite(&p,sizeof(p),1,fp);
                fclose(fp);
                break;


        }

    }

 }
 void del(int id){
  int f=0 ;

  FILE *ft;

  fp=fopen("product.txt","rb");
  ft=fopen("temp.txt","wb");
  while (fread(&p,sizeof(p),1,fp) == 1){
    if(id == p.id){
        f=1;
    }else{
       fwrite(&p,sizeof(p),1,ft);
    }
  }
  fclose(fp);
  fclose(ft);
  remove("product.txt");
  rename("temp.txt","product.txt");


}
void supprimer(){
   int id,f;
   printf(" Delete Product \n");
   printf("Enter product id to delete : ");
   scanf("%d",&id);

   FILE *ft;

   fp=fopen("product.txt","rb");

    while (fread(&p,sizeof(p),1,fp) == 1){
        if(id == p.id){
            f=1;
            fclose(fp);
            break;
        }

    }
  if(f==1){
    printf("\n Product Deleted Successefully ");
    del(id);
  }else{
      printf("\n\n Product Not Found !");
  }

}


void rechercher(){
   int id,f=0;
   system("cls");
   printf(" search Product\n");
   printf("Enter product id to buy : ");
   scanf("%d",&id);

   fp=fopen("product.txt","rb+");

   while (fread(&p,sizeof(p),1,fp) == 1){
    if(id == p.id){
        f=1;
        p.quantity=p.quantity-1;
        fseek(fp,-sizeof(p),1);
        fwrite(&p,sizeof(p),1,fp);
        fclose(fp);
        if(p.quantity ==0){
            del(p.id);
        }
        break;
    }
   }
   if(f==1){
    printf("\nProduct Bought Successefully");
   }else{
       printf("\n\n Product Not Found !");
   }


}

 int main(){

 int ch;

 while(1){
    system("cls");
    printf("<== Store Management System ==>\n\n");
    printf("1.Add Products \n");
    printf("2.Dispaly Products \n");
    printf("3.Update Product \n");
    printf("4.Delete Product \n");
    printf("5.search Product to buy\n");
    printf("0.Exit \n");
    printf("Enter your choice : ");
    scanf("%d",&ch);
    switch(ch){
    case 0:
        exit(0);

    case 1:
        ajouter();
        break;
    case 2:
        afficher();
        break;
    case 3:
        modifier();
        break;
    case 4:
        supprimer();
        break;
   case 5:
        rechercher();
        break;
   default :
      printf("Invalid choice\n");
    }
    printf("\n Press any key to continue");
    getch();
    }
    return 0;
 }
