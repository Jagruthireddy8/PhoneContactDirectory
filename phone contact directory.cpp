#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Contact
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    struct Contact *next;
};

struct Contact *head = NULL;

// Function to create a new contact node
struct Contact* createContact(char name[], char phone[], char email[]) {
    struct Contact *newContact = (struct Contact*)malloc(sizeof(struct Contact));
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->email, email);
    newContact->next = NULL;
    return newContact;
}

// Add new contact
void addContact() {
    char name[50], phone[15], email[50];
    printf("\nEnter Name: ");
    scanf("%s", name);
    printf("Enter Phone: ");
    scanf("%s", phone);
    printf("Enter Email: ");
    scanf("%s", email);

    struct Contact *newContact = createContact(name, phone, email);

    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newContact;
    }

    printf("\nContact added successfully!\n");
}

// Display all contacts
void displayContacts() {
    struct Contact *temp = head;
    if (temp == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    while (temp != NULL) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n\n", temp->name, temp->phone, temp->email);
        temp = temp->next;
    }
}

// Search contact by name
void searchContact() {
    char name[50];
    printf("\nEnter name to search: ");
    scanf("%s", name);

    struct Contact *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("\nContact Found!\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n", temp->name, temp->phone, temp->email);
            return;
        }
        temp = temp->next;
    }
    printf("\nContact not found.\n");
}

// Delete contact by name
void deleteContact() {
    char name[50];
    printf("\nEnter name to delete: ");
    scanf("%s", name);

    struct Contact *temp = head, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nContact not found.\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("\nContact deleted successfully.\n");
}

// Save contacts to file
void saveToFile() {
    FILE *fp = fopen("contacts.txt", "w");
    struct Contact *temp = head;

    while (temp != NULL) {
        fprintf(fp, "%s %s %s\n", temp->name, temp->phone, temp->email);
        temp = temp->next;
    }

    fclose(fp);
    printf("\nContacts saved to file successfully!\n");
}

// Load contacts from file
void loadFromFile() {
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL)
        return;

    char name[50], phone[15], email[50];
    while (fscanf(fp, "%s %s %s", name, phone, email) != EOF) {
        struct Contact *newContact = createContact(name, phone, email);
        if (head == NULL)
            head = newContact;
        else {
            struct Contact *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newContact;
        }
    }

    fclose(fp);
}

// Main Function
int main() {
    int choice;
    loadFromFile();

    do {
        printf("\n===== PHONE CONTACT DIRECTORY =====\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: displayContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: saveToFile(); printf("\nExiting program...\n"); break;
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
