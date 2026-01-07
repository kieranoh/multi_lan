package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns its output or an empty string in case of an error.
func getLsResult(dirPath string) string {
	// Prepare the command
	cmd := exec.Command("ls", "-l", dirPath)

	// Execute the command and capture the output
	output, err := cmd.Output()
	if err != nil {
		// Return an empty string if an error occurs
		return ""
	}

	// Return the output as a string
	return strings.TrimSpace(string(output))
}