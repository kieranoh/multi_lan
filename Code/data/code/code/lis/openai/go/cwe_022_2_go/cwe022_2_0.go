package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
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
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading tar
		}

		// Create the destination file path
		destFilePath := filepath.Join(destPath, header.Name)

		// Ensure the directory exists
		if header.FileInfo().IsDir() {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the destination file
		destFile, err := os.OpenFile(destFilePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.ModePerm)
		if err != nil {
			return false // Error creating file
		}
		defer destFile.Close()

		// Copy the contents from the tar file to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			return false // Error copying file
		}
	}

	return true // Extraction successful
}