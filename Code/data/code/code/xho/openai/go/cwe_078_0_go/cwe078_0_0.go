package main

import (
	"fmt"
	"os/exec"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns the output (only stdout). If an error occurs during command
// execution (e.g., directory not found, permission error), it returns an empty string.
func getLsResult(dirPath string) string {
	// Prepare the command
	cmd := exec.Command("ls", "-l", dirPath)

	// Run the command and capture the output
	output, err := cmd.CombinedOutput()

	// If there is an error, return an empty string
	if err != nil {
		return ""
	}

	// Return the output as a string
	return string(output)
}

func main() {
	// Example usage
	result := getLsResult("/path/to/directory")
	fmt.Println(result)
}