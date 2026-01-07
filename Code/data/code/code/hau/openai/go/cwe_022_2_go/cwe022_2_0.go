package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful, otherwise returns false in case of errors.
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
		// Get the next file in the archive
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading tar archive
		}

		// Construct the full path for the destination file
		targetPath := filepath.Join(destPath, header.Name)

		// Handle directory
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the target file
		targetFile, err := os.Create(targetPath)
		if err != nil {
			return false // Error creating file
		}

		// Copy the content from the tar file to the target file
		if _, err := io.Copy(targetFile, tarReader); err != nil {
			targetFile.Close()
			return false // Error during file copy
		}

		// Close the target file
		if err := targetFile.Close(); err != nil {
			return false // Error closing file
		}
	}

	return true // Successful extraction
}