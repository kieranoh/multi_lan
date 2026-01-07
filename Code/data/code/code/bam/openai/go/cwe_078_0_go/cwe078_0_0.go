package main

import (
	"os/exec"
	"strings"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns the output or an empty string in case of an error.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}