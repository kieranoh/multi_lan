package main

import (
	"os/exec"
	"strings"
)

// getLsResult retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée dans un chemin de répertoire fourni par l'utilisateur.
// Si une erreur se produit pendant l'exécution de la commande (par exemple, répertoire introuvable, erreur de permission),
// retourne une chaîne vide.
func getLsResult(dirPath string) string {
	cmd := exec.Command("ls", "-l", dirPath)
	output, err := cmd.Output()
	if err != nil {
		return ""
	}
	return strings.TrimSpace(string(output))
}