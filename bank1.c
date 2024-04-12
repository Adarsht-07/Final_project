#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int i;
struct bank
{
    int acno;
    char name[20];
    char pass[10];
    char qns[30];
    char ans[30];
    int bal;
    char status;
    char type;
};
struct tranction

{
    int acno;
    char trtype; // c for credit (deposit) d for debit(withdraw)
    int amt;
};
void createAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    p = fopen("ddaatt", "ab");
    if (p == NULL)
    {
        printf("Something Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        b1.acno = num + 1; // new acno is +1
        b1.status = 'a';
        printf("\nEnter Your Name:\t ");
        scanf("%s", b1.name);
        printf("\nEnter Balance:\t ");
        scanf("%d", &b1.bal);
        printf("\nEnter the Account Type(Saving/ Current):\t ");
        fflush(stdin);
        scanf("%c", &b1.type);
        printf("Enter Password: ");
        getPassword(b1.pass);

        printf("\nEnter Your Recover Question:\t ");
        fflush(stdin);
        gets(b1.qns);
        printf("\nEnter the Answer:\t ");
        fflush(stdin);
        gets(b1.ans);
        fwrite(&b1, sizeof(b1), 1, p); // b1 represents a single account that's why we used 1
        fclose(p);
        printf("\nAccount %d is created Succesfully", b1.acno);
    }
}
void clearScreen()
{
    system("cls"); // For Windows
}
void getPassword(char *password)
{
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 9)
    {
        if (ch == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (ch != '\b')
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}
void changeName()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END); // this moves the file pointer to the end of the line
        int po = ftell(p);     // this function gets the current position of the file pointer,which effectively gives the size of the file
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number: \t");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number. ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char nam[10];
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("Enter New Name:\t ");
                    scanf("%s", nam);
                    strcpy(b1.name, nam);
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("Your Name is Changed Succesfully");
                    fclose(p);
                }
            }
            else
            {
                printf("Password Do Not Match");
            }
        }
    }
}
void changePass()
{
    system("cls");
    struct bank b1;
    FILE *p;

    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number:\t ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number!!!");
            getch();
            return;
        }
        else
        {

            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);

            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    char pas[10];
                    printf("Enter the New Password: \t");
                    getPassword(pas);
                    strcpy(b1.pass, pas);
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("Password is Changed Successfully");
                    fclose(p);
                }
            }
            else
            {
                printf("Password Do not Match!!");
            }
        }
    }
}
void changeType()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number:\t ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char nam[10];
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    if (b1.type == 's')
                        b1.type = 'c';
                    else
                        b1.type = 's';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("Your Account Type is changed Successfully");
                    fclose(p);
                }
            }
            else
            {
                printf("Password Do not Match!!");
            }
        }
    }
}
void showDetails()
{
    system("cls");
    struct bank b1;

    FILE *p;
    p = fopen("ddaatt", "rb");
    if (p == NULL)
    {
        printf("Something Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number: \t");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number!!");
            getch();
            return;
        }
        else
        {
            char passs[10];

            printf("Enter Your Password:\t ");
            getPassword(passs);

            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            if (strcmp(b1.pass, passs) == 0)
            {
                if (b1.status == 'a')
                {
                    printf("Account Number=\t %d \n Name=\t %s \n Balance =\t %d \n Type =\t %c \n Recover Question =\t %s \n Answer =\t %s \n", b1.acno, b1.name, b1.bal, b1.type, b1.qns, b1.ans);
                }
                else
                {
                    printf("Your Account is Suspended!!! Please Contact the Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("Password Do Not Match");
            }
        }
    }
}
void depositeAccount()
{
    system("cls");
    struct bank b1;
    FILE *p, *q;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number:\t ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number!!");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("Enter Deposite Amount:\t ");
                    scanf("%d", &amt);
                    b1.bal = b1.bal + amt;
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("Amount Deposited Sucessfully");
                    q = fopen("trnc", "ab");
                    if (q == NULL)
                    {
                        printf("Something Went Wrong!!");
                        getch();
                        return;
                    }
                    else
                    {
                        struct tranction t1;
                        t1.acno = b1.acno;
                        t1.trtype = 'c';
                        t1.amt = amt;
                        fwrite(&t1, sizeof(t1), 1, q);
                    }
                    fclose(p);
                    fclose(q);
                }
                else
                {
                    printf("Your Account is Suspended!! Please Contact The Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("Password Do not Match");
            }
        }
    }
}
void withdrawAccount()
{
    system("cls");
    struct bank b1;
    FILE *p, *q;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number:\t");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number!!");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);
            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    printf("Enter the Withdrawl Amount:\t ");
                    scanf("%d", &amt);
                    if ((b1.type == 's' && (b1.bal - amt) >= 1000) || (b1.type == 'c' && (b1.bal - amt) >= 3000))
                    {
                        b1.bal = b1.bal - amt;
                        fseek(p, pos, SEEK_SET);
                        fwrite(&b1, sizeof(b1), 1, p);
                        printf("Amount has been Withdrawn from Your Account");
                        q = fopen("trnc", "ab");
                        if (q == NULL)
                        {
                            printf("Something Went Wrong!!");
                            getch();
                            return;
                        }
                        else
                        {
                            struct tranction t1;
                            t1.acno = b1.acno;
                            t1.trtype = 'd';
                            t1.amt = amt;
                            fwrite(&t1, sizeof(t1), 1, q);
                        }
                        fclose(q);
                        fclose(p);
                    }
                    else
                    {
                        printf("Insufficient Balance");
                        getch();
                        return;
                    }
                }
            
                else
                {
                    printf("Your  Account is Suspended!!! Please Contact the Bank!!!");
                    getch();
                    return;
                }
            }
            else
            {
                printf("Password Do not Match");
            }
        }
    }
}
void activateAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Something Went Wrong!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number: \t ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number!! ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'd')
                {
                    b1.status = 'a';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    fclose(p);
                    printf("Your Account is Successfully Activated");
                }
                else
                {
                    printf("Your Account is Already Activate");
                    getch();
                    return;
                }
            }
            else
            {
                printf("Password Do not Match");
            }
        }
    }
}
void deactivateAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Account Not Found!!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number: \t\n");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("Enter Your Password:\t");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {

                if (b1.status == 'a')
                {
                    b1.status = 'd';
                    fseek(p, pos, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    fclose(p);
                    printf("Your Account is Successfully Deactivated");
                }
                else
                {
                    printf("Your Account is Suspended!!! Please Contact the Bank");
                    getch();
                    return;
                }
            }
            else
            {
                printf("Password Do Not Match");
            }
        }
    }
}
void transferAccount()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Account Not Found !!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);
        system("cls");
        int to, frm;
        printf("Enter the Sender's Account Number: \t \n");
        scanf("%d", &frm);
        printf("Enter the Receiver's Account Number: \t \n");
        scanf("%d", &to);
        if (to > num || frm > num)
        {
            printf("Sender or Reciver Account Number is not valid");
            getch();
            exit(0);
        }
        else
        {
            int amt;
            printf("Enter the Transfer Amount");
            scanf("%d", &amt);
            int po = (frm - 1) * sizeof(b1);
            fseek(p, po, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            char opas[10];
            printf("Enter Your Password:\t ");
            getPassword(opas);

            if (strcmp(b1.pass, opas) == 0)
            {
                if ((b1.type == 's' && (b1.bal - amt >= 1000)) || (b1.type == 'c' && (b1.bal - amt >= 3000)))
                {
                    b1.bal = b1.bal - amt;
                    fseek(p, po, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);

                    int pos = (to - 1) * sizeof(b1);
                    fseek(p, pos, SEEK_SET);
                    fread(&b1, sizeof(b1), 1, p);
                    b1.bal = b1.bal + amt;
                    fseek(p, po, SEEK_SET);
                    fwrite(&b1, sizeof(b1), 1, p);
                    printf("Amount Transfered Successfully");
                    fclose(p);
                }
                else
                {
                    printf("Insufficient Amount!!");
                    getch();
                    return;
                }
            }
        }
    }
}
void forgotPass()
{
    system("cls");
    struct bank b1;
    FILE *p;
    int amt;
    p = fopen("ddaatt", "rb+");
    if (p == NULL)
    {
        printf("Account Not Found!!");
        getch();
        return;
    }
    else
    {
        fseek(p, 0, SEEK_END);
        int po = ftell(p);
        int num = po / sizeof(b1);

        int n;
        printf("Enter the Account Number you want to recover the password: \t ");
        scanf("%d", &n);

        if (n > num)
        {
            printf("Invalid Account Number ");
            getch();
            return;
        }
        else
        {
            int pos = (n - 1) * sizeof(b1);
            fseek(p, pos, SEEK_SET);
            fread(&b1, sizeof(b1), 1, p);
            printf("Give Answer to Your Recover Question: \t ");
            printf("%s\n", b1.qns);
            char an[30];
            fflush(stdin);
            gets(an);
            if (strcmp(b1.ans, an) == 0)
            {
                printf("Your Password is=\t %s\n", b1.pass);
                getch();
                return;
            }
            else
            {
                printf("Invalid Answer");
                getch();
                return;
            }
        }
    }
}
int main()
{
    char ch;
    int n;
    do
    {
        clearScreen();
        printf("\n===== Bank Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Show Details\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Activate Account\n");
        printf("6. Deactivate Account\n");
        printf("7. Transfer\n");
        printf("8. Change Name\n");
        printf("9. Change Type\n");
        printf("10. Change Password\n");
        printf("11. Forgot Password\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        fflush(stdin);

        if (n == 1)
            createAccount();
        else if (n == 2)
            showDetails();
        else if (n == 3)
            depositeAccount();
        else if (n == 4)
            withdrawAccount();
        else if (n == 5)
            activateAccount();
        else if (n == 6)
            deactivateAccount();
        else if (n == 7)
            transferAccount();
        else if (n == 8)
            changeName();
        else if (n == 9)
            changeType();
        else if (n == 10)
            changePass();
        else if (n == 11)
            forgotPass();
        else if (n == 12)
            printf("Thank you for visiting");
        else
        {
            printf("Invalid Choice");
            exit(0);
        }

        printf("\nDo you want to Continue (y for yes and n for no)?:\t ");
        fflush(stdin);
        scanf("%c", &ch);

    } while (ch != 'n' && ch != 'N');

    return 0;
}