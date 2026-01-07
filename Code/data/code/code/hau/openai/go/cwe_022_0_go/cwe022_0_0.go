package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory.
// If an error occurs (e.g., file not found, permission error), it returns an empty string.
// The caller is responsible for freeing the returned string.
func readFileFromDir(filename, dirPath string) string {
	// Construct the full file path
	fullPath := filepath.Join(dirPath, filename)

	// Attempt to read the file
	content, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// Return an empty string if an error occurs
		return ""
	}

	// Return the content as a string
	return string(content)
}