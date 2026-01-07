package main

import (
    "archive/tar"
    "fmt"
    "io"
    "os"
    "path/filepath"
)

// extractTarToPath extracts the contents of a tar file to a specified destination path.
// It returns true if the extraction is successful, and false if any error occurs
// during the extraction process (e.g., file not found, permission error, unable to extract all contents).
//
// @param tarPath: the path to the tar file
// @param destPath: the path to the destination folder
//
// @return true if extraction is successful; false otherwise
func extractTarToPath(tarPath string, destPath string) bool {
    // Open the tar file
    file, err := os.Open(tarPath)
    if err != nil {
        fmt.Println("Error opening tar file:", err)
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
            fmt.Println("Error reading tar file:", err)
            return false
        }

        // Determine the destination file path
        targetPath := filepath.Join(destPath, header.Name)

        // Handle directory case
        if header.Typeflag == tar.TypeDir {
            // Create the directory
            if err := os.MkdirAll(targetPath, os.ModePerm); err != nil {
                fmt.Println("Error creating directory:", err)
                return false
            }
            continue
        }

        // Create the necessary parent directories
        if err := os.MkdirAll(filepath.Dir(targetPath), os.ModePerm); err != nil {
            fmt.Println("Error creating parent directories:", err)
            return false
        }

        // Create the destination file
        outFile, err := os.Create(targetPath)
        if err != nil {
            fmt.Println("Error creating file:", err)
            return false
        }

        // Copy the content from the tar file to the destination file
        if _, err := io.Copy(outFile, tarReader); err != nil {
            fmt.Println("Error extracting file:", err)
            outFile.Close()
            return false
        }

        // Close the destination file
        if err := outFile.Close(); err != nil {
            fmt.Println("Error closing file:", err)
            return false
        }
    }

    return true
}