#include <stdio.h>
#include <string.h>

#define MAX 5

struct Passenger {
    int id;
    char name[20];
};

struct Passenger confirmed[MAX];
struct Passenger waiting[MAX];

int frontC = 0, rearC = -1;
int frontW = 0, rearW = -1;

void reserve() {
    struct Passenger p;
    int i;

    printf("Enter ID and Name: ");
    scanf("%d %s", &p.id, p.name);

    // Check in confirmed list
    for (i = frontC; i <= rearC; i++) {
        if (confirmed[i].id == p.id || strcmp(confirmed[i].name, p.name) == 0) {
            printf("Already Reserved\n");
            return;
        }
    }

    // Check in waiting list
    for (i = frontW; i <= rearW; i++) {
        if (waiting[i].id == p.id || strcmp(waiting[i].name, p.name) == 0) {
            printf("Already Reserved (Waiting List)\n");
            return;
        }
    }

    // Normal reservation
    if (rearC < MAX - 1) {
        confirmed[++rearC] = p;
        printf("Seat Confirmed\n");
    } else {
        waiting[++rearW] = p;
        printf("Added to Waiting List\n");
    }
}

void cancel() {
    if (frontC > rearC) {
        printf("No reservations\n");
        return;
    }

    printf("Cancelled: %s\n", confirmed[frontC].name);
    frontC++;

    if (frontW <= rearW) {
        confirmed[++rearC] = waiting[frontW++];
        printf("Waiting passenger moved to confirmed\n");
    }
}

void display() {
    int i;
    printf("\nConfirmed List:\n");
    for (i = frontC; i <= rearC; i++)
        printf("%d %s\n", confirmed[i].id, confirmed[i].name);

    printf("\nWaiting List:\n");
    for (i = frontW; i <= rearW; i++)
        printf("%d %s\n", waiting[i].id, waiting[i].name);
}

int main() {
    int choice;
    while (1) {
        printf("\n1.Reserve\n2.Cancel\n3.Display\n4.Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: reserve(); break;
            case 2: cancel(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice");
        }
    }
}