import (
    "os/exec"
    "strings"
)

func getLsResult(dirPath string) string {
    // Execute the ls -l command with the provided directory path
    cmd := exec.Command("ls", "-l", dirPath)
    
    // Capture the standard output
    output, err := cmd.Output()
    
    // If there's an error (e.g., directory not found, permission error), return empty string
    if err != nil {
        return ""
    }
    
    // Convert the output to string and return
    return strings.TrimSpace(string(output))
}