package main

import (
	"archive/tar"
	"fmt"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// Returns true if extraction is successful; otherwise, false.
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	tarFile, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer tarFile.Close()

	// Create a new tar reader
	tarReader := tar.NewReader(tarFile)

	// Iterate through the files in the tar archive
	for {
		// Get the next file in the tar
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

		// Create the destination file
		destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false // Error creating file
		}
		defer destFile.Close()

		// Copy the file data from the tar to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			return false // Error copying file data
		}
	}

	return true // Extraction successful
}