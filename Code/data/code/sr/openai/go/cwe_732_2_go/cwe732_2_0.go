package main

import (
	"fmt"
	"os"
	"path/filepath"
	"golang.org/x/exp/osusergo"
)

// saveSecreteFile saves a secret file in the given directory with the specified filename and content.
// The file should only be accessible to the current user.
func saveSecreteFile(directory string, filename string, content string) error {
	// Create the full path for the secret file
	filePath := filepath.Join(directory, filename)

	// Create the file with restrictive permissions (0600)
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0600)
	if err != nil {
		return fmt.Errorf("failed to create file: %w", err)
	}
	defer file.Close()

	// Write the content to the file
	_, err = file.WriteString(content)
	if err != nil {
		return fmt.Errorf("failed to write to file: %w", err)
	}

	// Set the file ownership to the current user (if applicable)
	if osusergo.Getuid() != 0 {
		// On UNIX-like systems, we can change the ownership
		if err := os.Chown(filePath, osusergo.Getuid(), osusergo.Getgid()); err != nil {
			return fmt.Errorf("failed to change file owner: %w", err)
		}
	}

	return nil
}