#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMMANDS 100
#define MAX_COMMAND_LENGTH 30

char commands[MAX_COMMANDS][MAX_COMMAND_LENGTH];
int top = 0;

typedef struct {
    int x;
    int y;
    int grabed; // 0: Not Grabed, etc: Grabed
} Object;

typedef struct {
    int id;
    int status; // 0: inactive, 1: active
} Motor;

typedef struct {
    int x;
    int y;
} MotorVector;

Object object;
Motor motors[8];
MotorVector motorVector;

/**
 * Object
*/
void initialize_object() {
    object.x = -1;
    object.y = 0;
    object.grabed = 0;
}

void print_object_status() {
    if(object.grabed) printf("Block:\nI'm here!! x:%4d, y:%4d\nI'm caughted\n\n", object.x, object.y);
    else printf("Block:\nI'm here!! x:%4d, y:%4d\nBut I'm not caughted\n\n", object.x, object.y);
}

void caughted_object() {
    object.grabed = 1;
}
void free_object() {
    object.grabed = 0;
}

int is_caughted() {
    return object.grabed;
}

/**
 * Motor Vector
*/
void print_motor_status() {
    printf("\nMotor Vector - x:%4d y:%4d\n\n", motorVector.x, motorVector.y);
}

void move_motor(const int dx, const int dy) {
    if(is_caughted()) {
        object.x += dx; object.y += dy; 
    }

    motorVector.x += dx; motorVector.y += dy;
}

/**
 * Motors
*/
void initialize_motors() {
    for (int i = 0; i < 8; i++) {
        motors[i].id = i + 1;
        motors[i].status = 0;
    }
    motorVector.x = 0; motorVector.y = 0;
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

    move_motor(1, 0);
}
//activate_motor(1)아닌가 ? 
void left() {
    activate_motor(1); // y-axis motor 

    move_motor(-1, 0);
}


void up() {
    activate_motor(2); // claw up/down motor 0->1

    move_motor(0, 1);
}

void down() {
    deactivate_motor(2); // claw up/down motor 1->0
    
    move_motor(0, -1);
}

void hand_up(){
    activate_motor(3); // 0->1

    move_motor(0,1);
}

void hand_down(){
    deactivate_motor(3); // 1->0

    move_motor(0,-1);
}

void grab() {
    for (int i = 4; i <= 8; i++) {
        activate_motor(i); // fingers' motors
    }

    if(motorVector.x == object.x && motorVector.y == object.y) {
        caughted_object();
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

    free_object();
}

void list_commands() {
    printf("Command List:\n");
    for (int i = 0; i < top; i++) {
        printf("%d. %s\n", i + 1, commands[i]);
    }
}

int main(void) {
    char command[20];
    initialize_object();
    initialize_motors();

    while (1) {
        printf("Enter a command: ");
        fgets(command, 20, stdin);
        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        bool flag = false;

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

        else if (strcmp(command, "handup") == 0) {
            hand_up();
            strncpy(commands[top++], command, MAX_COMMAND_LENGTH);
        }
        else if (strcmp(command, "handdown") == 0) {
            hand_down();
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
            flag = true;
        }

        // Invalid한 Command에서는 상태를 print하지 않음
        if(!flag) {
            list_commands();
            print_motor_status();
            print_object_status();
        }
        printf("———————\n");
    }

    return 0;
}