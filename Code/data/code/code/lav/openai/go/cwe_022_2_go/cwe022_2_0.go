package main

import (
	"archive/tar"
	"os"
	"path/filepath"
)

// extractTarToPath extracts the contents of a tar file to the specified destination path.
// Returns true if the extraction is successful, false otherwise (e.g., file not found, permission errors, unable to extract all contents).
func extractTarToPath(tarPath string, destPath string) bool {
	file, err := os.Open(tarPath)
	if err != nil {
		return false
	}
	defer file.Close()

	gzr, err := tar.NewReader(file)
	if err != nil {
		return false
	}

	for {
		header, err := gzr.Next()
		if err != nil {
			break
		}

		target := filepath.Join(destPath, header.Name)

		switch header.Typeflag {
		case tar.TypeDir:
			if err := os.MkdirAll(target, os.ModePerm); err != nil {
				return false
			}
		case tar.TypeReg:
			outFile, err := os.Create(target)
			if err != nil {
				return false
			}
			defer outFile.Close()

			if _, err := io.Copy(outFile, gzr); err != nil {
				return false
			}
		default:
			return false
		}
	}
	return true
}