package main

import (
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile saves a secret file in the specified directory with the given filename and content.
// The file should be accessible only to the current user.
func saveSecreteFile(directory string, filename string, content string) error {
	// Create the full path for the secret file
	fullPath := filepath.Join(directory, filename)

	// Create the file with permissions set to 0600 (read and write only for the owner)
	file, err := os.OpenFile(fullPath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		return err
	}
	defer file.Close()

	// Write the content to the file
	_, err = file.WriteString(content)
	if err != nil {
		return err
	}

	// Get the current user ID and set the file owner
	if err := os.Chown(fullPath, os.Getuid(), os.Getgid()); err != nil {
		return err
	}

	return nil
}