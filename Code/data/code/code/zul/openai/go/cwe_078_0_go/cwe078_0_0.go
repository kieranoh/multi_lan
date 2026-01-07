package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the 'ls -l' command in the provided directory path.
// It returns the output of the command or an empty string if an error occurs.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}