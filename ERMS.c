#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

// Prototypes
void AppendInList(void);
void DisplayRecords(void);
void SearchEmployee(int);
void UpdateSalary(int, float);
void DeleteEmployee(int);
void freespace(void);
void filehandling(void);

struct nodeType
{
    int empID;
    char empName[30];
    float empSalary;
    struct nodeType *next; // stores address of next node that will dynamically allocate
    // use struct also with variable name because compiler undertsands builtin data types like struct, int..
};

struct nodeType *head = NULL;
// creates an empty LL.

int main()
{
    int n;
    int id;
    float salary;
    char ch;

    printf("Enter Number of employees\n> ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        AppendInList();
    } // Used to store N employess in a list

    // Display complete List
    DisplayRecords();

    // Search EMP by ID
    printf("Enter ID of the employee to see his/her record\n> ");
    scanf("%d", &id);
    SearchEmployee(id);

    // Update Salary by EMP by ID
    printf("Enter ID of the employee for updating his/her salary\n> ");
    scanf("%d", &id);
    printf("Enter new salary of the person\n> ");
    scanf("%f", &salary);
    UpdateSalary(id, salary);

    // Delete EMP by ID
    printf("Enter ID of the employee for removing him/her from a list\n> ");
    scanf("%d", &id);
    DeleteEmployee(id);

    // Display complete List after deleting a person
    DisplayRecords();

    // Stores all data in the file.
    filehandling();

    // Function used to free dynamically allocated memory.
    printf("Press enter to free the allocated space....");
    ch = getche();
    freespace();

    return 0;
}

void AppendInList(void)
{
    struct nodeType *newNode = malloc(sizeof(struct nodeType));
    // Dynamically allocate memory for new node and stores the address of the chunk.

    // Creating complete node with its values
    printf("Enter ID of employee\n> ");
    scanf("%d", &newNode->empID); // As newNode stores the address of the structure therefore for giving value to the specific data type of struct use this(->) method.
    printf("Enter Name of employee\n> ");
    scanf(" %[^\n]", newNode->empName);
    getchar();
    printf("Enter Salary of employee\n> ");
    scanf("%f", &newNode->empSalary);
    newNode->next = NULL;

    // Inserting Node in a list
    if (head == NULL)
    {
        head = newNode;
        printf("Person is added in the list successfully\n");
        return;
    }
    else
    {
        struct nodeType *temp = head; // *temp is a variable and used to store just addresses of the list.temp = head, means head next = temp next
        while (temp->next != NULL)
        {
            temp = temp->next;
            // next itself is nothing as it is not declared globally, but temp -> next is what we want
        }
        temp->next = newNode;
        printf("Person is added in the list successfully\n");
    }
}
void DisplayRecords(void)
{
    printf("EMPLOYEE RECORDS\n");
    printf("===================\n");
    printf("%-5s| %-15s| %-10s\n", "ID", "Name", "Salary");
    printf("--------------------------------------------------------------------------------------------\n");
    struct nodeType *temp = head; // means head -> next = temp -> next
    while (temp != NULL)
    {
        printf("%-5d| ", temp->empID);
        printf("%-15s| ", temp->empName);
        printf("%-10.2f\n", temp->empSalary);
        temp = temp->next;
    }
    printf("--------------------------------------------------------------------------------------------\n");
}
void SearchEmployee(int ID)
{
    struct nodeType *temp = head; // means head -> next = temp -> next
    while (temp->empID != ID && temp->next != NULL)
    {
        temp = temp->next;
    }

    if (temp->empID == ID)
    {
        printf("Record of employee with %d ID\n", ID);
        printf("=====================================\n");
        printf("%-5s| %-15s| %-10s\n", "ID", "Name", "Salary");
        printf("--------------------------------------------------------------------------------------------\n");
        printf("%-5d| ", temp->empID);
        printf("%-15s| ", temp->empName);
        printf("%-10.2f\n", temp->empSalary);
        printf("--------------------------------------------------------------------------------------------\n");
    }
    else
    {
        printf("ID not found in the list\n");
    }
}
void UpdateSalary(int ID, float salary)
{
    struct nodeType *temp = head; // means head -> next = temp -> next
    while (temp->empID != ID && temp->next != NULL)
    {
        temp = temp->next;
    }
    // means we have successfully find the node which contains the given ID. Now update the salary in that node

    if (temp->empID == ID)
    {
        temp->empSalary = salary;
        printf("Salary Updated Successfuly!\n");
    }
    else
    {
        printf("ID not found in the list\n");
    }
}
void DeleteEmployee(int ID)
{
    struct nodeType *temp = head;
    struct nodeType *previous = NULL;

    while (temp != NULL)
    {
        if (temp->empID == ID)
        {
            if (previous == NULL) // special case (deleting head)
            {
                head = temp->next; // Previously head stores address of 1st node(chunk). Now head stores NULL.
            }
            else
            {
                previous->next = temp->next;
            }

            free(temp); // If special case match then it stores address of 1st node(chunk) else it stores address of node of given id.
            printf("The record of the person Successfuly removes from the list\n");
            return;
        }

        // Iterating over all nodes to check given ID
        previous = temp;
        temp = temp->next;
    }
    printf("The given ID is not found in the list\n");
}
void filehandling(void)
{
    FILE *fp = fopen("ERMS.txt", "a");
    if (fp == NULL)
    {
        printf("Error Occured in opening file\n");
        return;
    }

    fprintf(fp, "EMPLOYEE RECORDS\n");
    fprintf(fp, "===================\n");
    fprintf(fp, "%-5s| %-15s| %-10s\n", "ID", "Name", "Salary");
    fprintf(fp, "--------------------------------------------------------------------------------------------\n");
    struct nodeType *temp = head; // means head -> next = temp -> next
    while (temp != NULL)
    {
        fprintf(fp, "%-5d| ", temp->empID);
        fprintf(fp, "%-15s| ", temp->empName);
        fprintf(fp, "%-10.2f\n", temp->empSalary);
        temp = temp->next;
    }
    fprintf(fp, "--------------------------------------------------------------------------------------------\n");
}
void freespace(void)
{
    struct nodeType *temp;

    while (head != NULL)
    {
        temp = head;       // stores address of 1st node then 2nd and so on
        head = head->next; // stores address of 2nd node then 3rd and so on
        free(temp);        // Free 1st node then 2nd and so on
    }
    printf("All the nodes memory is freed successfully\n");
}
