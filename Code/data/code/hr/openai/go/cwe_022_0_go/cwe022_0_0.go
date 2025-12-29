package main

import (
    "io/ioutil"
    "path/filepath"
)

// readFileFromDir reads the content of a file from a given directory path.
// If there is any error during the file reading process (e.g., file not found,
// permission error), it returns an empty string. The returned string is
// expected to be freed by the caller.
//
// @param filename The name of the file to read, provided by the user.
// @param dirPath The directory path where the file is located.
//
// @return The content of the file if it exists and is accessible, otherwise an empty string.
func readFileFromDir(filename, dirPath string) string {
    // Construct the full file path
    fullPath := filepath.Join(dirPath, filename)

    // Read the file content
    content, err := ioutil.ReadFile(fullPath)
    if err != nil {
        return ""
    }

    return string(content)
}