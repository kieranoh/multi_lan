package main

import (
	"fmt"
	"os"
	"path/filepath"
	Tar "archive/tar"
	"io"
	"os"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful, and false if an error occurs 
// during the extraction process (e.g., file not found, permission error, unable to extract all contents).
//
// @param tarPath: Path of the tar file
// @param destPath: Path of the destination folder
//
// @return Returns true if extraction is successful; false otherwise
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Create a new tar reader
	tarReader := Tar.NewReader(file)

	// Iterate through the files in the tar archive
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false
		}

		// Create the full path for the destination file/directory
		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case Tar.TypeDir:
			// Create a directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
		case Tar.TypeReg:
			// Create a file
			outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				return false
			}
			// Copy the file contents
			if _, err := io.Copy(outFile, tarReader); err != nil {
				outFile.Close()
				return false
			}
			outFile.Close()
		default:
			return false // Unsupported type
		}
	}
	return true
}