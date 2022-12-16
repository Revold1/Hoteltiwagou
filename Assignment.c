#include <stdio.h>
#include <strings.h>

typedef struct Rooms
{
    int roomID;
    int status;
    char customerName[20];
} Rooms;

void listOccupiedRooms(struct Rooms *hotel);
void assignRoom(struct Rooms *hotel);
void removeRoom(struct Rooms *hotel);
void findCustomer(struct Rooms *hotel);

int empty(struct Rooms *hotel);
int full(struct Rooms *hotel);


int main()
{
    //initialise variable and struct
    int choice;
    Rooms hotel[5] = {{1, 0,},{2, 0,},{3, 0,},{4, 0,},{5, 0,}};

    //Menu
    printf("NTU HOTEL ROOM RESERVATION PROGRAM:\n");
    printf("1: listOccupiedRooms()\n");
    printf("2: assignRoom()\n");
    printf("3: removeRoom()\n");
    printf("4: findCustomer()\n");
    printf("5: quit\n");
    do {
        printf("Enter your choice:\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            // LIST OF OCCUPIED ROOM
            listOccupiedRooms(hotel);
            break;
        case 2:
            // ASSIGN ROOM
            assignRoom(hotel);
            break;
        case 3:
            // REMOVE ROOM
            removeRoom(hotel);
            break;
        case 4:
            // FIND CUSTOMER
            findCustomer(hotel);
            break;
        default:
            break;
        }
    } while (choice != 5); // QUIT
    return 0;
}

int full(struct Rooms *hotel)
{
    int i;
    for (i=0; i < 5; i++)
    {
        if (hotel[i].status == 0)
            return 0;
    }
    return 1;
}


int empty(struct Rooms *hotel)
{
    int i;
    for (i=0; i < 5; i++)
    {
        if (hotel[i].status == 1)
            return 0;
    }
    return 1;
}


void listOccupiedRooms(struct Rooms *hotel)
{
    int i;

    printf("listOccupiedRooms():\n");
    if (empty(hotel))
    {
        printf("The hotel is empty\n");
        return;
    }
    for (i = 0; i < 5; i++)
    {
        if (hotel[i].status == 1)
        {
            printf("roomID: %d\n", hotel[i].roomID);
            printf("customer name: %s\n", hotel[i].customerName);
        }
    }
}
void assignRoom(struct Rooms *hotel)
{
    int i, room_ID;
    char customer_name[20], *p;
    printf("assignRoom():\n");

    // checking for full occupancy
    if (full(hotel))
    {
        printf("The hotel is full\n");
        return;
    }
    while (1)
    {
        printf("Enter a roomID between 1 and 5:\n");
        scanf("%d", &room_ID);

        //loop back to Enter roomID for invalid ID
        if (room_ID < 1 || room_ID > 5)
            continue;
        
        //check if roomID entered is already occupied
        if (hotel[room_ID - 1].status == 1)
        {
            printf("Occupied! Enter another roomID\n");
            continue;
        }

        // assigning room to customer
        else
        {
            hotel[room_ID - 1].status = 1;
            printf("Enter customer name:\n");
            scanf("\n");
            fgets(customer_name, 20, stdin);
            if ( p=strchr(customer_name,'\n') )
                *p = '\0';
            strcpy(hotel[room_ID - 1].customerName, customer_name);
            printf("The room has been assigned successfully\n");
            break;
        }
    }
        
}
void removeRoom(struct Rooms *hotel)
{
    int i, room_ID;
    printf("removeRoom():\n");

    //check for empty hotel
    if (empty(hotel))
    {
        printf("All the rooms are empty\n");
        return;
    }

    while (1)
    {
        printf("Enter a roomID between 1 and 5:\n");
        scanf("%d", &room_ID);

        //loop back to Enter roomID for invalid ID
        if (room_ID < 1 || room_ID > 5)
            continue;

        //check for empty room
        if (hotel[room_ID -1].status == 0)
        {
            printf("Empty! Enter another roomID for removal\n");
            continue;
        }

        //break out of loop for valid ID
        else
            break;
    }
    hotel[room_ID-1].status = 0;
    memset(hotel[room_ID-1].customerName, 0 , 20);
    printf("Removal is successful\n");

}
void findCustomer(struct Rooms *hotel)
{
    int i;
    char target_name[20];
    char *p;

    printf("findCustomer:\n");
    printf("Enter customer name:\n");
    scanf("\n");
    fgets(target_name, 20, stdin);
    if ((p=strchr(target_name, '\n')))
        *p = '\0';
    
    for (i = 0; i < 5; i++)
    {
        if(hotel[i].status == 1 && strcasecmp(target_name, hotel[i].customerName) == 0)
        {
            printf("The target customer name is found\n");
            printf("roomID: %d\n", hotel[i+1].roomID);
            printf("customer name: %s\n", hotel[i+1].customerName);
            return;
        }
    }
    printf("The target customer name is not found\n");
}