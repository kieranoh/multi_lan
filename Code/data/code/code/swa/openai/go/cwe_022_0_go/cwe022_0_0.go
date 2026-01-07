package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file located in the provided directory path.
// If the file is not found or there is a permission error, it returns an empty string.
// The returned string must be freed by the caller.
func readFileFromDir(filename, dirPath string) string {
	// Create the full path to the file
	fullPath := filepath.Join(dirPath, filename)

	// Attempt to read the file
	data, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// Return an empty string if there is an error
		return ""
	}

	// Return the file content as a string
	return string(data)
}