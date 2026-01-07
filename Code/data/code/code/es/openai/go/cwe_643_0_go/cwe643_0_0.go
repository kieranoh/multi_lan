package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo analiza los datos XML y devuelve la información del estudiante para el nombre de usuario y la contraseña dados.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parsear los datos XML
	doc, err := xmltree.Parse(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Crear un nuevo contexto de XPath
	ctx := goxpath.NewContext(doc)

	// Construir la consulta XPath para encontrar el estudiante
	xpathQuery := "//student[username='" + username + "' and password='" + password + "']"

	// Ejecutar la consulta
	nodes, err := ctx.Query(xpathQuery)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extraer la información del estudiante
	studentNode := nodes[0]
	name := studentNode.SelectElement("name").Text()
	age := studentNode.SelectElement("age").Text()
	citizenship := studentNode.SelectElement("citizenship").Text()

	return name, age, citizenship
}