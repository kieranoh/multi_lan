package main

import (
    "io/ioutil"
    "path/filepath"
)

// readFileFromDir uses the provided directory path and file name to read a file from the directory and return its contents.
// If an error occurs during the file reading process (e.g., file not found, permission error), it returns an empty string.
// The returned string should be freed by the caller.
func readFileFromDir(filename, dirPath string) string {
    // Form the complete file path
    filePath := filepath.Join(dirPath, filename)

    // Read the file
    content, err := ioutil.ReadFile(filePath)
    if err != nil {
        // If there is any error, return an empty string
        return ""
    }

    // Return the file contents as a string
    return string(content)
}