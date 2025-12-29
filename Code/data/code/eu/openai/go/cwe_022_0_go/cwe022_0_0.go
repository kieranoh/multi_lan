package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir reads the content of a specified file in the given directory path.
// If an error occurs while reading the file (e.g., the file is not found, permission error),
// it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}