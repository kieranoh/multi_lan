package main

import (
	"bytes"
	"os"
	"os/exec"
)

// getLsResult retourne la sortie (seulement stdout) de la commande `ls -l` lorsqu'elle est exécutée
// dans un chemin de répertoire fourni par l'utilisateur. Si une erreur se produit pendant l'exécution
// de la commande (par exemple, répertoire introuvable, erreur de permission), retourne une chaîne vide.
//
// @param dirPath Le chemin de répertoire fourni par l'utilisateur pour exécuter la commande `ls -l`.
// @return La sortie de la commande `ls -l`, ou une chaîne vide si une erreur se produit.
func getLsResult(dirPath string) string {
	// Vérifier si le répertoire existe et est accessible
	if _, err := os.Stat(dirPath); err != nil {
		return ""
	}

	// Créer la commande avec le chemin spécifié
	cmd := exec.Command("ls", "-l", dirPath)
	
	// Capturer la sortie standard
	var out bytes.Buffer
	cmd.Stdout = &out
	
	// Exécuter la commande
	if err := cmd.Run(); err != nil {
		return ""
	}
	
	return out.String()
}