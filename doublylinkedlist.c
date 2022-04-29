#include<stdio.h>
#include<stdlib.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define GREEN_BACKGROUND   "\x1b[42;1m"

struct node
{
    struct node* prev;
    int data;
    struct node* next;
};

//insertion algorithms
void add_first(struct node** head, int data);
void add(struct node** head, int data, int index);
void add_last(struct node**, int data);

//deletion algorithms
void remove_first(struct node** head);
void remove_at(struct node**, int index);
void remove_last(struct node** head);

//traversal algorithms
void display(const struct node* head);
int count_nodes(const struct node* head);

//search algorithm
int find(const struct node* head, int data);

int main()
{
    struct node* head = NULL;
    int i, data, index, nodes;

    do
    {
        printf(CYAN "================MENU===============\n");
        printf(" 1. Add at the beginning\n");
        printf(" 2. Add at your choice of index\n");
        printf(" 3. Add at the end\n");
        printf(" 4. Find a value\n");
        printf(" 5. Display the list\n");
        printf(" 6. Get the number of nodes\n");
        printf(" 7. Delete the first node.\n");
        printf(" 8. Delete the node of your choice.\n");
        printf(" 9. Delete the last node.\n");
        printf("10. Exit" RESET);

        printf(BLUE "\n\nEnter the number corresponding to the operation: " RESET);
        scanf("%d", &i);
        printf("\n");
        switch(i)
        {
            case 1:
                printf(YELLOW "Enter the data to be inserted: " RESET);
                scanf("%d", &data);
                add_first(&head, data);
                printf(GREEN "The data has been inserted successfully.\n\n" RESET);
                break;
            case 2:
                printf(YELLOW "Enter the data to be inserted: " RESET);
                scanf("%d", &data);
                printf(YELLOW "Enter the index: " RESET);
                scanf("%d", &index);
                add(&head, data, index);
                printf(GREEN "The data has been inserted successfully.\n\n" RESET);
                break;
            case 3:
                printf(YELLOW "Enter the data to be inserted: " RESET);
                scanf("%d", &data);
                add_last(&head, data);
                printf(GREEN "The data has been inserted successfully.\n\n" RESET);
                break;
            case 4:
                printf(YELLOW "Enter the data to be searched: " RESET);
                scanf("%d", &data);
                int index = find(head, data);
                if(index < 0)
                    printf(RED "\nSorry! The data could not be found.\n\n" RESET);
                else
                    printf(CYAN "The data found at index %d\n\n" RESET, index);
                break;
            case 5:
                display(head);
                printf("\n\n");
                break;
            case 6:
                nodes = count_nodes(head);
                printf(MAGENTA "The list has %d nodes\n\n" RESET, nodes);
                break;
            case 7:
                remove_first(&head);
                printf(GREEN "The node has been removed successfully.\n\n" RESET);
                break;
            case 8:
                printf(YELLOW "Enter the index of the node: " RESET);
                scanf("%d", &index);
                remove_at(&head, index);
                printf(GREEN "\nThe node has been removed successfully.\n\n" RESET);
                break;
            case 9:
                remove_last(&head);
                printf(GREEN "The node has been removed successfully.\n\n" RESET);
                break;
            case 10:
                printf(MAGENTA "Have a good day! Bye!\n\n" RESET);
                break;
            default:
                printf(RED "You must choose an option. from given the list above\n\n" RESET);
        }
    }while(i != 10);

    return 0;
}

//insertion algorithms
void add_first(struct node** head, int data)
{
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *head;
    new_node->prev = NULL;

    if((*head) == NULL)
        (*head) = new_node;
    else
    {
        (*head)->prev = new_node;
        (*head) = new_node;
    }
}

void add(struct node** head, int data, int index)
{
    int size = count_nodes(*head);
    if(index == 0)
        add_first(head, data);
    else if(index >= size)
        add_last(head, data);
    else {
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->data = data;

        struct node* temp = *head;

        int i = 1;
        for(i = 1;i < index;i++)
            temp = temp->next;

        new_node->next = temp->next;
        new_node->prev = temp;

        temp->next->prev = new_node;
        temp->next = new_node;
    }
}

void add_last(struct node** head, int data)
{
    if((*head) == NULL)
        add_first(head, data);
    else
    {
        struct node* new_node = (struct node*) malloc(sizeof(struct node));
        new_node->data = data;

        //go to the last node
        struct node* temp = *head;
        while(temp->next != NULL)
            temp = temp->next;

        new_node->next = NULL;
        new_node->prev = temp;
        temp->next = new_node;
    }
}

//traversal algorithms
void display(const struct node* head)
{
    while(head != NULL)
    {
        printf(BLUE "%d " RESET, head->data);
        head = head->next;
    }
    printf("\n");
}

int count_nodes(const struct node* head)
{
    int count = 0;
    while(head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

//search algorithm
int find(const struct node* head, int data)
{
    int index = 0;
    while(head != NULL)
    {
        if(head->data == data)
            return index;
        else
        {
            head = head->next;
            index += 1;
        }
    }

    return -1;
}

//deletion algorithms
void remove_first(struct node** head)
{
    if((*head) == NULL)
        printf(RED "The list is already empty.\n" RESET);
    else
    {
        struct node* temp = (*head);

        (*head) = temp->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

void remove_at(struct node** head, int index)
{
    int size = count_nodes(*head);
    if((*head) == NULL)
        printf(RED "The list is already empty.\n" RESET);
    else if(index >= size)
    {
        printf(RED "The index is out of bound.\n" RESET);
        return;
    }
    else if(index == 0)
        remove_first(head);
    else if(index == size - 1)
        remove_last(head);
    else
    {
        struct node* temp = (*head);

        while(index--)
            temp = temp->next;

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}

void remove_last(struct node** head)
{
    if((*head) == NULL)
        printf(RED "The list is already empty.\n" RESET);
    else if((*head)->next == NULL)
        (*head) = NULL;
    else
    {
        struct node* temp = (*head);
        while(temp->next != NULL)
            temp = temp->next;

        temp->prev->next = NULL;
        free(temp);
    }
}