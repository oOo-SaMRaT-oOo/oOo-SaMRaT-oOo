#include<stdio.h>
#include<stdlib.h> /* Just for using exit() function */

struct user_structure
{
    int id,balance;
    char name[100];
}s[1000];

int user_count = 0; /* Initialization for the counting pointer */

void save_data(struct user_structure s[1000])
{
    FILE *fc;
    FILE *fp;
    fc = fopen("user_count.txt","w");
    if(fc == NULL)
    {
        printf("Error Saving data ... !");
        return;
    }
    fprintf(fc,"%d",user_count);
    fclose(fc);

    fp = fopen("user_data.txt","w");
    if(fp == NULL)
    {
        printf("Error saving data ... !");
        return;
    }
    for(int i = 0;i< user_count; i+= 1)
    {
        fprintf(fp,"%d %s %d\n",s[i].id,s[i].name,s[i].balance);
    }
    fclose(fp);
}

void load_data(struct user_structure s[1000])
{
    FILE *fp;
    FILE *fc;
    fc = fopen("user_count.txt","r");
    if(fc == NULL)
    {
        printf("Error loading data ... !");
        return;
    }

    fscanf(fc,"%d",&user_count);
    fclose(fc);

    fp = fopen("user_data.txt","r");
    if( fp == NULL)
    {
        printf("Error loading data ... !");
        return;
    }
    for(int i = 0;i< user_count;i+=1)
    {
        fscanf(fp,"%d %s %d\n",&s[i].id,&s[i].name,&s[i].balance);
    }
    fclose(fp);
}

void creating_account(struct user_structure s[1000])
{
    printf("Enter user id : ");
    scanf("%d",&s[user_count].id);
    printf("Enter name : ");
    getchar();
    scanf("%[^\n]s",s[user_count].name);
    printf("Enter initial balance {R.s} : ");
    scanf("%d",&s[user_count].balance);
    user_count += 1;
    save_data(s);
    printf("... Account Created Successfully ... ");
}

void depositing_money(struct user_structure s[1000])
{
    int cash;
    int id;
    printf("Enter user id : ");
    scanf("%d",&id);
    for(int i=0;i<user_count;i++)
    {
        if(s[i].id  == id)
        {
            printf("Enter amount to deposite {R.s} : ");
            scanf("%d",&cash);
            s[i].balance += cash;
            save_data(s);
            printf("\n... SUCCESSFULLY DEPOSITED ... ");
            return ;
        }
    }
    printf("Invalid user id ... !\n");
}

void checking_balance(struct user_structure s[1000])
{
    int id;
    printf("Enter user id : ");
    scanf("%d",&id);
    for(int i = 0;i<user_count;i++)
    {
        if(s[i].id == id)
        {
            printf("User : %s\n",s[i].name);
            printf("Balance : %d R.s\n",s[i].balance);
            return;
        }
    }
    printf("Invalid user id ... !");
}

void withdrawing_money(struct user_structure s[1000])
{
    int cash;
    int id;
    printf("Enter user id : ");
    scanf("%d",&id);
    for(int i=0;i<user_count;i++)
    {
        if(s[i].id  == id)
        {
            re:
            printf("Enter amount to withdraw {R.s} : ");
            scanf("%d",&cash);
            if (cash > s[i].balance)
            {
                printf("Not enought balance ... !\n");
                printf("Please re-enter ...\n");
                goto re;
            }
            s[i].balance -= cash;
            save_data(s);
            printf("\n... SUCCESSFULLY WITHDRAWED ... ");
            return ;
        }
    }
    printf("Invalid user id ... !\n");
    
}


void reset_system(struct user_structure s[1000]) 
{
    FILE *fc;
    fc = fopen("user_count.txt","w");
    fclose(fc);

    FILE *fp;
    fp = fopen("user_data.txt","w");
    fclose(fp);

    return;
}

int main()
{
    int choice,choice2;
    load_data(s);

    reset_system(s); /* Just for demonstration */

    /* I am using this reset function just for demonstration.
       In real practice We can remove this function call and use
       only When needed. */

    n:
    printf("\n\n... WELCOME TO PULCHOWK BANKING SYSTEM ...");
    printf("\n\n");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","NUMBER","TYPE OF ACTION");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","1.","Create Account");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","2.","Deposite Money");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","3.","Withdraw Money");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","4.","Check Balance");
    printf("+--------+-----------------+\n");
    printf("| %-6s | %-15s |\n","5.","EXIT SYSTEM");
    printf("+--------+-----------------+\n");
    printf("\nPlease Enter your choice : ");
    label:
    scanf("%d",&choice);
    if (choice <1 || choice >5)
    {
        printf("\nPlease Re-enter choice : ");
        goto label;
    }
    switch (choice)
    {
    case 1:
        creating_account(s);
        break;
    
    case 2:
        depositing_money(s);
        break;
    
    case 3:
        withdrawing_money(s);
        break;

    case 4:
        checking_balance(s);
        break;

    case 5:
        printf("\nExiting the system ... \n\n");
        printf("... Thank You DEAR USER ... \n\n");
        exit(0);
        break;
    
    default:
        printf("... Invalid Choice ... !");
        goto label;
    }
    printf("\n\nWant to perform other action or exit ?\n");
    printf("1. Don't Exit\n2. Yes Exit\n");
    l:
    printf("Enter choice -> ");
    scanf("%d",&choice2);
    if (choice2 != 1 && choice2 !=2)
    {
        printf("Invalid choice ... !\n");
        goto l;
    }
    if (choice2 == 1)
    {
        printf("\n\n .............................................................. \n\n");
        goto n;
    }
    else
    {
        printf("\nExiting the system ... \n\n");
        printf("... Thank You DEAR USER ... \n\n");
        exit(0);
    }
    return 0;
}

