package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file from a specified directory.
// It returns the content of the file if it exists and is accessible,
// otherwise it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full path to the file
	fullPath := filepath.Join(dirPath, filename)

	// Read the file
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// Return an empty string if there's an error
		return ""
	}

	// Return the content as a string
	return string(content)
}