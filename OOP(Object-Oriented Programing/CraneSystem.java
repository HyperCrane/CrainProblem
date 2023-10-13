import java.util.*;

//Crane Position init
abstract class Position {
    int x;
    int y;

    Position() {
        this.x = 0;
        this.y = 0;
    }

    void moveX(int dx) { this.x += dx; }
    void moveY(int dy) { this.y += dy; } 
}

//motor status init
class Motor extends Position {
    boolean isActive;

    Motor() {
        isActive = false;
    }

    public void activate() {
        isActive = true;
    }

    public void deactivate() {
        isActive = false;
    }
}

//object position init
class Box extends Position {
    int z;

    Box() {
        z = 0;
    }
}

class CraneSystem {
    ArrayList<Motor> motors = new ArrayList<>();
    Box object = new Box();

    ArrayList<String> commands = new ArrayList<>();

    CraneSystem() {
        for(int i = 0; i < 8; i++) {
            motors.add(new Motor());
        }
    }


public static void main(String[] args) throws Exception {
    CraneSystem cs = new CraneSystem();
    Scanner scanner = new Scanner(System.in);

    while(true) {
        System.out.print("Enter a command: ");
        String command = scanner.nextLine();

        boolean flag = false;

        if(command.equals("right")) {
            cs.motors.get(1-1).activate();
            cs.motors.get(1-1).moveX(1);
            cs.commands.add(command);  
        }
        else if(command.equals("left")) {
                cs.motors.get(1-1).activate();
                cs.motors.get(1-1).moveX(-1);
                cs.commands.add(command);
        }
        else if(command.equals("down")) {
            cs.motors.get(2-1).activate();
            cs.motors.get(2-1).moveY(-1);
            cs.commands.add(command); 
        }
        else if(command.equals("up")) {
            cs.motors.get(2-1).activate();
            cs.motors.get(2-1).moveY(-1);
            cs.commands.add(command);
        }
        else if(command.equals("grab")) {
            boolean allStragiht = true;
            boolean allInactive = true;

            for (int i = 4; i <= 8; i ++) {
                if (cs.motors.get(i-1).isActive) {
                    allInactive = false;
                    break;
                }
            }

            if (allStragiht && allInactive) {
                for (int i = 4; i <= 8; i ++) {
                    cs.motors.get(i-1).activate();
                }

                cs.object.z += 10;
                cs.commands.add(command);
            } else {
                System.out.println("Cannot grab. All or some of the fingers are already bent or some motors are active.");
            }
        }
        else if(command.equals("letgo")) {
            boolean allActivate = true;

            for(int i = 4; i <= 8; i++) {
                if (!cs.motors.get(i-1).isActive) {
                    allActivate = false;
                    break;
                }
            }

            if(allActivate) {
                for(int i = 4; i <= 8; i++) {
                    cs.motors.get(i-1).deactivate();
                }

                cs.object.z -= 10;
                cs.commands.add(command);
            }
        
         else{
              System.out.println("Cannot let go. Some of the motors are not active.");
           }
        }

        else if (command.equals("exit")) {
            System.out.println("End the crane operation");
            break;
        } else {
            System.out.println("Invalid command! Please enter again");
            flag = true;
        }
    
        if (!flag) {
            System.out.println("command List: ");
            for (int i = 0; i < cs.commands.size(); i++) {
                System.out.println((i)+"."+cs.commands.get(i));
            }
            System.out.println("---------------");
        }
    }
}
}

