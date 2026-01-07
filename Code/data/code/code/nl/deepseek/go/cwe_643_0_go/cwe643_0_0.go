import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse de XML-gegevens
    parsedXML, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Construeer XPath-query om student te vinden met gegeven gebruikersnaam en wachtwoord
    xpathQuery := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // Compileer de XPath-query
    xpExec := goxpath.MustParse(xpathQuery)
    
    // Voer de query uit op de geparseerde XML
    result, err := xpExec.Exec(parsedXML)
    if err != nil {
        return "", "", ""
    }

    // Controleer of er een student is gevonden
    nodes, ok := result.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }

    // Haal de eerste gevonden student op (er zou er maar één moeten zijn)
    studentNode := nodes[0]

    // Helper functie om tekstinhoud van een kindelement op te halen
    getChildText := func(parent tree.Node, childName string) string {
        childXPath := goxpath.MustParse(childName)
        childResult, err := childXPath.ExecNode(parent)
        if err != nil {
            return ""
        }
        
        if textNode, ok := childResult.(tree.Elem); ok {
            return textNode.GetToken().String()
        }
        return ""
    }

    // Haal de gewenste informatie op
    name := getChildText(studentNode, "name")
    age := getChildText(studentNode, "age")
    citizenship := getChildText(studentNode, "citizenship")

    return name, age, citizenship
}