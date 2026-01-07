package main

import (
	"os"
	"path/filepath"
	"strings"
	"archive/tar"
	"io"
	"log"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// It returns true if the extraction is successful; otherwise, it returns false.
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		log.Println("Error opening tar file:", err)
		return false
	}
	defer file.Close()

	tarReader := tar.NewReader(file)

	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Println("Error reading tar file:", err)
			return false
		}

		// Create the target file path
		targetPath := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			// Create directories
			if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
				log.Println("Error creating directory:", err)
				return false
			}
		case tar.TypeReg:
			// Create files
			file, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
			if err != nil {
				log.Println("Error creating file:", err)
				return false
			}
			if _, err := io.Copy(file, tarReader); err != nil {
				log.Println("Error writing file:", err)
				file.Close()
				return false
			}
			file.Close()
		default:
			log.Println("Unknown type:", header.Typeflag)
			return false
		}
	}

	return true
}