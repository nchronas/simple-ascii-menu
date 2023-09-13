#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define MAX_COMMAND_CHARACTERS 6
#define MAX_COMMAND_PARAMETERS 5
#define FIELD_SEPARATOR        ","
#define MAX_INPUT_CHARACTERS   100

void print_help_menu() {
    std::cout << "This is where a description of the commands would be" << std::endl;
}

void print_button_command() {
    int pressed = rand() % 2;
    std::cout << "Button status: " << (pressed ? "pressed" : "Not pressed") << std::endl;
}

void print_led_command(std::vector<std::string>& parameters) {
    if(parameters.empty()) {
        std::cout << "Led command wrong parameters" << std::endl;
        return;
    }

    if (parameters[0] == "on") {
        std::cout << "Led is on" << std::endl;
    } else if (parameters[0] == "off") {
        std::cout << "Led is off" << std::endl;
    } else if (parameters[0] == "blink") {
        if (parameters.size() != 2) {
            std::cout << "Led blinking command wrong parameters" << std::endl;
        } else {
            std::cout << "Led is blinking with " << parameters[1] << " Hz" << std::endl;
        }
    } else {
        std::cout << "Led command wrong parameters" << std::endl;
    }
}

bool process_buffer(std::string& command, std::vector<std::string>& parameters, std::string buffer) {
    if (buffer.empty()) {
        return true;
    }

    size_t pos = buffer.find(FIELD_SEPARATOR);
    command = buffer.substr(0, pos);

    if (pos != std::string::npos) {
        buffer.erase(0, pos + 1);
    } else {
        buffer.clear();
    }

    parameters.clear();
    while ((pos = buffer.find(FIELD_SEPARATOR)) != std::string::npos) {
        parameters.push_back(buffer.substr(0, pos));
        buffer.erase(0, pos + 1);
    }

    if (!buffer.empty()) {
        parameters.push_back(buffer);
    }

    std::cout << "Command " << command << " parsed with " << parameters.size() << " arguments" << std::endl;

    return false;
}

int main() {
    std::string cmd;
    std::vector<std::string> par;

    std::string buffer;

    while (true) {
        std::cout << "Enter a command: ";
        std::cin >> buffer;

        if (process_buffer(cmd, par, buffer)) {
            continue;
        }

        std::cout << "Command parsed " << cmd << "." << std::endl;

        if (cmd == "help") {
            if (!par.empty()) {
                std::cout << "Command " << cmd << " wrong arguments" << std::endl;
                continue;
            }

            print_help_menu();
            std::cout << "Command " << cmd << " finished" << std::endl;

        } else if (cmd == "led") {
            print_led_command(par);
            std::cout << "Command " << cmd << " finished" << std::endl;

        } else if (cmd == "button") {
            if (!par.empty()) {
                std::cout << "Command " << cmd << " wrong arguments" << std::endl;
                continue;
            }

            print_button_command();
            std::cout << "Command " << cmd << " finished" << std::endl;

        } else {
            std::cout << "Command not found" << std::endl;
        }
    }

    return 0;
}
