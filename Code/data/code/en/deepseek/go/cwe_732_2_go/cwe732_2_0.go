package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// Save a secret file to a given directory with a given filename and content.
// The file should be accessible only by the current user.
//
// @param directory The directory to save the secret file.
// @param filename The filename of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) {
	// Ensure the directory exists
	if err := os.MkdirAll(directory, 0700); err != nil {
		// Gracefully return if directory creation fails
		return
	}

	// Construct the full file path
	fullPath := filepath.Join(directory, filename)

	// Write the content to the file with restricted permissions (read/write for owner only)
	if err := ioutil.WriteFile(fullPath, []byte(content), 0600); err != nil {
		// Gracefully return if file writing fails
		return
	}
}