package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the `ls -l` command in the user-specified directory path.
// It returns the output of the `ls -l` command or an empty string if there are any errors.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}

	return strings.TrimSpace(string(output))
}