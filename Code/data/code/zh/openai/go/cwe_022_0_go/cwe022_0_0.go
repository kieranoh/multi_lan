package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory.
// If there is any error during the file reading process (e.g., file not found, permission error),
// it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)

	// Read the file content
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// Return an empty string in case of an error
		return ""
	}

	// Return the file content as a string
	return string(content)
}