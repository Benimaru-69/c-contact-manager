#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char name[50];
    char phone[20];
    char email[50];
};

void addContact() {
    struct Person p;
    FILE *fp = fopen("contacts.dat", "ab");
    if (fp == NULL) return;

    printf("\nEnter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", p.phone);
    printf("Enter Email: ");
    scanf(" %[^\n]", p.email);

    fwrite(&p, sizeof(struct Person), 1, fp);
    fclose(fp);
    printf("Contact saved successfully.\n");
}

void listContacts() {
    struct Person p;
    FILE *fp = fopen("contacts.dat", "rb");
    if (fp == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fread(&p, sizeof(struct Person), 1, fp)) {
        printf("Name : %s\n", p.name);
        printf("Phone: %s\n", p.phone);
        printf("Email: %s\n", p.email);
        printf("--------------------\n");
    }
    fclose(fp);
}

void searchContact() {
    char query[50];
    struct Person p;
    int found = 0;

    printf("\nEnter name to search: ");
    scanf(" %[^\n]", query);

    FILE *fp = fopen("contacts.dat", "rb");
    if (fp == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    while (fread(&p, sizeof(struct Person), 1, fp)) {
        if (strcmp(p.name, query) == 0) {
            printf("\nFound:\n");
            printf("Name : %s\n", p.name);
            printf("Phone: %s\n", p.phone);
            printf("Email: %s\n", p.email);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Contact not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Contact\n");
        printf("2. List Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                listContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
