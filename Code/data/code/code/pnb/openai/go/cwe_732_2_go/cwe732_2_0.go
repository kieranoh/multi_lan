package main

import (
	"os"
	"path/filepath"
)

// saveSecreteFile saves a secret file with the given name and content in the specified directory.
// The file should be accessible only to the current user.
func saveSecreteFile(directory string, filename string, content string) error {
	// Create the full path for the new file
	fullPath := filepath.Join(directory, filename)

	// Create the file with restricted permissions (0600)
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

	return nil
}