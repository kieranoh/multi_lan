package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory.
// It returns the content of the file if it exists and is accessible;
// otherwise, it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}