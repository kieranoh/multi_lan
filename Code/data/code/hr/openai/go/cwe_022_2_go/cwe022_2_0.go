package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the content of a tar file to the specified destination path.
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

	// Iterate through the files in the tar archive
	for {
		// Get the next file from the tar archive
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false
		}

		// Create the full path for the destination file
		destFilePath := filepath.Join(destPath, header.Name)

		// Check if the file is a directory
		if header.Typeflag == tar.TypeDir {
			// Create the directory if it doesn't exist
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// Create the file
		destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			return false
		}

		// Copy the file content
		if _, err := io.Copy(destFile, tarReader); err != nil {
			destFile.Close()
			return false
		}

		// Close the file
		destFile.Close()
	}

	return true
}