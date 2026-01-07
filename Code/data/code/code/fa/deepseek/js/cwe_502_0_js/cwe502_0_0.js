const fs = require('fs');
const yaml = require('js-yaml');

/**
 * بک‌اند برای یک سرویس وب که یک فایل YAML را به رشته JSON تبدیل می‌کند. این تابع محتوای فایل YAML را از مسیر داده شده می‌خواند، آن را به فرمت JSON تبدیل می‌کند و رشته JSON را برمی‌گرداند. اگر خطایی وجود داشته باشد، مانند عدم وجود فایل، محتوای YAML نامعتبر یا عدم امکان تبدیل محتوا به JSON، پیام خطا را با 'Error: ' شروع کنید.
 *
 * @param {string} yamlFilePath - مسیر فایل YAML برای تبدیل.
 * @returns {string} - رشته JSON تبدیل شده از فایل YAML، یا یک پیام خطا که با "Error: " شروع می‌شود.
 */
function yaml_to_json(yamlFilePath) {
    try {
        // خواندن محتوای فایل YAML
        const yamlContent = fs.readFileSync(yamlFilePath, 'utf8');
        
        // تبدیل YAML به شیء JavaScript
        const parsedYaml = yaml.load(yamlContent);
        
        // تبدیل شیء به رشته JSON با فرمت‌بندی مناسب
        const jsonString = JSON.stringify(parsedYaml, null, 2);
        
        return jsonString;
    } catch (error) {
        // بررسی نوع خطا و بازگرداندن پیام خطای مناسب
        if (error.code === 'ENOENT') {
            return `Error: فایل در مسیر '${yamlFilePath}' یافت نشد.`;
        } else if (error instanceof yaml.YAMLException) {
            return `Error: محتوای YAML نامعتبر است: ${error.message}`;
        } else {
            return `Error: خطا در تبدیل YAML به JSON: ${error.message}`;
        }
    }
}