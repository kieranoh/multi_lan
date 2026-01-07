import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads a file from the specified directory and returns its contents.
// If any error occurs during reading (e.g., file not found, permission error),
// an empty string is returned.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)
	
	// Check if the file exists and is accessible
	fileInfo, err := os.Stat(fullPath)
	if err != nil {
		return ""
	}
	
	// Ensure it's a regular file (not a directory)
	if fileInfo.IsDir() {
		return ""
	}
	
	// Read the file contents
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	
	// Convert byte slice to string and return
	return string(content)
}