package main

import (
	"archive/tar"
	"io"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction was successful; otherwise, it returns false.
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
		// Get the next file in the archive
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			return false
		}

		// Construct the full path for the file to be extracted
		targetPath := filepath.Join(destPath, header.Name)

		// Check for directory in the header
		if header.Typeflag == tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				return false
			}
			continue
		}

		// Create the file to extract
		targetFile, err := os.OpenFile(targetPath, os.O_RDWR|os.O_CREATE|os.O_TRUNC, os.FileMode(header.Mode))
		if err != nil {
			return false
		}

		// Copy the contents from the tar file to the target file
		if _, err := io.Copy(targetFile, tarReader); err != nil {
			targetFile.Close()
			return false
		}

		// Close the target file
		targetFile.Close()
	}

	return true
}