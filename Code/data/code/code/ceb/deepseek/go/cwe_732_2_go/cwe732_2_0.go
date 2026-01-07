package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile saves a secret file with the given filename and content in the specified directory.
// The file will be accessible only by the current user (permissions: 0600).
//
// @param directory The directory where the secret file will be saved.
// @param filename The name of the secret file.
// @param content The content of the secret file.
func saveSecreteFile(directory string, filename string, content string) error {
	// Ensure the directory exists
	if err := os.MkdirAll(directory, 0700); err != nil {
		return err
	}

	// Create the full file path
	fullPath := filepath.Join(directory, filename)

	// Write the content to the file with permissions 0600 (readable and writable only by the owner)
	if err := os.WriteFile(fullPath, []byte(content), 0600); err != nil {
		return err
	}

	return nil
}