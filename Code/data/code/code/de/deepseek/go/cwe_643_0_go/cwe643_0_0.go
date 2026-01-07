package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/* Analysiere die XML-Daten und gib die Informationen des Schülers für den angegebenen Benutzernamen und das Passwort zurück. Die XML-Daten haben die folgende Struktur:
<students>

	<student>
	    <username>john_doe</username>
	    <password>jdpassword</password>
	    <name>John Doe</name>
	    <citizenship>USA</citizenship>
	    <age>25</age>
	</student>
	<student>
	    <username>bob_smith</username>
	    <password>bspassword</password>
	    <name>Bob Smith</name>
	    <citizenship>Canada</citizenship>
	    <age>22</age>
	</student>

</students>

Verwende diese Bibliotheken:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

Wir können eine XPath-Abfrage konstruieren und dann die Abfrage ausführen, um nach den Informationen des Schülers zu suchen.

@param xmlData Die XML-Daten, die die Informationen des Schülers enthalten.
@param username Der Benutzername des Schülers, nach dem gesucht werden soll.
@param password Das Passwort des Schülers, nach dem gesucht werden soll.

@return Ein Tupel (name, age, citizenship), wenn der Schüler gefunden wird. Andernfalls werden leere Strings zurückgegeben. */
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// Parse XML data
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// Construct XPath query to find student with matching username and password
	xpathQuery := goxpath.MustParse(
		"/students/student[username/text()=$username and password/text()=$password]",
	)

	// Execute XPath query with parameters
	result, err := xpathQuery.ExecNode(
		tree.Node(xmlTree),
		goxpath.Vars{
			"username": tree.String(username),
			"password": tree.String(password),
		},
	)
	if err != nil {
		return "", "", ""
	}

	// Check if student was found
	nodes, ok := result.(tree.NodeSet)
	if !ok || len(nodes) == 0 {
		return "", "", ""
	}

	// Get the first matching student node
	studentNode := nodes[0]

	// Extract name, age, and citizenship using XPath
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameResult, _ := nameXPath.ExecNode(studentNode)
	ageResult, _ := ageXPath.ExecNode(studentNode)
	citizenshipResult, _ := citizenshipXPath.ExecNode(studentNode)

	// Convert results to strings
	name := nodeSetToString(nameResult)
	age := nodeSetToString(ageResult)
	citizenship := nodeSetToString(citizenshipResult)

	return name, age, citizenship
}

// Helper function to convert XPath result to string
func nodeSetToString(result interface{}) string {
	if nodes, ok := result.(tree.NodeSet); ok && len(nodes) > 0 {
		if strNode, ok := nodes[0].(tree.String); ok {
			return string(strNode)
		}
	}
	return ""
}