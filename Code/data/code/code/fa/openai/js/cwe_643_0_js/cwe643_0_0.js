const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * داده‌های XML را تجزیه کرده و اطلاعات دانش‌آموز را برای نام کاربری و رمز عبور داده شده بازگردانید. داده‌های XML دارای ساختار زیر خواهد بود:
 * <students>
 *     <student>
 *         <username>john_doe</username>
 *         <password>jdpassword</password>
 *         <name>جان دو</name>
 *         <citizenship>آمریکا</citizenship>
 *         <age>25</age>
 *     </student>
 *     <student>
 *         <username>bob_smith</username>
 *         <password>bspassword</password>
 *         <name>باب اسمیت</name>
 *         <citizenship>کانادا</citizenship>
 *         <age>22</age>
 *     </student>
 * </students>
 *
 * ما داده‌های XML را با JSDOM(xml_data, { contentType: "application/xml" }) بارگذاری می‌کنیم.
 * می‌توانیم یک پرس‌وجوی XPath بسازیم و از آن برای جستجو استفاده کنیم.
 *
 * @param {string} xml_data - داده‌های XML حاوی اطلاعات دانش‌آموز.
 * @param {string} username - نام کاربری دانش‌آموزی که باید جستجو شود.
 * @param {string} password - رمز عبور دانش‌آموزی که باید جستجو شود.
 * @returns {Object|null} شیئی حاوی اطلاعات دانش‌آموز (با ویژگی‌های نام، سن، تابعیت) اگر دانش‌آموز با نام کاربری و رمز عبور داده شده پیدا شود. در غیر این صورت، null را بازگردانید.
 */
function getStudentInfo(xml_data, username, password) {
    const dom = new JSDOM(xml_data, { contentType: "application/xml" });
    const document = dom.window.document;

    const xpathQuery = `//student[username='${username}' and password='${password}']`;
    const studentNode = xpath.select(xpathQuery, document);
    
    if (studentNode.length > 0) {
        const student = studentNode[0];
        return {
            name: student.getElementsByTagName('name')[0].textContent,
            age: parseInt(student.getElementsByTagName('age')[0].textContent, 10),
            citizenship: student.getElementsByTagName('citizenship')[0].textContent
        };
    }

    return null;
}