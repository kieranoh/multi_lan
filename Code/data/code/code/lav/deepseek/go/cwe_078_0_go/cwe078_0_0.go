package main

import (
	"bytes"
	"os/exec"
	"strings"
)

// getLsResult returns the output of `ls -l` command for the given directory path.
// If any error occurs during command execution (e.g., directory not found, permission error),
// it returns an empty string.
//
// @param dirPath The user-provided directory path where `ls -l` command will be executed.
// @return The output of `ls -l` command or empty string if error occurs.
func getLsResult(dirPath string) string {
	// Create the command with the provided directory path
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Create buffers to capture stdout and stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Execute the command
	err := cmd.Run()
	
	// If there's any error or stderr has content, return empty string
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Return the stdout output as string, trimming any trailing newline
	return strings.TrimSuffix(stdout.String(), "\n")
}