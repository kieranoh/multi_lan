package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns its output. If an error occurs during command execution,
// such as directory not found or permission error, it returns an empty string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}