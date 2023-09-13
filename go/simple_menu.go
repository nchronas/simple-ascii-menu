package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

const (
	maxCommandCharacters  = 6
	maxCommandParameters  = 5
	fieldSeparator        = ","
	maxInputCharacters    = 100
)

type CommandProcessor struct {
	cmd string
	par []string
}

func (cp *CommandProcessor) printHelpMenu() {
	fmt.Println("This is where a description of the commands would be")
}

func (cp *CommandProcessor) printButtonCommand() {
	pressed := rand.Intn(2) == 1
	status := "Not pressed"
	if pressed {
		status = "pressed"
	}
	fmt.Printf("Button status: %s\n", status)
}

func (cp *CommandProcessor) printLedCommand() {
	if len(cp.par) == 0 {
		fmt.Println("Led command wrong parameters")
		return
	}

	switch cp.par[0] {
	case "on":
		fmt.Println("Led is on")
	case "off":
		fmt.Println("Led is off")
	case "blink":
		if len(cp.par) != 2 {
			fmt.Println("Led blinking command wrong parameters")
			return
		}
		fmt.Printf("Led is blinking with %s Hz\n", cp.par[1])
	default:
		fmt.Println("Led command wrong parameters")
	}
}

func (cp *CommandProcessor) processBuffer(buffer string) bool {
	if buffer == "" {
		return true
	}

	parts := strings.SplitN(buffer, string(fieldSeparator), 2)
	cp.cmd = parts[0]
	if len(parts) > 1 {
		cp.par = strings.Split(parts[1], string(fieldSeparator))
	} else {
		cp.par = nil
	}

	fmt.Printf("Command %s parsed with %d arguments\n", cp.cmd, len(cp.par))

	return false
}



func main() {
	rand.Seed(time.Now().UnixNano())

	cp := CommandProcessor{}

	for {
		var buffer string
		fmt.Print("Enter a command: ")
		fmt.Scan(&buffer)

		if cp.processBuffer(buffer) {
			continue
		}

		fmt.Printf("Command parsed %s.\n", cp.cmd)

		switch cp.cmd {
		case "help":
			if len(cp.par) != 0 {
				fmt.Printf("Command %s wrong arguments\n", cp.cmd)
				continue
			}
			cp.printHelpMenu()
			fmt.Printf("Command %s finished\n", cp.cmd)

		case "led":
			cp.printLedCommand()
			fmt.Printf("Command %s finished\n", cp.cmd)

		case "button":
			if len(cp.par) != 0 {
				fmt.Printf("Command %s wrong arguments\n", cp.cmd)
				continue
			}
			cp.printButtonCommand()
			fmt.Printf("Command %s finished\n", cp.cmd)

		default:
			fmt.Println("Command not found")
		}
	}
}
