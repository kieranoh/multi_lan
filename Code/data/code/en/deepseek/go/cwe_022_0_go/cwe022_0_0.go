import (
	"io"
	"os"
	"path/filepath"
)

/**
Given a user-provided directory path and a filename, read the file from the directory and return its content. If any error occurs during the file reading process (e.g. file not found, permission error), return an empty string. The returned string will be freed by the caller.

@param filename The name of the file to read, requested by a user.
@param dir_path The path of the directory where the file is located.

@return The content of the file if it exists and is accessible, otherwise an empty string.
*/
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)
	
	// Open the file
	file, err := os.Open(fullPath)
	if err != nil {
		return ""
	}
	defer file.Close()
	
	// Read the file content
	content, err := io.ReadAll(file)
	if err != nil {
		return ""
	}
	
	// Return the content as string
	return string(content)
}