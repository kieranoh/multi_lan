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
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading tar
		}

		// Construct the full path for the extracted file
		targetPath := filepath.Join(destPath, header.Name)

		// Check if the header describes a directory
		if header.Typeflag == tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the file
		outFile, err := os.Create(targetPath)
		if err != nil {
			return false // Error creating file
		}
		defer outFile.Close()

		// Copy the file contents from the tar archive to the new file
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false // Error copying file contents
		}
	}

	return true // Extraction successful
}