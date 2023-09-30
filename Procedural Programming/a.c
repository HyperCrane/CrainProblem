#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    if (motors[id-1].status == 0) {
        printf("Motor %d: active\n", id);
        motors[id-1].status = 1;
    }
}

void deactivate_motor(int id) {
    if (motors[id-1].status == 1) {
        printf("Motor %d: inactive\n", id);
        motors[id-1].status = 0;
    }
}

void right() {
    activate_motor(1); // x axis motor
}

void left() { 
   activate_motor(2); // y axis motor 
}

void up() { 
   deactivate_motor(3); // claw up/down motor 
}

void down() { 
   activate_motor(3); // claw up/down motor  
}
   
void grab() {   
   for (int i=4;i<=8;i++){  
       activate_motor(i); // fingers' motors
   }   
}   

void let_go(){
     int flag=0;
     for (int i=4;i<=8;i++){  
         if(motors[i-1] .status == true){
             flag=1 ;
             break ;
         }
     }    
     
     if(flag==0){
         printf("I already opened my finger\n");
         return ;
     }

     for(int i=4;i<=8;i++){
         deactivate_motor(i);
     }     
}   

int main(void) {
    char command[20];
    initialize_motors();

    while(1) {
        printf("Enter a command: ");
        fgets(command, 20, stdin);
        // remove newline character
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "right") == 0) {
            right();
        } else if (strcmp(command, "down") == 0) {
            down();
        } else if (strcmp(command, "grab") == 0) {
            grab();
        } else if (strcmp(command, "up") == 0) {
            up();
	} else if (strcmp(command,"left")==0){
	    left();
	} else if(strcmp(command,"let go")==0){
	    let_go();
	} else if(strcmp(command,"exit")==0){
	     break ;
	} else{
	    printf("Invalid command! Please enter again.");
	}
   }

    return 0;
}
