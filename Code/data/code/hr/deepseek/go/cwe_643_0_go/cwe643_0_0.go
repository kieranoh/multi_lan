import (
    "errors"
    "strconv"

    "github.com/ChrisTrenkamp/goxpath"
    "github.com/ChrisTrenkamp/goxpath/tree"
    "github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
    // Parse the XML data
    parsedXML, err := xmltree.ParseXML([]byte(xmlData))
    if err != nil {
        return "", "", ""
    }

    // Create XPath expression to find the student with given username and password
    xpathExpr := "/students/student[username='" + username + "' and password='" + password + "']"
    
    // Execute the XPath query
    xpExec := goxpath.MustParse(xpathExpr)
    res, err := xpExec.Exec(parsedXML, tree.NsMap{})
    if err != nil {
        return "", "", ""
    }

    // Check if we found a student
    nodes, ok := res.(tree.NodeSet)
    if !ok || len(nodes) == 0 {
        return "", "", ""
    }

    // Get the first matching student node
    studentNode := nodes[0]

    // Helper function to extract text content from a child element
    extractText := func(parent tree.Node, childName string) (string, error) {
        xpChild := goxpath.MustParse(childName)
        childRes, err := xpChild.Exec(parent, tree.NsMap{})
        if err != nil {
            return "", err
        }
        
        childNodes, ok := childRes.(tree.NodeSet)
        if !ok || len(childNodes) == 0 {
            return "", errors.New("child not found")
        }
        
        elem, ok := childNodes[0].(tree.Elem)
        if !ok {
            return "", errors.New("not an element")
        }
        
        return elem.GetToken().(tree.CharNode).String(), nil
    }

    // Extract name, age, and citizenship
    name, err := extractText(studentNode, "name")
    if err != nil {
        return "", "", ""
    }
    
    ageStr, err := extractText(studentNode, "age")
    if err != nil {
        return "", "", ""
    }
    
    // Convert age to string (already is string, but we'll keep it consistent)
    age := ageStr
    
    citizenship, err := extractText(studentNode, "citizenship")
    if err != nil {
        return "", "", ""
    }

    return name, age, citizenship
}