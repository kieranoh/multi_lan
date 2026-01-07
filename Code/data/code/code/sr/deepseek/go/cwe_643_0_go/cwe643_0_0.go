import (
    "strings"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse XML data
    xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Create XPath expression to find student with matching username and password
    xpathExpr := goxpath.MustParse(`/students/student[username="` + username + `" and password="` + password + `"]`)

    // Execute XPath query
    result, err := xpathExpr.ExecNode(xmlTree)
    if err != nil {
        return "", "", ""
    }

    // Check if any student was found
    if len(result) == 0 {
        return "", "", ""
    }

    // Get the first matching student node
    studentNode := result[0]

    // Helper function to extract text content from child element
    extractText := func(elementName string) string {
        expr := goxpath.MustParse(elementName)
        nodes, err := expr.ExecNode(studentNode)
        if err != nil || len(nodes) == 0 {
            return ""
        }
        
        // Get text content from the element
        if elem, ok := nodes[0].(tree.Elem); ok {
            return elem.ResValue()
        }
        return ""
    }

    // Extract name, age, and citizenship
    name := extractText("name")
    age := extractText("age")
    citizenship := extractText("citizenship")

    return name, age, citizenship
}