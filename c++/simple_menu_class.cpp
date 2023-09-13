#include <iostream>
#include <vector>
#include <cstdlib>

#define MAX_COMMAND_CHARACTERS 6
#define MAX_COMMAND_PARAMETERS 5
#define FIELD_SEPARATOR        ","
#define MAX_INPUT_CHARACTERS   100

class CommandProcessor {
private:
    std::string cmd;
    std::vector<std::string> par;

public:
    void print_help_menu() {
        std::cout << "This is where a description of the commands would be" << std::endl;
    }

    void print_button_command() {
        int pressed = rand() % 2;
        std::cout << "Button status: " << (pressed ? "pressed" : "Not pressed") << std::endl;
    }

    void print_led_command() {
        if(par.empty()) {
            std::cout << "Led command wrong parameters" << std::endl;
            return;
        }

        if (par[0] == "on") {
            std::cout << "Led is on" << std::endl;
        } else if (par[0] == "off") {
            std::cout << "Led is off" << std::endl;
        } else if (par[0] == "blink") {
            if (par.size() != 2) {
                std::cout << "Led blinking command wrong parameters" << std::endl;
            } else {
                std::cout << "Led is blinking with " << par[1] << " Hz" << std::endl;
            }
        } else {
            std::cout << "Led command wrong parameters" << std::endl;
        }
    }

    bool process_buffer(const std::string& buffer) {
        if (buffer.empty()) {
            return true;
        }

        size_t pos = buffer.find(FIELD_SEPARATOR);
        cmd = buffer.substr(0, pos);

        if (pos != std::string::npos) {
            par.clear();
            std::string rest = buffer.substr(pos + 1);

            while ((pos = rest.find(FIELD_SEPARATOR)) != std::string::npos) {
                par.push_back(rest.substr(0, pos));
                rest.erase(0, pos + 1);
            }

            if (!rest.empty()) {
                par.push_back(rest);
            }
        }

        std::cout << "Command " << cmd << " parsed with " << par.size() << " arguments" << std::endl;

        return false;
    }
};

int main() {
    CommandProcessor processor;

    std::string buffer;

    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, buffer);

        if (processor.process_buffer(buffer)) {
            continue;
        }

        std::cout << "Command parsed " << processor.get_command() << "." << std::endl;

        if (processor.get_command() == "help") {
            if (!processor.has_parameters()) {
                std::cout << "Command " << processor.get_command() << " wrong arguments" << std::endl;
                continue;
            }

            processor.print_help_menu();
            std::cout << "Command " << processor.get_command() << " finished" << std::endl;

        } else if (processor.get_command() == "led") {
            processor.print_led_command();
            std::cout << "Command " << processor.get_command() << " finished" << std::endl;

        } else if (processor.get_command() == "button") {
            if (!processor.has_parameters()) {
                std::cout << "Command " << processor.get_command() << " wrong arguments" << std::endl;
                continue;
            }

            processor.print_button_command();
            std::cout << "Command " << processor.get_command() << " finished" << std::endl;

        } else {
            std::cout << "Command not found" << std::endl;
        }

        buffer.clear();
    }

    return 0;
}
