import (
	"bytes"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Normalize the directory path
	cleanPath := filepath.Clean(dirPath)
	
	// Check if the path is a directory
	// Note: We don't need to check permissions here since exec.Command will handle it
	// But we can do a basic check to avoid unnecessary command execution
	if cleanPath == "" {
		return ""
	}
	
	// Create the command
	cmd := exec.Command("ls", "-l", cleanPath)
	
	// Capture stdout and stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Execute the command
	err := cmd.Run()
	
	// If there's any error (including non-zero exit code), return empty string
	if err != nil || stderr.Len() > 0 {
		return ""
	}
	
	// Return the stdout output as string
	return stdout.String()
}