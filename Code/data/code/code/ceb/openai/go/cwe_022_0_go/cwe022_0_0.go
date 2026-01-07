package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file located in the specified directory.
// If an error occurs during the file reading process (e.g., file not found, permission error),
// it returns an empty string. The returned string must be freed by the caller.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)
	
	// Read the file content
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// If there is an error, return an empty string
		return ""
	}
	
	// Return the content as a string
	return string(content)
}