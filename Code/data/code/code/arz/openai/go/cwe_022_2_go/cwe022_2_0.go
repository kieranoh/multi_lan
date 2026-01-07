package main

import (
    "archive/tar"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

// extractTarToPath extracts the contents of a tar file to a specified destination path.
// It returns true if extraction is successful, false otherwise.
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
        // Get the next file in the tar archive
        header, err := tarReader.Next()
        if err == io.EOF {
            break // End of archive
        }
        if err != nil {
            return false
        }

        // Create the target file path
        targetPath := filepath.Join(destPath, header.Name)

        // Handle directory
        if header.Typeflag == tar.TypeDir {
            // Create the directory
            if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
                return false
            }
            continue
        }

        // Create the target file
        targetFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY, os.FileMode(header.Mode))
        if err != nil {
            return false
        }
        defer targetFile.Close()

        // Copy the file content from the tar archive to the target file
        if _, err := io.Copy(targetFile, tarReader); err != nil {
            return false
        }
    }

    return true
}