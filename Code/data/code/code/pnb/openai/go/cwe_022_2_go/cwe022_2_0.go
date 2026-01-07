package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"archive/tar"
	"io"
	"os"
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
			return false // Error reading the tar file
		}

		// Create the file or directory
		dest := filepath.Join(destPath, header.Name)
		switch header.Typeflag {
		case tar.TypeDir:
			// Create a directory
			if err := os.MkdirAll(dest, os.ModePerm); err != nil {
				return false // Error creating directory
			}
		case tar.TypeReg:
			// Create a file
			outFile, err := os.Create(dest)
			if err != nil {
				return false // Error creating file
			}
			defer outFile.Close()

			// Copy the content from the tar file to the new file
			if _, err := io.Copy(outFile, tarReader); err != nil {
				return false // Error writing to file
			}
		default:
			return false // Unsupported file type
		}
	}
	return true // Successful extraction
}