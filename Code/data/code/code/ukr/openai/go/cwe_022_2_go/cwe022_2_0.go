package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
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

	// Iterate through the tar file
	for {
		// Get the next file in the tar
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of the tar file
		}
		if err != nil {
			return false // Error reading the tar file
		}

		// Create the full path for the extracted file
		targetPath := filepath.Join(destPath, header.Name)

		// Check if the header indicates a directory
		if header.Typeflag == tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Ensure the parent directory exists
		if err := os.MkdirAll(filepath.Dir(targetPath), os.ModePerm); err != nil {
			return false // Error creating parent directory
		}

		// Create the file
		outFile, err := os.Create(targetPath)
		if err != nil {
			return false // Error creating file
		}
		defer outFile.Close()

		// Copy the contents from the tar file to the new file
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false // Error writing file
		}
	}

	return true // Extraction successful
}