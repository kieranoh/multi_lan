package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the `ls -l` command on the provided directory path 
// and returns the output. If an error occurs (e.g., directory not found, 
// permission error), it returns an empty string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}