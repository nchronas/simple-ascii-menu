import random

MAX_COMMAND_CHARACTERS = 6
MAX_COMMAND_PARAMETERS = 5
FIELD_SEPARATOR = ","
MAX_INPUT_CHARACTERS = 100

class CommandProcessor:
    def __init__(self):
        self.cmd = ""
        self.par = []

    def print_help_menu(self):
        print("This is where a description of the commands would be")

    def print_button_command(self):
        pressed = random.choice([True, False])
        print(f"Button status: {'pressed' if pressed else 'Not pressed'}")

    def print_led_command(self):
        if not self.par:
            print("Led command wrong parameters")
            return

        if self.par[0] == "on":
            print("Led is on")
        elif self.par[0] == "off":
            print("Led is off")
        elif self.par[0] == "blink":
            if len(self.par) != 2:
                print("Led blinking command wrong parameters")
            else:
                print(f"Led is blinking with {self.par[1]} Hz")
        else:
            print("Led command wrong parameters")

    def process_buffer(self, buffer):
        if not buffer:
            return True

        parts = buffer.split(FIELD_SEPARATOR, 1)
        self.cmd = parts[0]
        self.par = parts[1].split(FIELD_SEPARATOR) if len(parts) > 1 else []

        print(f"Command {self.cmd} parsed with {len(self.par)} arguments")

        return False

def main():
    processor = CommandProcessor()

    while True:
        buffer = input("Enter a command: ")

        if processor.process_buffer(buffer):
            continue

        print(f"Command parsed {processor.cmd}.")

        if processor.cmd == "help":
            if len(processor.par) != 0:
                print(f"Command {processor.cmd} wrong arguments")
                continue

            processor.print_help_menu()
            print(f"Command {processor.cmd} finished")

        elif processor.cmd == "led":
            processor.print_led_command()
            print(f"Command {processor.cmd} finished")

        elif processor.cmd == "button":
            if len(processor.par) != 0:
                print(f"Command {processor.cmd} wrong arguments")
                continue

            processor.print_button_command()
            print(f"Command {processor.cmd} finished")

        else:
            print("Command not found")

if __name__ == "__main__":
    main()
