package main

import (
	"bytes"
	"os/exec"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns the output as a string. If an error occurs during execution,
// such as the directory not being found or permission errors, it returns
// an empty string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)

	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return "" // Return empty string on error
	}

	return out.String()
}