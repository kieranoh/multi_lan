package main

import (
	"io/ioutil"
	"os"
	"path/filepath"
)

// readFileFromDir reads the content of a file from a specified directory
// and returns its content as a string. If any error occurs during the
// file reading process (like file not found or permission error), it
// returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	fullPath := filepath.Join(dirPath, filename)
	data, err := ioutil.ReadFile(fullPath)
	if err != nil {
		return ""
	}
	return string(data)
}