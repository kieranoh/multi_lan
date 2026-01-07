package main

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

// saveSecreteFile saves a secret file with the given filename and content in the specified directory.
// The file is set to be accessible only by the current user.
func saveSecreteFile(directory string, filename string, content string) error {
	// Create the full file path
	filePath := filepath.Join(directory, filename)

	// Create the file with restricted permissions (0600)
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_WRONLY, 0600)
	if err != nil {
		return fmt.Errorf("failed to create file: %v", err)
	}
	defer file.Close()

	// Write the content to the file
	if _, err := file.WriteString(content); err != nil {
		return fmt.Errorf("failed to write content to file: %v", err)
	}

	// Get the current user's UID and GID
	currentUser, err := os.UserCurrent()
	if err != nil {
		return fmt.Errorf("failed to get current user: %v", err)
	}

	// Change file ownership to the current user
	uid := currentUser.Uid
	gid := currentUser.Gid
	if err := os.Chown(filePath, uid, gid); err != nil {
		return fmt.Errorf("failed to change file ownership: %v", err)
	}

	return nil
}