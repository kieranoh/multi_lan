const checkEmail = (email) => {
    // تعبير منتظم للتحقق من صحة عنوان البريد الإلكتروني
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // التحقق من مطابقة البريد الإلكتروني للنمط
    const isValid = emailPattern.test(email);
    
    return [isValid, emailPattern];
};