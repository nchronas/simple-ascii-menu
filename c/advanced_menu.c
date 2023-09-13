#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COMMAND_CHARACTERS 6
#define MAX_COMMAND_PARAMETERS 5
#define FIELD_SEPERATOR        ","
#define MAX_INPUT_CHARACTERS   100

#define MENU_SIZE (sizeof(menu) / sizeof(menu[0]))

void print_help_menu(char *parameters[], __uint8_t args);
void print_button_command(char *parameters[], __uint8_t args);
void print_led_command(char *parameters[], __uint8_t args);

struct _menu {
    char *cmd;
    char *description;
    void (*process_command)(char *argv[], __uint8_t argc);
};

struct _menu menu[] = {
    {.cmd = "help", .description = "Help menu", .process_command = &print_help_menu},
    {.cmd = "led", .description = "Set the led state to on,off or blink and the Hz", .process_command = &print_led_command},
    {.cmd = "button", .description = "Get if the button is pressed", .process_command = &print_button_command},
};

void print_help_menu(char *parameters[], __uint8_t args)  {
    
    printf("menu:\n");

    printf("%d commands found.\n", MENU_SIZE);

    for (int i = 0; i < MENU_SIZE; i++) {
        printf("%d. %s: %s.\n", i, menu[i].cmd, menu[i].description);
    }
    printf("End of debug menu\n");
}

void print_button_command(char *parameters[], __uint8_t args)  {
    // Simulate if the button is pressed or not
    int pressed = rand() % 2;
    printf("Button status: %s\n", pressed ? "pressed" : "Not pressed");
}

void print_led_command(char *parameters[], __uint8_t args) {
    
    if(args == 0) {
        printf("Led command wrong parameters\n");
        return;
    }

    if (strncmp("on", parameters[0], 5) == 0) {    
       printf("Led is on\n");
    } else if (strncmp("off", parameters[0], 5) == 0) {
       printf("Led is off\n");
    } else if (strncmp("blink", parameters[0], 5) == 0) {
        if(args != 2) {
            printf("Led blinking command wrong parameters\n");
        }
        printf("Led is blinking with %s Hz\n", parameters[1]);
    } else {
       printf("Led command wrong parameters\n");
    }
    
} 

bool process_buffer(char **command, char *parameters[], __uint8_t *args, char *buffer) {

    char *rest;

    if (buffer == NULL || strlen(buffer) == 0) {
        return true;
    }

    // First token is the command string
    *command = strtok_r(buffer, FIELD_SEPERATOR, &rest);
    if (strlen(*command) == 0) {
        return true;
    }
    *args = 0;

    for (int i = 0; i < MAX_COMMAND_PARAMETERS; i++) {
        parameters[i] = strtok_r(rest, FIELD_SEPERATOR, &rest);
        if (parameters[i] == NULL) {
            break;
        }
        (*args)++;
    }
    printf("Command %s parsed with %d arguments\n", *command, *args);

    return false;
}

void main() {

    char *cmd;
    char *par[MAX_COMMAND_PARAMETERS];
    uint8_t args;

    char buffer[MAX_INPUT_CHARACTERS];

    while(true) {


        printf("Enter a command :");
        scanf("%100s", buffer);

        if (process_buffer(&cmd, par, &args, buffer)) {
            continue;
        }

        printf("Command parsed %s.\n", cmd);

        bool command_found = false;
        for (int i = 0; i < MENU_SIZE; i++) {

            if (strncmp(menu[i].cmd, cmd, MAX_INPUT_CHARACTERS) == 0) {
                menu[i].process_command(par, args);
                printf("Command %s finished\n", menu[i].cmd);
                command_found = true;
            }
        }
        if(!command_found) { printf("Command not found\n"); }
    }
}