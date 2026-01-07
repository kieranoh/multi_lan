package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// saveSecreteFile saves a secret file with the given filename and content in the specified directory.
// The file should only be accessible by the current user.
func saveSecreteFile(directory string, filename string, content string) error {
	// Create the directory if it does not exist
	err := os.MkdirAll(directory, os.ModePerm)
	if err != nil {
		return fmt.Errorf("failed to create directory: %w", err)
	}

	// Define the full path for the secret file
	filePath := filepath.Join(directory, filename)

	// Create the file with restricted permissions
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		return fmt.Errorf("failed to open file: %w", err)
	}
	defer file.Close()

	// Write content to the file
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("failed to write to file: %w", err)
	}

	return nil
}