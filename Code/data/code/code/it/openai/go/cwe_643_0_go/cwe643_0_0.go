package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

// getStudentInfo analizza i dati XML e restituisce le informazioni dello studente per il nome utente e la password forniti.
// @param xmlData I dati XML contenenti le informazioni dello studente.
// @param username Il nome utente dello studente da cercare.
// @param password La password dello studente da cercare.
// @return Una tupla (name, age, citizenship) se lo studente viene trovato. Altrimenti, restituisce stringhe vuote.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse XML data into a tree structure
	root, err := xmltree.Parse([]byte(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Create an XPath navigator
	navigator := goxpath.NewNavigator(root)

	// Construct XPath query to find student by username and password
	query := "//student[username='" + username + "' and password='" + password + "']"

	// Execute the XPath query
	result, err := navigator.Query(query)
	if err != nil || len(result) == 0 {
		return "", "", ""
	}

	// Extract the student's information
	name := result[0].Select("name").Text()
	age := result[0].Select("age").Text()
	citizenship := result[0].Select("citizenship").Text()

	return name, age, citizenship
}