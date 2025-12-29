package main

import (
	"bytes"
	"os/exec"
)

// getLsResult executes the `ls -l` command on the provided directory path.
// It returns the output of the command if successful, or an empty string if an error occurs.
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