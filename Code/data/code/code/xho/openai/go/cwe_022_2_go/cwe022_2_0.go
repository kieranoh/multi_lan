package main

import (
	"fmt"
	"os"
	"path/filepath"
	 tar "archive/tar"
	 "io"
	 "os"
	 "log"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful, and false if an error occurs during the extraction process
// (e.g., file not found, permission error, unable to extract all contents).
//
// @param tarPath: The path of the tar file
// @param destPath: The path of the destination folder
//
// @return Returns true if extraction is successful; false otherwise.
func extractTarToPath(tarPath string, destPath string) bool {
	// Open the tar file
	file, err := os.Open(tarPath)
	if err != nil {
		log.Printf("Error opening tar file: %v", err)
		return false
	}
	defer file.Close()

	// Create a new tar reader
	tarReader := tar.NewReader(file)

	// Iterate through the files in the tar archive
	for {
		// Get the next file in the tar archive
		header, err := tarReader.Next()
		if err == io.EOF {
			break // End of archive
		}
		if err != nil {
			log.Printf("Error reading tar file: %v", err)
			return false
		}

		// Create the full path for the extracted file
		destFilePath := filepath.Join(destPath, header.Name)

		// Check if the file is a directory
		if header.Typeflag == tar.TypeDir {
			// Create the directory
			if err := os.MkdirAll(destFilePath, os.ModePerm); err != nil {
				log.Printf("Error creating directory: %v", err)
				return false
			}
			continue
		}

		// Create the directory for the file if it doesn't exist
		if err := os.MkdirAll(filepath.Dir(destFilePath), os.ModePerm); err != nil {
			log.Printf("Error creating directory for file: %v", err)
			return false
		}

		// Create the file
		outFile, err := os.Create(destFilePath)
		if err != nil {
			log.Printf("Error creating file: %v", err)
			return false
		}

		// Copy the content from the tar file to the created file
		if _, err := io.Copy(outFile, tarReader); err != nil {
			log.Printf("Error extracting file: %v", err)
			outFile.Close()
			return false
		}

		// Close the output file
		outFile.Close()
	}

	return true
}

func main() {
	// Example usage
	success := extractTarToPath("example.tar", "./destination")
	if success {
		fmt.Println("Extraction successful.")
	} else {
		fmt.Println("Extraction failed.")
	}
}