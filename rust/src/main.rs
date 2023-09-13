use std::io::{self, Write};
use rand::Rng;

const MAX_COMMAND_CHARACTERS: usize = 6;
const MAX_COMMAND_PARAMETERS: usize = 5;
const FIELD_SEPARATOR: char = ',';
const MAX_INPUT_CHARACTERS: usize = 100;

struct CommandProcessor {
    cmd: String,
    par: Vec<String>,
}

impl CommandProcessor {
    fn new() -> Self {
        CommandProcessor {
            cmd: String::new(),
            par: Vec::new(),
        }
    }

    fn print_help_menu(&self) {
        println!("This is where a description of the commands would be");
    }

    fn print_button_command(&self) {
        let pressed = rand::thread_rng().gen_bool(0.5);
        println!("Button status: {}", if pressed { "pressed" } else { "Not pressed" });
    }

    fn print_led_command(&self) {
        if self.par.is_empty() {
            println!("Led command wrong parameters");
            return;
        }

        match self.par[0].as_str() {
            "on" => println!("Led is on"),
            "off" => println!("Led is off"),
            "blink" => {
                if self.par.len() != 2 {
                    println!("Led blinking command wrong parameters");
                    return;
                }
                println!("Led is blinking with {} Hz", self.par[1]);
            }
            _ => println!("Led command wrong parameters"),
        }
    }

    fn process_buffer(&mut self, buffer: &str) -> bool {
        if buffer.is_empty() {
            return true;
        }
    
        let mut parts = buffer.splitn(2, FIELD_SEPARATOR);
        self.cmd = parts.next().unwrap().to_string();
        self.par = parts.next().unwrap_or("").split(FIELD_SEPARATOR).map(String::from).collect();
    
        if self.par.len() == 1 && self.par[0].is_empty() {
            self.par.clear();
        }
    
        println!("Command {} parsed with {} arguments", self.cmd, self.par.len());
    
        false
    }
    
}

fn main() {
    let mut cp = CommandProcessor::new();

    loop {
        print!("Enter a command: ");
        io::stdout().flush().unwrap();

        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).unwrap();
        buffer = buffer.trim().to_string();

        if cp.process_buffer(&buffer) {
            continue;
        }

        println!("Command parsed {}.", cp.cmd);

        match cp.cmd.as_str() {
            "help" => {
                if !cp.par.is_empty() {
                    println!("Command {} wrong arguments", cp.cmd);
                    continue;
                }
                cp.print_help_menu();
                println!("Command {} finished", cp.cmd);
            }
            "led" => {
                cp.print_led_command();
                println!("Command {} finished", cp.cmd);
            }
            "button" => {
                if !cp.par.is_empty() {
                    println!("Command {} wrong arguments", cp.cmd);
                    continue;
                }
                cp.print_button_command();
                println!("Command {} finished", cp.cmd);
            }
            _ => println!("Command not found"),
        }
    }
}
