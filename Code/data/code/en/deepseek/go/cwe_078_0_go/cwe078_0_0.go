import (
	"bytes"
	"os"
	"os/exec"
	"path/filepath"
)

func getLsResult(dirPath string) string {
	// Clean the path to remove any trailing slashes and normalize
	cleanPath := filepath.Clean(dirPath)
	
	// Check if the directory exists and is accessible
	if info, err := os.Stat(cleanPath); err != nil || !info.IsDir() {
		return ""
	}
	
	// Create the command with the cleaned directory path
	cmd := exec.Command("ls", "-l")
	cmd.Dir = cleanPath
	
	// Capture stdout and stderr
	var stdout, stderr bytes.Buffer
	cmd.Stdout = &stdout
	cmd.Stderr = &stderr
	
	// Run the command
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	// Check if there was any error output
	if stderr.Len() > 0 {
		return ""
	}
	
	// Return the stdout output as string
	return stdout.String()
}