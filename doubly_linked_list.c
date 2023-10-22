#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
 	struct Node *prev;
    int data;
    struct Node *next;
} node;

void printMenu();

void insertAtBegin(node **head, node **tail, int item);
void insertAfterElement(node **head, node **tail, int item, int after);
void insertBeforeElement(node **head, int item, int before);
void insertAtEnd(node **head, node **tail, int item);

void deleteFromBegin(node **head, node **tail);
void deleteAfterElement(node **head, node **tail, int after);
void deleteBeforeElement(node **head, int before);
void deleteFromEnd(node **head, node **tail);
void deleteList(node **head, node **tail);

void traverseInOrder(node *head);
void traverseInReverseOrder(node *tail);

node *searchInList(node *head, int key);

int main(void)
{
    int option, item, after, before, key;
    node *head = NULL, *tail = NULL;
	node *nd, *preloc, *curloc;

    while(1)
    {
        printMenu();
        scanf("%d", &option);
        switch(option)
        {
            case 1: printf("Enter item to insert at begining :");
                    scanf("%d", &item);
                    insertAtBegin(&head, &tail, item);
                    break;
            case 2: printf("Enter item to insert :");
                    scanf("%d", &item);
                    printf("Enter item after which one this element will be added :");
                    scanf("%d", &after);
                    insertAfterElement(&head, &tail, item, after);
                    break;
            case 3: printf("Enter item to insert :");
                    scanf("%d", &item);
                    printf("Enter item before which one this element will be added :");
                    scanf("%d", &before);
                    insertBeforeElement(&head, item, before);
                    break;
            case 4: printf("Enter item to insert at end :");
                    scanf("%d", &item);
                    insertAtEnd(&head, &tail, item);
                    break;
            case 5: deleteFromBegin(&head, &tail);
                    break;
            case 6: printf("A node will be deleted after an element. Enter the element :");
            		scanf("%d", &after);
					deleteAfterElement(&head, &tail, after);
                    break;
     		case 7: printf("A node will be deleted before an element. Enter the element :");
            		scanf("%d", &before);
					deleteBeforeElement(&head, before);
                    break;
            case 8: deleteFromEnd(&head, &tail);
                    break;
            case 9: deleteList(&head, &tail);
                    break;
            case 10: traverseInOrder(head);
            		printf("\n");
                    break;
            case 11: traverseInReverseOrder(tail);
                    printf("\n");
					break;
            case 12:printf("Enter key to search :");
                    scanf("%d", &key);
                    nd = searchInList(head, key);
                    if(nd == NULL)
                    	printf("Element not found\n");
                   	else
                   		printf("Element found\n");
                    break;
            case 0: exit(0);
            default: printf("Invalid option");
        }
    }
    return 0;
}

void printMenu()
{
    printf("Options\n");
    printf("    1: insert at begin\n");
    printf("    2: insert after an element\n");
    printf("    3: insert before an element\n");
    printf("    4: insert at end\n");
    printf("    5: delete from begining\n");
    printf("    6: delete after an element\n");
    printf("    7: delete before an element\n");
    printf("    8: delete from end\n");
    printf("    9: delete list\n");
    printf("    10: traverse in order\n");
    printf("    11: traverse in reverse order\n");
    printf("    12: search a key in list\n");
    printf("	Enter your choice:");
}

void insertAtBegin(node **head, node**tail, int item)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = item;
    newnode->prev = NULL;

    if(*head == NULL)
    {
    	newnode->next = NULL;
		*tail = newnode;
    }
    else
    {
    	newnode->next = *head;
    	(*head)->prev = newnode;
    }
    *head = newnode;
}

void insertAfterElement(node **head, node **tail, int item, int after)
{
    node *newnode;;
    node *curloc = searchInList(*head, after);
    if (curloc == (node *) NULL)
        return;

	newnode = (node *)malloc(sizeof(node));
    newnode->data = item;
    newnode->next = curloc->next;

	if(curloc->next != NULL)
	{
		(curloc->next)->prev = newnode;
    }
	else
	{
		*tail = newnode;
	}
	newnode->prev = curloc;
	curloc->next = newnode;
}

void insertBeforeElement(node **head, int item, int before)
{
	node *newnode, *curloc;
	curloc=searchInList(*head,before);
	if (curloc==NULL)
		return;
	newnode=(node *)malloc(sizeof(node));
	newnode->data=item;
	if(curloc->prev==NULL)
	{
		newnode->prev=NULL;
		curloc->prev=newnode;
		newnode->next=*head;
		*head=newnode;
	}
	else
	{
		newnode->prev=curloc->prev;
		newnode->next=curloc;
		(curloc->prev)->next=newnode;
		curloc->prev=newnode;
	}
}

void insertAtEnd(node **head, node **tail, int item)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = item;
    newnode->next=NULL;

    if(*head == NULL)
    {
    	*head = newnode;
    	newnode->prev = NULL;
    }
    else
    {
        newnode->prev = *tail;
		(*tail)->next = newnode;
    }
    *tail = newnode;
}

void deleteFromBegin(node **head, node **tail)
{
    node *temp;
    if(*head == NULL)
        return;
    temp = *head;
    if(*head == *tail)
    {
    	*head = *tail = NULL;
    }
   	else
    {
        (temp->next)->prev = NULL;
        *head = (*head)->next;
    }
    free(temp);
}

void deleteAfterElement(node **head, node **tail, int after)
{
    node *temp, *loc;
    loc = searchInList(*head, after);
    if (loc == (node *)NULL)
        return;

    if(loc->next == NULL)
    	printf("There is no element after %d", after);
   	else
	{
		temp = loc->next;
		loc->next = temp->next;
		if(temp->next == NULL)
			*tail = loc;
    }
    free(temp);
}

void deleteBeforeElement(node **head, int before)
{
	node *temp, *curloc;
	temp=*head;
	curloc=searchInList(*head,before);
	if (curloc==NULL)
		return;
	else if((curloc->prev)->prev==NULL)
	{
		temp=curloc->prev;
		curloc->prev=NULL;
		*head=curloc;
		free(temp);
	}
	else
	{
		temp=curloc->prev;
		curloc->prev=temp->prev;
		(temp->prev)->next=curloc;
		free(temp);
	}
}

void deleteFromEnd(node **head, node **tail)
{
    node *temp;
    if(*head == NULL)
        return;

	temp = *tail;
    if(*head == *tail)
    {
        *head = *tail = NULL;
    }
	else
    {
        (temp->prev)->next = NULL;
        *tail = temp->prev;
    }
    free(temp);
}

void deleteList(node **head, node **tail)
{
    node *temp;
    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}

void traverseInOrder(node *head)
{
    while(head != NULL)
    {
        printf(" %d ", head->data);
        head = head->next;
    }
}

void traverseInReverseOrder(node *tail)
{
    while(tail != NULL)
    {
        printf(" %d ", tail->data);
        tail = tail->prev;
    }
}

node * searchInList(node *head, int key)
{
    while((head != NULL) && (head->data != key))
        head = head->next;
    return head;
}

