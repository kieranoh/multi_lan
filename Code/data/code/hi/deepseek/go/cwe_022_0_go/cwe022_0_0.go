import (
	"io/ioutil"
	"os"
	"path/filepath"
)

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
	
	// Read the file content
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	
	return string(content)
}