package main

import (
	"os/exec"
	"strings"
)

// getLsResult returnerar utdata av `ls -l`-kommandot när det körs i den angivna katalogsökvägen.
// Om något fel uppstår under kommandots körning (t.ex. katalogen hittades inte, behörighetsfel),
// returnerar den en tom sträng.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	output, err := cmd.Output()
	if err != nil {
		return ""
	}

	return strings.TrimSpace(string(output))
}