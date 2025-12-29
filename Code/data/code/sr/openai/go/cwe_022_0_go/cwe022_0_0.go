package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the contents of a file in a specified directory.
// If an error occurs during the file reading process (e.g., file not found, permission issues),
// it returns an empty string. The returned string will free the caller.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(data)
}