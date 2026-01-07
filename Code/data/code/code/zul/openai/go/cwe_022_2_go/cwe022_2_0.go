package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful, and false in case of an error (e.g., file not found,
// permission errors, or unable to extract all contents).
//
// @param tarPath: the path of the tar file
// @param destPath: the path of the destination folder
//
// @return true if extraction is successful; false otherwise
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file for reading
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	// Create a new tar reader
	tarReader := tar.NewReader(file)

	// Iterate through the tar file's contents
	for {
		// Get the next file in the tar archive
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false // Error reading tar file
		}

		// Create the full path for the extracted file
		targetPath := filepath.Join(destPath, header.Name)

		// Handle directory creation
		if header.Typeflag == tar.TypeDir {
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false // Error creating directory
			}
			continue
		}

		// Create the file to write the contents to
		outFile, err := os.Create(targetPath)
		if err != nil {
			return false // Error creating file
		}
		defer outFile.Close()

		// Copy the contents from the tar file to the output file
		if _, err := io.Copy(outFile, tarReader); err != nil {
			return false // Error writing file
		}
	}

	return true // Extraction successful
}