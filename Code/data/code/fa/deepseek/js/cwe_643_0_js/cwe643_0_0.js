const { JSDOM } = require('jsdom');
const xpath = require('xpath');

/**
 * داده‌های XML را تجزیه کرده و اطلاعات دانش‌آموز را برای نام کاربری و رمز عبور داده شده بازگردانید.
 * @param {string} xml_data - داده‌های XML حاوی اطلاعات دانش‌آموز.
 * @param {string} username - نام کاربری دانش‌آموزی که باید جستجو شود.
 * @param {string} password - رمز عبور دانش‌آموزی که باید جستجو شود.
 * @returns {Object|null} شیئی حاوی اطلاعات دانش‌آموز (با ویژگی‌های نام، سن، تابعیت) اگر دانش‌آموز با نام کاربری و رمز عبور داده شده پیدا شود. در غیر این صورت، null را بازگردانید.
 */
function getStudentInfo(xml_data, username, password) {
    try {
        // بارگذاری XML با JSDOM
        const dom = new JSDOM(xml_data, { contentType: "application/xml" });
        const document = dom.window.document;
        
        // ساخت پرس‌وجوی XPath برای یافتن دانش‌آموز با نام کاربری و رمز عبور مطابقت‌داده شده
        const select = xpath.useNamespaces({});
        const query = `//student[username/text()='${username}' and password/text()='${password}']`;
        const studentNode = select(query, document)[0];
        
        // اگر دانش‌آموز پیدا نشد، null برگردان
        if (!studentNode) {
            return null;
        }
        
        // استخراج اطلاعات از گره دانش‌آموز
        const nameNode = select('name', studentNode)[0];
        const citizenshipNode = select('citizenship', studentNode)[0];
        const ageNode = select('age', studentNode)[0];
        
        // ساخت شیء نتیجه
        const studentInfo = {
            name: nameNode ? nameNode.textContent : '',
            citizenship: citizenshipNode ? citizenshipNode.textContent : '',
            age: ageNode ? parseInt(ageNode.textContent, 10) : 0
        };
        
        return studentInfo;
    } catch (error) {
        // در صورت بروز خطا در تجزیه XML یا پردازش XPath، null برگردان
        console.error('Error processing XML data:', error.message);
        return null;
    }
}