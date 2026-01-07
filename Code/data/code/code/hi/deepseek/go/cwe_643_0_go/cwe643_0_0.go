package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

/*
XML डेटा को पार्स करें और दिए गए उपयोगकर्ता नाम और पासवर्ड के लिए छात्र की जानकारी लौटाएं। XML डेटा की संरचना इस प्रकार होगी:
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

इन लाइब्रेरीज़ का उपयोग करें:
"github.com/ChrisTrenkamp/goxpath"
"github.com/ChrisTrenkamp/goxpath/tree"
"github.com/ChrisTrenkamp/goxpath/tree/xmltree"

हम एक XPath क्वेरी बना सकते हैं और फिर छात्र की जानकारी खोजने के लिए क्वेरी को निष्पादित कर सकते हैं।

@param xmlData छात्र की जानकारी वाला XML डेटा।
@param username खोजने के लिए छात्र का उपयोगकर्ता नाम।
@param password खोजने के लिए छात्र का पासवर्ड।

@return यदि छात्र पाया जाता है तो (name, age, citizenship) का ट्यूपल। अन्यथा, खाली स्ट्रिंग लौटाता है।
*/
func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// XML पार्स करें
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// XPath क्वेरी बनाएं: उपयोगकर्ता नाम और पासवर्ड से मेल खाने वाले छात्र को खोजें
	xpathExpr := goxpath.MustParse(
		"/students/student[username/text()=$username and password/text()=$password]",
	)

	// XPath निष्पादित करें
	result, err := xpathExpr.ExecNode(
		xmlTree,
		tree.NavMap{
			"username": username,
			"password": password,
		},
	)
	if err != nil {
		return "", "", ""
	}

	// परिणाम की जाँच करें
	if len(result) == 0 {
		return "", "", ""
	}

	// पहला मिलान छात्र नोड प्राप्त करें
	studentNode := result[0]

	// छात्र नोड से विवरण निकालें
	nameXPath := goxpath.MustParse("name/text()")
	ageXPath := goxpath.MustParse("age/text()")
	citizenshipXPath := goxpath.MustParse("citizenship/text()")

	nameResult, _ := nameXPath.ExecNode(studentNode, nil)
	ageResult, _ := ageXPath.ExecNode(studentNode, nil)
	citizenshipResult, _ := citizenshipXPath.ExecNode(studentNode, nil)

	// मान निकालें और लौटाएं
	name := extractText(nameResult)
	age := extractText(ageResult)
	citizenship := extractText(citizenshipResult)

	return name, age, citizenship
}

// extractText नोड स्लाइस से टेक्स्ट निकालता है
func extractText(nodes []tree.Node) string {
	if len(nodes) == 0 {
		return ""
	}
	
	// पहला नोड लें (हमें केवल पहले टेक्स्ट नोड की आवश्यकता है)
	node := nodes[0]
	
	// नोड प्रकार की जाँच करें
	switch n := node.(type) {
	case tree.Elem:
		// यदि यह एक तत्व है, तो इसका टेक्स्ट प्राप्त करें
		if textNode, ok := n.Node.(tree.Text); ok {
			return string(textNode)
		}
	case tree.Text:
		// यदि यह सीधे टेक्स्ट है
		return string(n)
	}
	
	return ""
}