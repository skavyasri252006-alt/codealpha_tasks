#include <stdio.h>
#include <stdlib.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

/* Function declarations */
void createAccount();
void deposit();
void withdraw();
void checkBalance();

int main() {
    int choice;

    while (1) {
        printf("\n--- BANK ACCOUNT MANAGEMENT SYSTEM ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* Create Account */
void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);
    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

/* Deposit Money */
void deposit() {
    struct Account acc;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            found = 1;
            printf("Deposit successful!\n");
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

/* Withdraw Money */
void withdraw() {
    struct Account acc;
    int accNo, found = 0;
    float amount;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawal successful!\n");
            } else {
                printf("Insufficient balance!\n");
            }
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

/* Balance Enquiry */
void checkBalance() {
    struct Account acc;
    int accNo, found = 0;
    FILE *fp = fopen("bank.dat", "rb");

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Account Holder: %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

