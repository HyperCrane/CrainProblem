#include <iostream>
#include <vector>
#include <string>

class Position {
private:
    int x, y;

public:
    Position() : x(0), y(0) {}

    void moveX(int dx) { x += dx; }
    void moveY(int dy) { y += dy; }
    int getX() const { return x; }
    int getY() const { return y; }
};

class Motor : public Position {
private:
    bool isActive;

public:
    Motor() : isActive(false) {}

    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
    bool getIsActive() const { return isActive; }
};

class Box : public Position {
public:
    int z;

    Box() : z(0) {}
};

class CraneSystem {
private:
    std::vector<Motor> motors;
    Box object;
    bool isGrabbed;
    static std::vector<std::string> commands;

public:
    CraneSystem() {
        for (int i = 0; i < 8; i++) {
            motors.push_back(Motor());
        }
    }

    static void addCommand(const std::string& command) {
        commands.push_back(command);
    }

    static const std::vector<std::string>& getCommands() {
        return commands;
    }

    static void printCommands() {
        std::cout << "Command List: \n";
        for (size_t i = 0; i < commands.size(); i++) {
            std::cout << i + 1 << ". " << commands[i] << "\n";
        }
        std::cout << "———————\n";
    }

    void printPositions() const {
        std::cout << "Crane Motor1 Position: (X: " << motors[0].getX() << ", Y: " << motors[0].getY() << ")\n";
        std::cout << "Crane Motor2 Position: (X: " << motors[1].getX() << ", Y: " << motors[1].getY() << ")\n";
        std::cout << "Box Position: (X: " << object.getX() << ", Y: " << object.getY() << ", Z: " << object.z << ")\n";
        std::cout << "———————\n";
    }

    void craneCommand(const std::string& command) {
        if (command == "right") {
            motors[0].activate();
            motors[0].moveX(1);
            if (isGrabbed) object.moveX(1);
        } else if (command == "left") {
            motors[0].activate();
            motors[0].moveX(-1);
            if (isGrabbed) object.moveX(-1);
        } else if (command == "down") {
            motors[1].activate();
            motors[1].moveY(-1);
            if (isGrabbed) object.moveY(-1);
        } else if (command == "up") {
            motors[1].activate();
            motors[1].moveY(1);
            if (isGrabbed) object.moveY(1);
        } else if (command == "grab") {
            if (motors[0].getX() != object.getX() || motors[0].getY() != object.getY()) {
                std::cout << "Cannot grab.\n";
                return;
            }

            bool allInactive = true;
            for (int i = 3; i < 8; i++) {
                if (motors[i].getIsActive()) {
                    allInactive = false;
                    break;
                }
            }
            if (allInactive) {
                for (int i = 3; i < 8; i++) {
                    motors[i].activate();
                }
                object.z += 10;
                isGrabbed = true;
            } else {
                std::cout << "Cannot grab. Some of the motors are active.\n";
            }
        } else if (command == "letgo") {
            bool allActive = true;
            for (int i = 3; i < 8; i++) {
                if (!motors[i].getIsActive()) {
                    allActive = false;
                    break;
                }
            }
            if (allActive) {
                for (int i = 3; i < 8; i++) {
                    motors[i].deactivate();
                }
                object.z -= 10;
                isGrabbed = false;
            } else {
                std::cout << "Cannot let go. Some of the motors are not active.\n";
            }
        } else if (command == "exit") {
            std::cout << "End the crane operation\n";
        } else {
            std::cout << "Invalid command! Please enter again\n";
        }

        addCommand(command);
        printCommands();
        printPositions();
    }
};

std::vector<std::string> CraneSystem::commands;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    CraneSystem cs;
    std::string command;

    while (true) {
        std::cout << "Enter a command: " << std::flush;
        std::getline(std::cin, command);
        cs.craneCommand(command);
        if (command == "exit") {
            break;
        }
    }

    return 0;
}

모터 1이 x축을 담당하고 모터 2가 y축을 담당해서 움직입니다.
인형 뽑기 기계처럼 작동하게 하였고 따라서 z축이 높이가 됩니다./
