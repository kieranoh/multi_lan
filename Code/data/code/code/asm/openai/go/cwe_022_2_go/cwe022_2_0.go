package main

import (
	"fmt"
	"os"
	"path/filepath"
	"archive/tar"
	"io"
)

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
			return false // Error reading tar
		}

		// Construct the full path for the extracted file
		targetPath := filepath.Join(destPath, header.Name)

		// Check for directory in the header
		if header.Typeflag == tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the file
		fileWriter, err := os.Create(targetPath)
		if err != nil {
			return false // Error creating file
		}
		defer fileWriter.Close()

		// Copy the contents from the tar file to the new file
		if _, err := io.Copy(fileWriter, tarReader); err != nil {
			return false // Error writing file
		}
	}

	return true // Extraction was successful
}