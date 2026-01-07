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

	// Iterate over the files in the tar archive
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error occurred
		}

		// Create the full path for the destination file
		destFilePath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// Create the directory
			if err := os.MkdirAll(destFilePath, os.FileMode(header.Mode)); err != nil {
				return false // Error occurred
			}
		case tar.TypeReg:
			// Create the file
			fileOut, err := os.OpenFile(destFilePath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false // Error occurred
			}
			defer fileOut.Close()

			// Copy the file content
			if _, err := io.Copy(fileOut, tarReader); err != nil {
				return false // Error occurred
			}
		default:
			return false // Unsupported file type
		}
	}

	return true // Extraction successful
}