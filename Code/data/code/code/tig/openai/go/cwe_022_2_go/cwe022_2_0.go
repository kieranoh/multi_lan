package main

import (
	"archive/tar"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful, and false if an error occurs during extraction
// (e.g., file not found, permission errors, or unable to extract all contents).
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Create a new tar reader
	tarReader := tar.NewReader(file)

	// Iterate through the files in the tar archive
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading the tar file
		}

		// Create the full path for the destination file
		destFilePath := filepath.Join(destPath, header.Name)

		// Handle directory
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, 0755); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the destination file
		destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // Error creating file
		}

		// Copy the contents from the tar file to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			destFile.Close()
			return false // Error copying file contents
		}

		// Close the destination file
		destFile.Close()
	}

	return true // Extraction successful
}