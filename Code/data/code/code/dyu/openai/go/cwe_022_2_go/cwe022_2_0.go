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

		// Check the type of file (directory or regular file)
		switch header.Typeflag {
		case tar.TypeDir:
			// Create directory
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
		case tar.TypeReg:
			// Create regular file
			destFile, err := os.OpenFile(destFilePath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.FileMode(header.Mode))
			if err != nil {
				return false // Error creating file
			}
			defer destFile.Close()

			// Copy the file content from the tar archive
			if _, err := io.Copy(destFile, tarReader); err != nil {
				return false // Error copying file content
			}
		default:
			return false // Unsupported file type
		}
	}

	return true // Extraction succeeded
}