package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir reads the content of a file from the specified directory.
// If an error occurs during the reading process (e.g., file not found, permission error),
// it returns an empty string. The returned string will be freed by the caller.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)

	data, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}

	return string(data)
}