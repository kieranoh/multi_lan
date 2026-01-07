package main

import (
	"errors"
	"strconv"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parsear el XML
	xmlTree, err := xmltree.ParseXML(xmlData)
	if err != nil {
		return "", "", ""
	}

	// Construir la consulta XPath para encontrar el estudiante con el username y password dados
	xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
	xpExec := goxpath.MustParse(xpathExpr)

	// Ejecutar la consulta
	res, err := xpExec.Exec(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// Verificar si se encontró algún resultado
	nodes, ok := res.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// Tomar el primer nodo estudiante encontrado
	studentNode := nodes[0]

	// Función auxiliar para extraer el texto de un elemento hijo
	getChildText := func(parent tree.Node, childName string) (string, error) {
		childXPath := goxpath.MustParse(childName)
		res, err := childXPath.Exec(parent)
		if err != nil {
			return "", err
		}

		nodes, ok := res.(tree.NodeSet)
		if !ok || len(nodes) == 0 {
			return "", errors.New("elemento no encontrado")
		}

		elem, ok := nodes[0].(tree.Elem)
		if !ok {
			return "", errors.New("no es un elemento")
		}

		return elem.ResValue(), nil
	}

	// Extraer los campos requeridos
	name, err := getChildText(studentNode, "name")
	if err != nil {
		return "", "", ""
	}

	citizenship, err := getChildText(studentNode, "citizenship")
	if err != nil {
		return "", "", ""
	}

	ageStr, err := getChildText(studentNode, "age")
	if err != nil {
		return "", "", ""
	}

	// Convertir la edad a string (ya que el retorno espera string)
	// Validar que sea un número válido
	_, err = strconv.Atoi(ageStr)
	if err != nil {
		return "", "", ""
	}

	return name, ageStr, citizenship
}