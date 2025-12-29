package main

import (
	"os/exec"
	"strings"
)

// `ls -l` agindua erabiltzaileak emandako direktorio bidean exekutatzean lortutako irteera (soilik stdout) itzuli. Agindua exekutatzean errore bat gertatzen bada (adibidez, direktorioa aurkitu ez, baimen errorea), itzuli string huts bat.
//
// @param dir_path `ls -l` agindua exekutatzeko erabiltzaileak emandako direktorio bidea.
//
// @return `ls -l` aginduaren irteera, edo errore bat gertatzen bada string huts bat.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}