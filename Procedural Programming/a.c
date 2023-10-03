#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMMANDS 100
#define MAX_COMMAND_LENGTH 30

char commands[MAX_COMMANDS][MAX_COMMAND_LENGTH];
int top = 0;

typedef struct {
    int id;
    int status; // 0: inactive, 1: active
} Motor;

Motor motors[8];

void initialize_motors() {
    for (int i = 0; i < 8; i++) {
        motors[i].id = i + 1;
        motors[i].status = 0;
    }
}

void activate_motor(int id) {
    if (motors[id - 1].status == 0) {
        printf("Motor %d: active\n", id);
        motors[id - 1].status = 1;
    }
}

void deactivate_motor(int id) {
    if (motors[id - 1].status == 1) {
        printf("Motor %d: inactive\n", id);
        motors[id - 1].status = 0;
    }
}

void right() {
    activate_motor(1); // x-axis motor
}

void left() {
    activate_motor(2); // y-axis motor 
}

void up() {
    deactivate_motor(3); // claw up/down motor 
}

void down() {
    activate_motor(3); // claw up/down motor  
}

void grab() {
    for (int i = 4; i <= 8; i++) {
        activate_motor(i); // fingers' motors
    }
}

void let_go() {
    int flag = 0;
    for (int i = 4; i <= 8; i++) {
        if (motors[i - 1].status == 1) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        printf("I already opened my finger\n");
        return;
    }

    for (int i = 4; i <= 8; i++) {
        deactivate_motor(i);
    }
}

void list_commands() {
    printf("Command List:\n");
    for (int i = 0; i < top; i++) {
        printf("%d. %s\n", i + 1, commands[i]);
    }
}

int main(void) {
    char command[20];
    initialize_motors();

    while (1) {
        printf("Enter a command: ");
        fgets(command, 20, stdin);
        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "right") == 0) {
            right();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "down") == 0) {
            down();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "grab") == 0) {
            grab();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "up") == 0) {
            up();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "left") == 0) {
            left();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "let go") == 0) {
            let_go();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("Invalid command! Please enter again.");
        }list_commands();
    }

    return 0;
}
