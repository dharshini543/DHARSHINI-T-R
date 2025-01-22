#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "user.h"
#include "enum.h"

FILE * UserFile = NULL;

void openUserFile()
{
    UserFile = fopen("Users.txt", "r+");
    if (!UserFile)
    {
        UserFile = fopen("Users.txt", "w+");
        if (!UserFile)
        {
            printf("Unable to open Users file\n");
        }
        else
        {
            printf("Users File opened successfully.\n");
        }
    }
    else
    {
        printf("Users File opened successfully.\n");
    }
}

void closeUserFile()
{
    if (UserFile != NULL)
    {
        fflush(UserFile);
        fclose(UserFile);
        printf("File closed successfully.\n");
    }
    else
    {
        printf("File pointer is NULL. No file to close.\n");
    }
}

void initializeUser(User *user, const char *username, const char *password, UserRole role)
{
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->isLoggedIn = 0;
    user->role = role;
}


User* loginUser(Userlist *userlist)
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\t ------- LOGIN -------\n");
    while(true)
    {

        printf("\tEnter username: ");
        if(scanf("%s", username) == 1 && strlen(username) < MAX_USERNAME_LENGTH)
        {
            break;
        }
        else
        {
            printf("Invalid Username,Enter valid Username\n");
        }
    }
    while(true)
    {

        printf("\tEnter Password: ");
        if(scanf("%s", password) == 1 && strlen(password) < MAX_USERNAME_LENGTH)
        {
            break;
        }
        else
        {
            printf("Invalid Password,Enter valid Password\n");
        }
    }

    for (int i = 0; i < userlist->userCount; i++)
    {
        if (strcmp(userlist->users[i].username, username) == 0 &&
            strcmp(userlist->users[i].password, password) == 0)
        {
            userlist->users[i].isLoggedIn = 1;
            return &userlist->users[i];
        }
    }
    return NULL;
}


int addUser(Userlist *userlist, const char *username, const char *password, UserRole role)
{
    if (userlist->userCount < MAX_USERS)
    {
        User *newUser = &userlist->users[userlist->userCount++];
        initializeUser(newUser, username, password, role);
        printf("User %s added successfully.\n", username);
        return Success;
    }
    else
    {
        printf("User limit reached. Cannot add more users.\n");
        return Failure;
    }
}


void deleteUser(Userlist *userlist, const char *username)
{
    for (int i = 0; i < userlist->userCount; i++)
    {
        if (strcmp(userlist->users[i].username, username) == 0)
        {
            for (int j = i; j < userlist->userCount - 1; j++)
            {
                userlist->users[j] = userlist->users[j + 1];
            }
            userlist->userCount--;
            printf("User %s deleted successfully.\n", username);
            return;
        }
    }
    printf("User %s not found.\n", username);
}

void displayUsers(Userlist *userlist)
{
    if (userlist->userCount > 0)
    {
        for (int i = 0; i < userlist->userCount; i++)
        {
            printf("User %d: %s %s\n", i + 1, userlist->users[i].username, userlist->users[i].password);
        }
    }
    else
    {
        printf("No users to display.\n");
    }
}


void saveUsersToFile(Userlist *userlist)
{
    FILE *file = fopen("Users.txt", "w");
    if (file != NULL)
    {
        for (int i = 0; i < userlist->userCount; i++)
        {
            fprintf(file, "%s\n", userlist->users[i].username);
            fprintf(file, "%s\n", userlist->users[i].password);
            fprintf(file, "%d\n", userlist->users[i].role);
        }
        fclose(file);
    }
    else
    {
        printf("Error saving users to file.\n");
    }
}

void loadUsersFromFile(Userlist *userlist)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        userlist->userCount = 0;

        while (fscanf(file, " %s %s  %d",
                      userlist->users[userlist->userCount].username,
                      userlist->users[userlist->userCount].password,
                      (int *)&userlist->users[userlist->userCount].role) == 3)
        {
            userlist->userCount++;
            if (userlist->userCount >= MAX_USERS)
            {
                fprintf(stderr, "Maximum user limit reached, some users may not be loaded.\n");
                break;
            }
        }

        fclose(file);
    }
}

void addFirstAdminUser(Userlist *userlist)
{
    if (userlist->userCount == 0)
    {
        char username[MAX_USERNAME_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        printf("Please create the first admin user:\n");
        while(true)
        {

            printf("\tEnter username: ");
            if(scanf("%s", userlist->users[0].username) == 1 && strlen(userlist->users[0].username) < MAX_USERNAME_LENGTH)
            {
                break;
            }
            else
            {
                printf("Invalid Username,Enter valid Username\n");
            }
        }
        while(true)
        {

            printf("\tEnter Password: ");
            if(scanf("%s", userlist->users[0].password) == 1 && strlen(userlist->users[0].password) < MAX_USERNAME_LENGTH)
            {
                break;
            }
            else
            {
                printf("Invalid Password,Enter valid Password\n");
            }
        }

        userlist->users[0].isLoggedIn = 0;
        userlist->users[0].role = ROLE_ADMIN;
        userlist->userCount = 1;
        printf("Admin user created successfully!\n");
    }
}

