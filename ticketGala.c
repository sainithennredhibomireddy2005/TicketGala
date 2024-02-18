
#include <stdio.h>
#include <stdlib.h>
#define MAX_SEATS 50
typedef struct {
    int seat_number;
    int reserved;
} Seat;
typedef struct node {
    Seat seat;
    struct node* next;
} Node;
typedef struct {
    Node* front;
    Node* rear;
} Queue;
void init_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}
int is_queue_empty(Queue* queue) {
    return (queue->front == NULL && queue->rear == NULL);
}
void enqueue(Queue* queue, Seat seat) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->seat = seat;
    new_node->next = NULL;
    if (is_queue_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}
Seat dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        Seat empty_seat = {0, 0};
        return empty_seat;
    }
    Node* node_to_remove = queue->front;
    Seat seat_to_remove = node_to_remove->seat;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(node_to_remove);
    return seat_to_remove;
}
void display_seats(Queue* queue) {
    printf("Current seats status:\n");
    Node* current_node = queue->front;
    while (current_node != NULL) {
        printf("Seat %d: %s\n", current_node->seat.seat_number, current_node->seat.reserved ? "Reserved" : "Available");
        current_node = current_node->next;
    }
}
int main() {
    Queue queue;
    init_queue(&queue);
    int choice, seat_number;
    Seat seat;
    do {
        printf("\n1. Purchase ticket\n");
        printf("2. Reserve seat\n");
        printf("3. Cancel reservation\n");
        printf("4. Display current seats status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        Node* current_node = queue.front;
        switch (choice) {
            case 1:
                printf("Enter seat number: ");
                scanf("%d", &seat_number);
                if (seat_number < 1 || seat_number > MAX_SEATS) {
                    printf("Invalid seat number\n");
                    break;
                }
                seat.seat_number = seat_number;
                seat.reserved = 1;
                enqueue(&queue, seat);
                printf("Ticket purchased for seat %d\n", seat_number);
                break;
            case 2:
                printf("Enter seat number: ");
                scanf("%d", &seat_number);
                if (seat_number < 1 || seat_number > MAX_SEATS) {
                    printf("Invalid seat number\n");
                    break;
                }                
                while (current_node != NULL) {
                    if (current_node->seat.seat_number == seat_number) {
                        if (current_node->seat.reserved) {
                            printf("Seat already reserved\n");
                        } else {
                            current_node->seat.reserved = 1;
                            printf("Seat %d reserved\n", seat_number);
                        }
                        break;
                    }
                    current_node = current_node->next;
                }
                if (current_node == NULL) {
                    printf("Seat not found\n");
                }
                break;
            case 3:
                printf("Enter seat number: ");
                scanf("%d", &seat_number);
                if (seat_number < 1 || seat_number > MAX_SEATS) {
                    printf("Invalid seat number\n");
                    break;
                }
                while (current_node != NULL) {
                    if (current_node->seat.seat_number == seat_number) {
                        if (current_node->seat.reserved) {
                            current_node->seat.reserved = 0;
                            printf("Reservation cancelled for seat %d\n", seat_number);
                        } else {
                            printf("Seat not reserved\n");
                        }
                        break;
                    }
                    current_node = current_node->next;
                }
                if (current_node == NULL) {
                    printf("Seat not found\n");
                }
                break;
            case 4:
                display_seats(&queue);
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);
    Node* current_node = queue.front;
    while (current_node != NULL) {
        Node* node_to_remove = current_node;
        current_node = current_node->next;
        free(node_to_remove);
    }
    return 0;
}

