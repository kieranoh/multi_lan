package main

import (
	"bytes"
	"os/exec"
)

// getLsResult executes the `ls -l` command for the provided directory path
// and returns the output as a string. If an error occurs during execution,
// it returns an empty string.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	var out bytes.Buffer
	cmd.Stdout = &out
	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}