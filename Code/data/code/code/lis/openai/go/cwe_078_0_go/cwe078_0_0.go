package main

import (
	"bytes"
	"os/exec"
)

// getLsResult returns the output of the `ls -l` command executed on the 
// user-provided directory path. If an error occurs during the command execution 
// (e.g., directory not found, permission error), it returns an empty string.
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