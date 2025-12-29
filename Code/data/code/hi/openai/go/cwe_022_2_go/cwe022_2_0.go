package main

import (
	"fmt"
	"os"
	"path/filepath"
	Tar "archive/tar"
	"io"
	"os/exec"
)

// extractTarToPath extracts the contents of a tar file at the specified path.
// It returns true if the extraction is successful; otherwise, it returns false if
// any errors occur during the extraction process (such as file not found, permission errors,
// or inability to extract all contents).
//
// @param tarPath: path of the tar file
// @param destPath: path of the destination folder
//
// @return true if the extraction is successful; otherwise, false
func extractTarToPath(tarPath string, destPath string) bool {
	// Check if the tar file exists
	if _, err := os.Stat(tarPath); os.IsNotExist(err) {
		return false
	}

	// Create the destination directory if it doesn't exist
	err := os.MkdirAll(destPath, os.ModePerm)
	if err != nil {
		return false
	}

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

		// Create the full path for the file
		target := filepath.Join(destPath, header.Name)

		// Check if the file is a directory
		if header.Typeflag == Tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(target, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// Create the target file
		outFile, err := os.Create(target)
		if err != nil {
			return false
		}
		defer outFile.Close()

		// Copy the file content from the tar to the target file
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false
		}
	}

	return true
}