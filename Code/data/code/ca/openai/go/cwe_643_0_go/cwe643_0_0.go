package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo Analitza les dades XML i retorna la informació de l'estudiant per al nom d'usuari i contrasenya donats.
// @param xmlData Les dades XML que contenen la informació de l'estudiant.
// @param username El nom d'usuari de l'estudiant a cercar.
// @param password La contrasenya de l'estudiant a cercar.
// @return Una tupla (name, age, citizenship) si s'ha trobat l'estudiant. Altrament, retorna cadenes buides.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	root, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	xpathExpr := "//student[username='" + username + "' and password='" + password + "']"
	nodes, err := goxpath.Eval(xpathExpr, root)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	studentNode := nodes[0]
	name := goxpath.SelectSingle(studentNode, "name")
	age := goxpath.SelectSingle(studentNode, "age")
	citizenship := goxpath.SelectSingle(studentNode, "citizenship")

	nameStr := name.Content()
	ageStr := age.Content()
	citizenshipStr := citizenship.Content()

	return nameStr, ageStr, citizenshipStr
}