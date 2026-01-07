const checkEmail = (email) => {
    // Регулярний вираз для перевірки валідності електронної пошти
    const emailPattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    
    // Перевірка електронної пошти на відповідність шаблону
    const isValid = emailPattern.test(email);
    
    // Повертаємо результат перевірки та шаблон
    return [isValid, emailPattern.toString()];
};