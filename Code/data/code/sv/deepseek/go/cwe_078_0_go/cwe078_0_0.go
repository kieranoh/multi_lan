package main

import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

// getLsResult returns the output (stdout only) of the `ls -l` command when run in a user-provided directory path.
// If any error occurs during command execution (e.g., directory not found, permission error), return an empty string.
//
// @param dirPath The user-provided directory path to run the `ls -l` command.
//
// @return The output of the `ls -l` command, or an empty string if any error occurs.
func getLsResult(dirPath string) string {
	// Clean the path to remove any trailing slashes or irregularities
	cleanPath := filepath.Clean(dirPath)

	// Check if the path exists and is a directory
	fileInfo, err := os.Stat(cleanPath)
	if err != nil {
		return ""
	}
	if !fileInfo.IsDir() {
		return ""
	}

	// Create the command to run ls -l in the specified directory
	cmd := exec.Command("ls", "-l")
	cmd.Dir = cleanPath

	// Capture stdout and stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr

	// Run the command
	err = cmd.Run()
	if err != nil {
		return ""
	}

	// Check if there was any stderr output (indicating a problem)
	if stderr.Len() > 0 {
		return ""
	}

	// Return the stdout output as a string
	return stdout.String()
}