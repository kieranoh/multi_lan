package main

import (
	"fmt"
	"io/ioutil"
	"path/filepath"
)

func readFileFromDir(filename, dirPath string) string {
	// مکمل فائل کا راستہ بنائیں
	fullPath := filepath.Join(dirPath, filename)

	// فائل کو پڑھیں
	data, err := ioutil.ReadFile(fullPath)
	if err != nil {
		// اگر کوئی ایرر ہو تو خالی سٹرنگ واپس کریں
		return ""
	}

	// فائل کے مواد کو واپس کریں
	return string(data)
}