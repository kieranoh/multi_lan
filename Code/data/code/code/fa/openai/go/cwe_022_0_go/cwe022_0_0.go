package main

import (
	"io/ioutil"
	"log"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory
// and returns its content as a string. If there is any error during the process
// (such as file not found or permission error), it returns an empty string.
// The returned string should be freed by the caller.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)

	// Read the file content
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		log.Printf("Error reading file: %v", err)
		return ""
	}

	return string(content)
}