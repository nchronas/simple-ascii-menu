#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ... (Other header files and macro definitions remain the same)

void print_led_command(char *parameters[], uint8_t args) {
    if (args == 0) {
        printf("Led command wrong parameters\n");
        return;
    }

    if (strncmp("on", parameters[0], MAX_COMMAND_CHARACTERS) == 0) {
        printf("Led is on\n");
    } else if (strncmp("off", parameters[0], MAX_COMMAND_CHARACTERS) == 0) {
        printf("Led is off\n");
    } else if (strncmp("blink", parameters[0], MAX_COMMAND_CHARACTERS) == 0) {
        if (args != 2) {
            printf("Led blinking command wrong parameters\n");
            return;
        }
        printf("Led is blinking with %s Hz\n", parameters[1]);
    } else {
        printf("Led command wrong parameters\n");
    }
}

bool process_buffer(char **command, char *parameters[], uint8_t *args, char *buffer) {
    char *rest;

    if (buffer == NULL || strlen(buffer) == 0) {
        return true;
    }

    *command = strtok_r(buffer, FIELD_SEPARATOR, &rest);

    if (*command == NULL || strlen(*command) == 0) {
        return true;
    }

    *args = 0;

    for (int i = 0; i < MAX_COMMAND_PARAMETERS; i++) {
        parameters[i] = strtok_r(rest, FIELD_SEPARATOR, &rest);

        if (parameters[i] == NULL) {
            break;
        }

        (*args)++;
    }

    printf("Command %s parsed with %d arguments\n", *command, *args);

    return false;
}

int main() {
    char *cmd;
    char *par[MAX_COMMAND_PARAMETERS];
    uint8_t args;

    char buffer[MAX_INPUT_CHARACTERS];

    srand(time(NULL)); // Seed the random number generator

    while (true) {
        printf("Enter a command: ");
        fgets(buffer, MAX_INPUT_CHARACTERS, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

        if (process_buffer(&cmd, par, &args, buffer)) {
            continue;
        }

        printf("Command parsed %s.\n", cmd);

        // ... (Rest of the main function remains the same)

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));
    }

    return 0;
}
