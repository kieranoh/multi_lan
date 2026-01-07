package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"archive/tar"
	"io"
	"log"
	"os"
)

// extractTarToPath extracts the contents of a tar file to a specified destination path.
// It returns true if extraction is successful, and false if any errors occur during extraction
// (e.g., file not found, permission errors, unable to extract all contents).
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		log.Println("Error opening tar file:", err)
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
			log.Println("Error reading tar file:", err)
			return false
		}

		// Create the destination file path
		destFilePath := filepath.Join(destPath, header.Name)

		// Create directories if they don't exist
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				log.Println("Error creating directory:", err)
				return false
			}
			continue
		}

		// Create the destination file
		destFile, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
		if err != nil {
			log.Println("Error creating file:", err)
			return false
		}

		// Copy the file content from the tar file to the destination file
		if _, err := io.Copy(destFile, tarReader); err != nil {
			log.Println("Error extracting file:", err)
			destFile.Close()
			return false
		}

		// Close the destination file
		destFile.Close()
	}

	return true
}