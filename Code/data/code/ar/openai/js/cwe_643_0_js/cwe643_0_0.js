const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * تحليل بيانات XML وإرجاع معلومات الطالب لاسم المستخدم وكلمة المرور المعطاة. ستحتوي بيانات XML على الهيكل التالي:
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>جون دو</name>
 *         <citizenship>الولايات المتحدة الأمريكية</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>بوب سميث</name>
 *         <citizenship>كندا</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * نقوم بتحميل بيانات XML باستخدام JSDOM(xml_data, { contentType: "application/xml" })
 * يمكننا بناء استعلام XPath واستخدامه للبحث.
 *
 * @param {string} xml_data - بيانات XML التي تحتوي على معلومات الطالب.
 * @param {string} username - اسم المستخدم للطالب الذي نبحث عنه.
 * @param {string} password - كلمة المرور للطالب الذي نبحث عنه.
 * @returns {Object|null} كائن يحتوي على معلومات الطالب (مع الخصائص الاسم، العمر، الجنسية) إذا تم العثور على الطالب بالاسم وكلمة المرور المعطاة. خلاف ذلك، ارجع null.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const doc = dom.window.document;

    // بناء استعلام XPath للبحث عن الطالب
    const expr = `//student[username = "${username}" and password = "${password}"]`;
    const nodes = xpath.select(expr, doc);

    // إذا تم العثور على الطالب، ارجع معلوماته
    if (nodes.length > 0) {
        const studentNode = nodes[0];
        return {
            name: studentNode.getElementsByTagName('name')[0].textContent,
            age: studentNode.getElementsByTagName('age')[0].textContent,
            citizenship: studentNode.getElementsByTagName('citizenship')[0].textContent,
        };
    }

    // إذا لم يتم العثور على الطالب، ارجع null
    return null;
}