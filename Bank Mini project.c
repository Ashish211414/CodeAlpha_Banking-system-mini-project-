#include <stdio.h>
#include <stdlib.h>

struct Bank
{
    int accNo;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();

int main()
{
    int choice;

    while (1)
    {
        printf("\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            balanceEnquiry();
            break;
        case 5:
            printf("Thank You!\n");
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}

void createAccount()
{
    struct Bank b;
    FILE *fp;

    fp = fopen("account.dat", "wb");

    printf("Enter Account Number: ");
    scanf("%d", &b.accNo);

    printf("Enter Name: ");
    scanf("%s", b.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &b.balance);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}

void deposit()
{
    struct Bank b;
    FILE *fp;
    float amount;

    fp = fopen("account.dat", "rb+");

    if (fp == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    fread(&b, sizeof(b), 1, fp);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    b.balance += amount;

    rewind(fp);
    fwrite(&b, sizeof(b), 1, fp);

    fclose(fp);

    printf("Amount Deposited Successfully!\n");
}

void withdraw()
{
    struct Bank b;
    FILE *fp;
    float amount;

    fp = fopen("account.dat", "rb+");

    if (fp == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    fread(&b, sizeof(b), 1, fp);

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if (amount > b.balance)
    {
        printf("Insufficient Balance!\n");
    }
    else
    {
        b.balance -= amount;

        rewind(fp);
        fwrite(&b, sizeof(b), 1, fp);

        printf("Withdrawal Successful!\n");
    }

    fclose(fp);
}

void balanceEnquiry()
{
    struct Bank b;
    FILE *fp;

    fp = fopen("account.dat", "rb");

    if (fp == NULL)
    {
        printf("Account not found!\n");
        return;
    }

    fread(&b, sizeof(b), 1, fp);

    printf("\n------ ACCOUNT DETAILS ------\n");
    printf("Account Number : %d\n", b.accNo);
    printf("Name           : %s\n", b.name);
    printf("Balance        : %.2f\n", b.balance);

    fclose(fp);
}