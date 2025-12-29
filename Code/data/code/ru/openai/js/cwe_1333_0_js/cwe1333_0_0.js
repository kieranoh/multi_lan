const checkEmail = (email) => {
    // Определяем регулярное выражение для проверки адреса электронной почты
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Проверяем, соответствует ли переданный адрес электронной почты шаблону
    const isValid = emailPattern.test(email);
    
    // Возвращаем кортеж: [булево значение, шаблон]
    return [isValid, emailPattern.toString()];
};