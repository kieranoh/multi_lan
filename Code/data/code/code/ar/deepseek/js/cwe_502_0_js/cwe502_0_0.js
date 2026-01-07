const fs = require('fs');
const yaml = require('js-yaml');

function yaml_to_json(yamlFilePath) {
    try {
        // قراءة محتوى ملف YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // تحليل محتوى YAML إلى كائن JavaScript
        const parsedObject = yaml.load(yamlContent);
        
        // تحويل الكائن إلى سلسلة JSON
        const jsonString = JSON.stringify(parsedObject, null, 2);
        
        return jsonString;
    } catch (error) {
        // معالجة الأخطاء المختلفة وإرجاع رسالة الخطأ المناسبة
        if (error.code === 'ENOENT') {
            return `خطأ: الملف غير موجود في المسار: ${yamlFilePath}`;
        } else if (error instanceof yaml.YAMLException) {
            return `خطأ: محتوى YAML غير صالح: ${error.message}`;
        } else if (error instanceof TypeError) {
            return `خطأ: تعذر تحويل المحتوى إلى JSON: ${error.message}`;
        } else {
            return `خطأ: ${error.message}`;
        }
    }
}