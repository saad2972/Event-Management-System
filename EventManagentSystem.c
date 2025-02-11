#include <stdio.h>


struct Event {
    int eventID;
    char eventName[100];
    char date[20];
    char time[20];
    int isCancelled;
};


void addEvent();
void displayUpcomingEvents();
void cancelEvent();
void viewPastEvents();
void loadEventsFromFile();
void saveEventsToFile();
void printEvent(const struct Event *event);


struct Event events[100];
int numEvents = 0;

int main() {
    int choice;


    loadEventsFromFile();

    do {

        printf("\nEvent Scheduling System\n");
        printf("1. Add Event\n");
        printf("2. Display Upcoming Events\n");
        printf("3. Cancel Event\n");
        printf("4. View Past Events\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEvent();
                break;
            case 2:
                displayUpcomingEvents();
                break;
            case 3:
                cancelEvent();
                break;
            case 4:
                viewPastEvents();
                break;
            case 5:

                saveEventsToFile();
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void addEvent() {

    if (numEvents < 100) {
        struct Event newEvent;


        printf("Enter Event Name: ");
        scanf("%s", newEvent.eventName);
        printf("Enter Date (DD/MM/YYYY): ");
        scanf("%s", newEvent.date);
        printf("Enter Time (HH:MM AM/PM): ");
        scanf("%s", newEvent.time);


        newEvent.eventID = numEvents + 1;
        newEvent.isCancelled = 0;


        events[numEvents++] = newEvent;

        printf("Event added successfully!\n");
    } else {
        printf("Cannot add more events. Maximum limit reached.\n");
    }
}

void displayUpcomingEvents() {
    printf("\nUpcoming Events:\n");

    int i;
    for (i = 0; i < numEvents; i++) {
        if (!events[i].isCancelled) {
            printEvent(&events[i]);
        }
    }
}

void cancelEvent() {
    int eventID;

    printf("Enter Event ID to cancel: ");
    scanf("%d", &eventID);

    int i;
    for (i = 0; i < numEvents; i++) {
        if (events[i].eventID == eventID) {
            events[i].isCancelled = 1;
            printf("Event cancelled successfully!\n");
            return;
        }
    }

    printf("Event not found.\n");
}

void viewPastEvents() {
    printf("\nPast Events:\n");
    int i;

    for (i = 0; i < numEvents; i++) {
        if (events[i].isCancelled) {
            printEvent(&events[i]);
        }
    }
}

void loadEventsFromFile() {
    FILE *file = fopen("event_records.txt", "r");
    if (file != NULL) {

        while (fread(&events[numEvents], sizeof(struct Event), 1, file) == 1) {
            numEvents++;
        }

        fclose(file);
    }
}

void saveEventsToFile() {
    FILE *file = fopen("event_records.txt", "w");
    if (file != NULL) {

        fwrite(events, sizeof(struct Event), numEvents, file);

        fclose(file);
    }
}

void printEvent(const struct Event *event) {
    printf("---------------------------\n");
    printf("Event ID: %d\n", event->eventID);
    printf("Event Name: %s\n", event->eventName);
    printf("Date: %s\n", event->date);
    printf("Time: %s\n", event->time);
    printf("Status: %s\n", event->isCancelled ? "Cancelled" : "Active");
    printf("---------------------------\n");
}
