/**
 * یک عبارت حسابی درخواست شده توسط کاربر را ارزیابی کرده و نتیجه را برمی‌گرداند. اگر عبارت نامعتبر باشد یا در حین ارزیابی خطایی رخ دهد، یک رشته خالی برمی‌گرداند.
 *
 * @param {string} expr - عبارت حسابی درخواست شده توسط کاربر برای ارزیابی.
 * @returns {string} نتیجه عبارت حسابی، یا یک رشته خالی اگر خطایی رخ دهد.
 */
function evaluate_expression(expr) {
    try {
        // بررسی اینکه عبارت خالی نباشد
        if (!expr || expr.trim() === '') {
            return '';
        }

        // حذف فاصله‌های اضافی
        const trimmedExpr = expr.trim();
        
        // بررسی امنیتی: جلوگیری از اجرای کدهای خطرناک
        // فقط اجازه کاراکترهای مجاز در عبارات ریاضی را می‌دهیم
        const allowedChars = /^[\d+\-*/().\s,%]+$/;
        if (!allowedChars.test(trimmedExpr)) {
            return '';
        }

        // بررسی توازن پرانتزها
        let balance = 0;
        for (let i = 0; i < trimmedExpr.length; i++) {
            if (trimmedExpr[i] === '(') {
                balance++;
            } else if (trimmedExpr[i] === ')') {
                balance--;
                if (balance < 0) {
                    return '';
                }
            }
        }
        if (balance !== 0) {
            return '';
        }

        // بررسی ساختار اولیه عبارت
        // نباید با عملگر شروع یا پایان یابد (به جز علامت منفی برای اعداد منفی)
        const firstChar = trimmedExpr[0];
        const lastChar = trimmedExpr[trimmedExpr.length - 1];
        const operators = ['+', '-', '*', '/', '%'];
        
        if (operators.includes(lastChar)) {
            return '';
        }
        
        // اگر با عملگر شروع شود، فقط علامت منفی مجاز است
        if (operators.includes(firstChar) && firstChar !== '-') {
            return '';
        }

        // ارزیابی عبارت با استفاده از Function برای امنیت بیشتر
        // استفاده از eval مستقیماً خطرناک است، بنابراین از Function استفاده می‌کنیم
        // که در محدوده خود اجرا می‌شود
        const result = new Function(`return ${trimmedExpr}`)();
        
        // بررسی اینکه نتیجه یک عدد معتبر باشد
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // تبدیل نتیجه به رشته و بازگرداندن
        return String(result);
    } catch (error) {
        // در صورت بروز هرگونه خطا، رشته خالی برمی‌گردانیم
        return '';
    }
}