#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "utils.c"

struct User
{
    char username[30];
    char password[30];

    union ActiveState
    {
        struct inactive
        {
            int type;
        } inactive;
        
        struct active
        {
            int type;
        } active;
    } activeState;
};

#define MaxUsers 30
int userCount = 2;

struct User users[MaxUsers] = {
    {"admin", "admin" },
    {"username", "password"}
};

void Login();
void Register();
int Search(int tpye, char* data);

int main()
{
    users[0].activeState.active.type = 1;
    users[1].activeState.inactive.type = 0;

    // printf("user[0].type: %d\n", users[0].activeState.active.type);
    // printf("user[0].type: %d\n", users[0].activeState.inactive.type);

    // printf("user[1].type: %d\n", users[1].activeState.active.type);
    // printf("user[1].type: %d\n", users[1].activeState.inactive.type);

    char resgisterMsg[18];
    sprintf(resgisterMsg, "Register(%d/%d)", userCount, MaxUsers);

    while (true)
    {
        
        printf("Users:\n");
        for (int i = 0; i < userCount; i++)
        {
            int active = users[i].activeState.active.type == 1;
            printf("%d - user: [%s, %s, %s]\n", i, users[i].username, users[i].password, active == 1 ? "active" : "inactive");
        }
        printf("\n");

        printf("1 - Login\n2 - %s\n3 - Exit\nChoose an option: \n", resgisterMsg);

        int option;
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            Login();
            break;
        case 2:
            if (userCount == MaxUsers)
            {
                printf("Reached maximum size of users can't register!");
                break;
            }

            Register();
            sprintf(resgisterMsg, "Register(%d/%d)", userCount, MaxUsers);
            break;
        case 3: break;
        default:
            printf("Invalid option!\n");
            break;
        }

        if (option == 3) break;

    }

    printf("\n");
    return 0;
}

void Login()
{
    char username[30];
    char password[30];

    while (true)
    {
        printf("Enter your username: ");
        scanf("%s", username);

        int index = Search(0, username);
        if (index == -1)
        {
            printf("Username doesn't exist!\n");
            continue;
        }

        if (users[index].activeState.inactive.type == 0) {
            printf("This user is inactive!\n");
            continue;
        }

        printf("Enter your password: ");
        scanf("%s", password);

        if (strcmp(users[index].password, password) != 0)
        {
            printf("Incorrect password!\n");
            continue;
        }

        break;
    }

    printf("Login Success!\n");
}

void Register()
{
    char username[30];
    char password[30];
    char passwordConfirmation[30];
    int active;

    while (true)
    {
        printf("Enter your username: ");
        scanf("%s", username);

        int index = Search(0, username);
        if (index != -1)
        {
            printf("Username already exists!\n");
            continue;
        }

        printf("Enter your password: ");
        scanf("%s", password);

        if (Search(1, password) != -1)
        {
            printf("Password already exists!\n");
            continue;
        }

        printf("Confirm your password: ");
        scanf("%s", passwordConfirmation);

        if (!strcmp(password, passwordConfirmation) == 0)
        {
            printf("Passwords not matching!\n");
            continue;
        }

        printf("Mark as active ? answer: (1-yes / 0-no): ");
        scanf("%d", &active);

        break;
    }

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    
    // Setting the active state.
    if (active == 1) {
        users[userCount].activeState.active.type = 1;
    } else {
        users[userCount].activeState.inactive.type = 0;
    }

    userCount++;

    for (int i = 0; i < userCount; i++)
    {
        printf("%d - user: [%s, %s]\n", i, users[i].username, users[i].password);
    }

    printf("Register Successfull! (%s, %s), length: %d\n", users[userCount].username, users[userCount].password, userCount);
}

int Search(int type, char *data)
{
    for (int i = 0; i < userCount; i++)
    {
        switch (type)
        {
        case 0:
            if (strcmp(users[i].username, data) == 0)
                return i;
            break;
        case 1:
            if (strcmp(users[i].password, data) == 0)
                return i;
            break;
        }
    }

    return -1;
}
