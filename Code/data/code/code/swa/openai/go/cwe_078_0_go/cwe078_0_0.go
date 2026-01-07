package main

import (
	"bytes"
	"os/exec"
)

// getLsResult executes the `ls -l` command on the provided directory path
// and returns its output or an empty string in case of an error.
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