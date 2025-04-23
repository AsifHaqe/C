#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct User {
    char username[50];
    char password[50];
    char email[50];
    char mobile[15];
    int callDuration;
    float billAmount;
    int callHistory[10];
    int historyCount;
    float paymentHistory[10];
    int paymentCount;
};

struct User users[20];
int userCount = 0;

int validatePassword(char *password) {
    int hasUpper = 0, hasDigit = 0, hasSpecial = 0;

    if (strlen(password) < 8) {
        return 0;
    }

    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (isupper(c)) {
            hasUpper = 1;
        } else if (isdigit(c)) {
            hasDigit = 1;
        } else if (!isalnum(c)) {
            hasSpecial = 1;
        }
    }

    return hasUpper && hasDigit && hasSpecial;
}

int validateMobile(char *mobile) {
    if (strlen(mobile) != 11) {
        return 0;
    }

    for (int i = 0; mobile[i] != '\0'; i++) {
        if (!isdigit(mobile[i])) {
            return 0;
        }
    }

    return 1;
}

int validateEmail(char *email) {
    int hasAt = 0, hasDot = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            hasAt = 1;
        } else if (email[i] == '.' && hasAt) {
            hasDot = 1;
        }
    }
    return hasAt && hasDot && strlen(email) > 5;
}

int isUsernameTaken(char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

int isEmailTaken(char *email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            return 1;
        }
    }
    return 0;
}

int isMobileTaken(char *mobile) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].mobile, mobile) == 0) {
            return 1;
        }
    }
    return 0;
}

void registration() {
    struct User newUser;

    printf("\n----------------------------------------\n");
    printf("          Registration\n");
    printf("----------------------------------------\n");
    printf("Enter username: ");
    scanf("%s", newUser.username);

    if (isUsernameTaken(newUser.username)) {
        printf("\n[ERROR] This username is already registered!\n");
        return;
    }

    do {
        printf("Enter email: ");
        scanf("%s", newUser.email);
        if (!validateEmail(newUser.email)) {
            printf("\n[ERROR] Invalid email! Must contain '@' and '.'\n");
        }
    } while (!validateEmail(newUser.email));

    if (isEmailTaken(newUser.email)) {
        printf("\n[ERROR] This email is already registered!\n");
        return;
    }

    do {
        printf("Enter mobile number: ");
        scanf("%s", newUser.mobile);

        if (!validateMobile(newUser.mobile)) {
            printf("\n[ERROR] Invalid mobile number! Must be exactly 11 digits.\n");
        }
    } while (!validateMobile(newUser.mobile));

    if (isMobileTaken(newUser.mobile)) {
        printf("\n[ERROR] This mobile number is already registered!\n");
        return;
    }

    int valid = 0;

    do {
        printf("Enter password: ");
        scanf("%s", newUser.password);

        if (validatePassword(newUser.password)) {
            valid = 1;
        } else {
            printf("\n[ERROR] Invalid password! Must have:\n");
            printf("  • 8+ characters\n  • 1 uppercase\n  • 1 number\n  • 1 special character\n");
        }
    } while (valid == 0);

    newUser.callDuration = 0;
    newUser.billAmount = 0.0;
    newUser.historyCount = 0;
    newUser.paymentCount = 0;

    users[userCount++] = newUser;
    printf("\nRegistration successful!\n");
    printf("----------------------------------------\n");
}

void login() {
    struct User oldUser;
    int attempts = 0;
    int index = -1;

    printf("\n----------------------------------------\n");
    printf("          User Login\n");
    printf("----------------------------------------\n");

    while (attempts < 3) {
        printf("Enter username: ");
        scanf("%s", oldUser.username);

        printf("Enter email: ");
        scanf("%s", oldUser.email);

        printf("Enter password: ");
        scanf("%s", oldUser.password);

        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, oldUser.username) == 0 &&
                strcmp(users[i].email, oldUser.email) == 0 &&
                strcmp(users[i].password, oldUser.password) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            break;
        } else {
            attempts++;
            if (attempts < 3) {
                printf("\n[ERROR] Invalid username, email, or password. %d attempts remaining.\n", 3 - attempts);
            }
        }
    }

    if (index == -1) {
        printf("\n[ERROR] Too many failed attempts. Account locked.\n");
        printf("----------------------------------------\n");
        return;
    }

    printf("\nLogin successful! Welcome, %s.\n", users[index].username);
    printf("Mobile number: %s\n", users[index].mobile);
    printf("----------------------------------------\n");

    int choice;
    do {
        printf("\n---------- User Menu ----------\n");
        printf("  1. Update Call Duration\n");
        printf("  2. Pay Bill\n");
        printf("  3. View Payment History\n");
        printf("  4. Logout\n");
        printf("-------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        while ((getchar()) != '\n');

        switch (choice) {
            case 1:
                printf("\n----------------------------------------\n");
                printf("          Update Call Duration\n");
                printf("----------------------------------------\n");
                printf("Enter call duration (in minutes): ");
                int newDuration;
                scanf("%d", &newDuration);
                if (newDuration < 0 || newDuration > 180) {
                    printf("\n[ERROR] Invalid duration! Must be between 0 and 180 minutes.\n");
                } else {
                    users[index].callDuration += newDuration;
                    if (users[index].historyCount < 10) {
                        users[index].callHistory[users[index].historyCount++] = newDuration;
                    }
                    users[index].billAmount = users[index].callDuration * 1.5;
                    printf("\nCall duration updated!\n");
                    printf("Total: %d minutes | New bill: ৳%.2f\n", users[index].callDuration, users[index].billAmount);
                }
                printf("----------------------------------------\n");
                break;
            case 2:
                printf("\n----------------------------------------\n");
                printf("          Pay Bill\n");
                printf("----------------------------------------\n");
                printf("Total payable amount: ৳%.2f\n", users[index].billAmount);
                printf("  1. Pay Full\n");
                printf("  2. Pay Half\n");
                printf("-------------------------------\n");
                printf("Enter choice: ");
                int payChoice;
                scanf("%d", &payChoice);
                while ((getchar()) != '\n');
                if (users[index].billAmount == 0.0) {
                    printf("\n[INFO] Bill already paid in its entirety!\n");
                } else {
                    switch (payChoice) {
                        case 1:
                            if (users[index].paymentCount < 10) {
                                users[index].paymentHistory[users[index].paymentCount++] = users[index].billAmount;
                            }
                            printf("\n=== Payment Receipt ===\n");
                            printf("Receipt ID: P%d\n", users[index].paymentCount);
                            printf("Amount Paid: ৳%.2f\n", users[index].billAmount);
                            users[index].billAmount = 0.0;
                            printf("Updated Bill: ৳%.2f\n", users[index].billAmount);
                            printf("=======================\n");
                            printf("Bill Successfully Paid\n");
                            break;
                        case 2:
                            if (users[index].paymentCount < 10) {
                                users[index].paymentHistory[users[index].paymentCount++] = users[index].billAmount / 2;
                            }
                            printf("\n=== Payment Receipt ===\n");
                            printf("Receipt ID: P%d\n", users[index].paymentCount);
                            printf("Amount Paid: ৳%.2f\n", users[index].billAmount / 2);
                            users[index].billAmount /= 2;
                            printf("Updated Bill: ৳%.2f\n", users[index].billAmount);
                            printf("=======================\n");
                            printf("Bill Successfully Paid\n");
                            break;
                        default:
                            printf("\n[ERROR] Invalid choice!\n");
                    }
                }
                printf("----------------------------------------\n");
                break;
            case 3:
                printf("\n----------------------------------------\n");
                printf("          Payment History\n");
                printf("----------------------------------------\n");
                for (int i = 0; i < users[index].paymentCount; i++) {
                    printf("Payment %d: ৳%.2f\n", i + 1, users[index].paymentHistory[i]);
                }
                if (users[index].paymentCount == 0) {
                    printf("[INFO] No payments made yet.\n");
                }
                printf("----------------------------------------\n");
                break;
            case 4:
                printf("\n----------------------------------------\n");
                printf("[INFO] Logging out...\n");
                printf("----------------------------------------\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice!\n");
        }
    } while (choice != 4);
}

void adminMenu() {
    char input[50];
    printf("\n----------------------------------------\n");
    printf("          Admin Login\n");
    printf("----------------------------------------\n");
    printf("Enter admin password: ");
    scanf("%s", input);
    if (strcmp(input, "Admin123!") != 0) {
        printf("\n[ERROR] Incorrect admin password!\n");
        printf("----------------------------------------\n");
        return;
    }
    int choice;
    do {
        printf("\n---------- Admin Menu ----------\n");
        printf("  1. View Bills\n");
        printf("  2. Delete User\n");
        printf("  3. View Payment Oversight\n");
        printf("  4. Exit Admin Mode\n");
        printf("-------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch (choice) {
            case 1:
                printf("\n----------------------------------------\n");
                printf("          Admin Panel - Bills\n");
                printf("----------------------------------------\n");
                printf("%-15s %-15s %-15s %-15s\n", "Username", "Mobile Number", "Call Duration", "Bill Amount");
                printf("------------------------------------------------------------\n");
                for (int i = 0; i < userCount; i++) {
                    printf("%-15s %-15s %-15d ৳%-15.2f\n",
                           users[i].username,
                           users[i].mobile,
                           users[i].callDuration,
                           users[i].billAmount);
                }
                printf("----------------------------------------\n");
                break;
            case 2:
                printf("\n----------------------------------------\n");
                printf("          Delete User\n");
                printf("----------------------------------------\n");
                printf("Enter username to delete: ");
                char delUser[50];
                scanf("%s", delUser);
                int found = 0;
                for (int i = 0; i < userCount; i++) {
                    if (strcmp(users[i].username, delUser) == 0) {
                        for (int j = i; j < userCount - 1; j++) {
                            users[j] = users[j + 1];
                        }
                        userCount--;
                        found = 1;
                        printf("\nUser deleted.\n");
                        break;
                    }
                }
                if (!found) {
                    printf("\n[ERROR] User not found.\n");
                }
                printf("----------------------------------------\n");
                break;
            case 3:
                printf("\n----------------------------------------\n");
                printf("          Payment Oversight\n");
                printf("----------------------------------------\n");
                float totalPayments = 0.0;
                for (int i = 0; i < userCount; i++) {
                    printf("User: %-15s\n", users[i].username);
                    printf("----------------------------------------\n");
                    printf("Payment History:\n");
                    for (int j = 0; j < users[i].paymentCount; j++) {
                        printf("  Payment %d: ৳%.2f\n", j + 1, users[i].paymentHistory[j]);
                        totalPayments += users[i].paymentHistory[j];
                    }
                    if (users[i].paymentCount == 0) {
                        printf("  [INFO] No payments made.\n");
                    }
                    printf("----------------------------------------\n");
                }
                printf("Total Payments Across All Users: ৳%.2f\n", totalPayments);
                printf("----------------------------------------\n");
                break;
            case 4:
                printf("\n----------------------------------------\n");
                printf("[INFO] Exiting admin mode...\n");
                printf("----------------------------------------\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice!\n");
        }
    } while (choice != 4);
}

int main() {
    int choice;

    do {
        printf("\n========================================\n");
        printf("      Telephone Billing System\n");
        printf("========================================\n");
        printf("  1. Registration\n");
        printf("  2. Login\n");
        printf("  3. Admin Menu\n");
        printf("  4. Exit\n");
        printf("========================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        while ((getchar()) != '\n');

        switch (choice) {
            case 1:
                registration();
                break;
            case 2:
                login();
                break;
            case 3:
                adminMenu();
                break;
            case 4:
                printf("\n========================================\n");
                printf("[INFO] Exiting...\n");
                printf("========================================\n");
                break;
            default:
                printf("\n[ERROR] Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}