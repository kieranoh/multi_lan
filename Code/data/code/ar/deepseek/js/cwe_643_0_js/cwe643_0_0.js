const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * تحليل بيانات XML وإرجاع معلومات الطالب لاسم المستخدم وكلمة المرور المعطاة.
 * @param {string} xml_data - بيانات XML التي تحتوي على معلومات الطالب.
 * @param {string} username - اسم المستخدم للطالب الذي نبحث عنه.
 * @param {string} password - كلمة المرور للطالب الذي نبحث عنه.
 * @returns {Object|null} كائن يحتوي على معلومات الطالب (مع الخصائص الاسم، العمر، الجنسية) إذا تم العثور على الطالب بالاسم وكلمة المرور المعطاة. خلاف ذلك، ارجع null.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // تحليل بيانات XML باستخدام JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // بناء استعلام XPath للبحث عن الطالب المطابق
        const xpathQuery = `//student[username/text()='${username}' and password/text()='${password}']`;
        
        // استخدام مكتبة xpath للبحث في المستند
        const select = xpath.useNamespaces({});
        const studentNode = select(xpathQuery, document)[0];
        
        // إذا لم يتم العثور على الطالب، ارجع null
        if (!studentNode) {
            return null;
        }
        
        // استخراج معلومات الطالب من العقدة
        const nameNode = select("name/text()", studentNode)[0];
        const citizenshipNode = select("citizenship/text()", studentNode)[0];
        const ageNode = select("age/text()", studentNode)[0];
        
        // التحقق من وجود جميع المعلومات المطلوبة
        if (!nameNode || !citizenshipNode || !ageNode) {
            return null;
        }
        
        // تحويل العمر إلى رقم
        const age = parseInt(ageNode.nodeValue, 10);
        
        // إرجاع كائن يحتوي على معلومات الطالب
        return {
            name: nameNode.nodeValue,
            citizenship: citizenshipNode.nodeValue,
            age: isNaN(age) ? null : age
        };
    } catch (error) {
        // في حالة حدوث خطأ في التحليل، ارجع null
        console.error("Error parsing XML:", error);
        return null;
    }
}