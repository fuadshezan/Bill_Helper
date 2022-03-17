#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//function to generate bills
void generateBillHeader(char name[50], char date[50]){
    printf("\n\n");

        printf("\t   Scope Restaurent");
        printf("\n\t----------------------");
        printf("\nDate: %s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("------------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n------------------------------------------");
        printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty * price);
    printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float vat=0.1*netTotal,grandTotal=netTotal + vat;
    printf("------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%%\t\t\t%.2f",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nVat @10%%\t\t\t%.2f",vat);
    //printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n------------------------------------------\n");
}

int main()
{
    //printf("Hello world!\n");
    float total;
    int opt,n,check;
    struct orders ord;
    struct orders order;
    char saveBill='y';
    char name[50];
    FILE *fp;
    //dashboard
    while(1){
            printf("\t=============Scope Restaurent===============");
            printf("\n\nPlease select your prefered option: ");
            printf("\n\n1.Generate Invoice");
            printf("\n2.Show all Invoice");
            printf("\n3.Search Invoice");
            printf("\n4.Clear all the Invoice");
            printf("\n5.Exit");
            printf("\n\n");

            printf("\n\nYour Choice: ");
            scanf("%d",&opt);
            fgetc(stdin);
            check=-1;

            switch(opt){
                case 1:
                    system("cls");
                    printf("\nPlease enter the name of the customer:");
                    fgets(ord.customer,50,stdin);
                    ord.customer[strlen(ord.customer)-1]=0;
                    strcpy(ord.date,__DATE__);
                    printf("\nPlease enter the number of items:\t");
                    scanf("%d",&n);
                    ord.numOfItems=n;
                    for(int i=0;i<n;i++){
                        fgetc(stdin);
                        printf("\n\n");
                        printf("Please enter the item %d:\t",i+1);
                        fgets(ord.itm[i].item,20,stdin);
                        ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                        printf("Please enter the quantity:\t");
                        scanf("%d",&ord.itm[i].qty);
                        printf("Please enter the unit price:\t");
                        scanf("%f",&ord.itm[i].price);
                        total+=ord.itm[i].qty * ord.itm[i].price;
                    }
                    generateBillHeader(ord.customer,ord.date);
                    for(int i=0;i<ord.numOfItems;i++){
                        generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                    }
                    generateBillFooter(total);

                    printf("\nDo you want to save the invoice?[y/n]: ");
                    scanf("%s",&saveBill);

                    if(saveBill=='y'){
                        fp=fopen("RestaurantBill.dat","a+");
                        fwrite(&ord,sizeof(struct orders),1,fp);
                        if(fwrite!=0){
                            printf("\nSuccecfully Saved\n\n");
                        }
                        else{
                            printf("\nError saving!\n\n");
                        }
                        fclose(fp);
                    }
                    else{
                        printf("\n\tInvoice not saved.\n\n");
                    }
                break;
            case 2:

                system("cls");
                fp=fopen("RestaurantBill.dat","r");
                printf("\n *****Your Previous Invoices *****\n");
                while(fread(&order,sizeof(struct orders),1,fp)){
                        check=0;
                        float tot=0;
                        generateBillHeader(order.customer,order.date);
                        for(int i=0;i<order.numOfItems;i++){

                            generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                            tot+=order.itm[i].qty*order.itm[i].price;
                        }
                        generateBillFooter(tot);
                    }
                if(check==-1){
                    printf("\n-----Invoice storage is Empty.------\n\n");
                }
                fclose(fp);
                break;

            case 3:
                system("cls");
                printf("Enter the name of the customer:\t");
                //fgetc(stdin);
                fgets(name,50,stdin);
                name[strlen(name)-1]=0;
                fp=fopen("RestaurantBill.dat","r");
                printf("\n *****Invoice of %s*****\n",name);
                while(fread(&order,sizeof(struct orders),1,fp)){
                        if (!strcmp(order.customer,name)){
                            float tot=0;
                            generateBillHeader(order.customer,order.date);
                            for(int i=0;i<order.numOfItems;i++){
                                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                                tot+=order.itm[i].qty*order.itm[i].price;
                            }
                            generateBillFooter(tot);
                        }
                        else{
                            printf("Sorry the invoice for does not exists.\n\n");
                        }

                }
                fclose(fp);
                break;
            case 4:
                    fclose(fopen("RestaurantBill.dat", "w"));
                    printf("\n *****Cleared all Invoices*****\n\n");
                    break;

            case 5:
                printf("\n\t\t*****Bye Bye*****\n\n");
                exit(0);
                break;
            default:
                printf("Sorry invalid option\n\n");
                break;
            }
        }
    return 0;

}
