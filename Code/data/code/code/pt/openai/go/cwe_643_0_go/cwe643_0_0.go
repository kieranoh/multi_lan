package main

import (
	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
	"strings"
)

// getStudentInfo analisa os dados XML e retorna as informações do aluno para o nome de usuário e senha fornecidos.
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Cria um novo parser para o XML
	root, err := xmltree.Parse([]byte(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Consulta XPath para encontrar o aluno com o nome de usuário e senha especificados
	xpathExpr := "//student[username='" + username + "' and password='" + password + "']"

	// Executa a consulta XPath
	nodes, err := goxpath.Query(root, xpathExpr)
	if err != nil || len(nodes) == 0 {
		return "", "", ""
	}

	// Extrai as informações do aluno encontrado
	studentNode := nodes[0]
	name := getNodeText(studentNode, "name")
	citizenship := getNodeText(studentNode, "citizenship")
	age := getNodeText(studentNode, "age")

	return name, age, citizenship
}

// getNodeText retorna o texto do nó filho especificado
func getNodeText(parent tree.Node, childName string) string {
	childNode := parent.FindChild(childName)
	if childNode != nil {
		return strings.TrimSpace(childNode.Value())
	}
	return ""
}