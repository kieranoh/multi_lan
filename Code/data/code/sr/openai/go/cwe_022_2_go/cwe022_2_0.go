package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful; otherwise, it returns false.
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
			return false // Error reading tar file
		}

		// Create the full path for the extracted file
		destFilePath := filepath.Join(destPath, header.Name)

		// Create the necessary directories for the file
		if header.FileInfo().IsDir() {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the destination file
		destFile, err := os.OpenFile(destFilePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.FileMode(header.Mode))
		if err != nil {
			return false // Error creating file
		}

		// Copy the contents from the tar file to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			destFile.Close()
			return false // Error during copy
		}
		destFile.Close()
	}

	return true // Extraction was successful
}