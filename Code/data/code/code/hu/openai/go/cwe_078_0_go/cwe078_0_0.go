package main

import (
	"os/exec"
	"strings"
)

// getLsResult Adja vissza az `ls -l` parancs kimenetét (csak stdout), amikor egy felhasználó által megadott könyvtárban futtatják. Ha hiba lép fel a parancs végrehajtása során (pl. könyvtár nem található, jogosultsági hiba), adjon vissza egy üres karakterláncot.
//
// @param dir_path A felhasználó által megadott könyvtár, ahol az `ls -l` parancsot végrehajtják.
//
// @return Az `ls -l` parancs kimenete, vagy egy üres karakterlánc, ha hiba lép fel.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}