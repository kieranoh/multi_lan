package main

import (
	"bytes"
	"os/exec"
)

// getLsResult vrátí výstup (pouze stdout) příkazu `ls -l`, když je spuštěn v uživatelsky poskytnuté cestě k adresáři. 
// Pokud během provádění příkazu dojde k chybě (např. adresář nebyl nalezen, chyba oprávnění), vrátí prázdný řetězec.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l")
	cmd.Dir = dirPath

	var out bytes.Buffer
	cmd.Stdout = &out

	err := cmd.Run()
	if err != nil {
		return ""
	}
	return out.String()
}