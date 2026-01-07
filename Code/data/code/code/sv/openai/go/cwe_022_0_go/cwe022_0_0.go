package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory
// and returns its content. If any error occurs during the reading process
// (e.g., file not found, permission errors), it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	filePath := filepath.Join(dirPath, filename)

	// Read the file content
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		// Return an empty string if an error occurs
		return ""
	}

	// Return the content as a string
	return string(content)
}