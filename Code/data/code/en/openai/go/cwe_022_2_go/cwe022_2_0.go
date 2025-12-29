package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"archive/tar"
	"io"
)

// extractTarToPath extracts the content of the tar file to the given destination path.
// If the extraction is successful, it returns true; otherwise, it returns false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Create a new tar reader
	tarReader := tar.NewReader(file)

	// Iterate through the files in the tar
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading tar
		}

		// Create the full path for the destination file
		destFilePath := filepath.Join(destPath, header.Name)

		// Handle directory
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Make sure the parent directory exists
		if err := os.MkdirAll(filepath.Dir(destFilePath), os.ModePerm); err != nil {
			return false // Error creating parent directory
		}

		// Create the destination file
		destFile, err := os.Create(destFilePath)
		if err != nil {
			return false // Error creating file
		}
		defer destFile.Close()

		// Copy the file content from the tar to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			return false // Error copying file content
		}
	}

	return true // Extraction successful
}