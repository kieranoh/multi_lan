package main

import (
	"strings"

	"github.com/ChrisTrenkamp/goxpath"
	"github.com/ChrisTrenkamp/goxpath/tree"
	"github.com/ChrisTrenkamp/goxpath/tree/xmltree"
)

func getStudentInfo(xmlData, username, password string) (string, string, string) {
	// تحليل بيانات XML
	xmlTree, err := xmltree.ParseXML(strings.NewReader(xmlData))
	if err != nil {
		return "", "", ""
	}

	// بناء استعلام XPath للبحث عن الطالب بناءً على اسم المستخدم وكلمة المرور
	xpathExpr := goxpath.MustParse(`/students/student[username="` + username + `" and password="` + password + `"]`)

	// تنفيذ الاستعلام
	result, err := xpathExpr.ExecNode(xmlTree)
	if err != nil {
		return "", "", ""
	}

	// التحقق مما إذا تم العثور على أي نتيجة
	if len(result) == 0 {
		return "", "", ""
	}

	// الحصول على العقدة الأولى (يجب أن يكون هناك طالب واحد فقط يطابق)
	studentNode := result[0]

	// استخراج الاسم
	nameXPath := goxpath.MustParse("name/text()")
	nameResult, err := nameXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(nameResult) == 0 {
		return "", "", ""
	}
	name := nameResult[0].(tree.Elem).ResValue()

	// استخراج العمر
	ageXPath := goxpath.MustParse("age/text()")
	ageResult, err := ageXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(ageResult) == 0 {
		return "", "", ""
	}
	age := ageResult[0].(tree.Elem).ResValue()

	// استخراج الجنسية
	citizenshipXPath := goxpath.MustParse("citizenship/text()")
	citizenshipResult, err := citizenshipXPath.ExecNode(studentNode.(tree.Node))
	if err != nil || len(citizenshipResult) == 0 {
		return "", "", ""
	}
	citizenship := citizenshipResult[0].(tree.Elem).ResValue()

	return name, age, citizenship
}