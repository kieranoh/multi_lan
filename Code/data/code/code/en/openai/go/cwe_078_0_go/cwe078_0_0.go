package main

import (
	"os/exec"
	"strings"
)

// getLsResult returns the output of `ls -l` command when executed in the provided directory path.
// If any error occurs during execution, it returns an empty string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	output, err := cmd.Output()
	if err != nil {
		return ""
	}

	return strings.TrimSpace(string(output))
}