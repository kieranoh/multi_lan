package main

import (
	"bytes"
	"os/exec"
)

// getLsResult executes the `ls -l` command in the provided directory path.
// It returns the output of the command, or an empty string if an error occurs.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out
	var stderr bytes.Buffer
	cmd.Stderr = &stderr

	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}