package main

import (
	"io/ioutil"
	"path/filepath"
)

// readFileFromDir reads the content of a file specified by filename in the directory dirPath.
// It returns the content of the file as a string if the file is accessible; otherwise, it returns an empty string.
func readFileFromDir(filename, dirPath string) string {
	filePath := filepath.Join(dirPath, filename)
	content, err := ioutil.ReadFile(filePath)
	if err != nil {
		return ""
	}
	return string(content)
}