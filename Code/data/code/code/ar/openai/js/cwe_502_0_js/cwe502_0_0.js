const fs = require('fs');
const yaml = require('js-yaml');

/**
 * واجهة خلفية لخدمة ويب تقوم بتحويل ملف YAML إلى سلسلة JSON. تقوم الدالة بقراءة محتوى ملف YAML من المسار المحدد، وتحويله إلى تنسيق JSON، وإرجاع سلسلة JSON. إذا كان هناك أي خطأ، مثل عدم العثور على الملف، أو محتوى YAML غير صالح، أو عدم إمكانية تحويل المحتوى إلى JSON، يتم إرجاع رسالة الخطأ التي تبدأ بـ 'خطأ: '.
 *
 * @param {string} yamlFilePath - المسار إلى ملف YAML المراد تحويله.
 * @returns {string} - سلسلة JSON المحولة من ملف YAML، أو رسالة خطأ تبدأ بـ "خطأ: ".
 */
function yaml_to_json(yamlFilePath) {
    try {
        const fileContents = fs.readFileSync(yamlFilePath, 'utf8');
        const data = yaml.load(fileContents);
        return JSON.stringify(data);
    } catch (error) {
        return `خطأ: ${error.message}`;
    }
}