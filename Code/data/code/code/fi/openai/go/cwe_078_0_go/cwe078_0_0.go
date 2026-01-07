package main

import (
	"os/exec"
	"strings"
)

// getLsResult palauttaa `ls -l`-komennon tuloste (vain stdout), kun se suoritetaan käyttäjän antamassa hakemistopolussa.
// Jos komennon suorittamisen aikana tapahtuu virhe (esim. hakemistoa ei löydy, käyttöoikeusvirhe), palauttaa tyhjän merkkijonon.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.CombinedOutput()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}