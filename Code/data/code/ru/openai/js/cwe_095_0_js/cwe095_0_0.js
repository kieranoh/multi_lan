function evaluate_expression(expr) {
    try {
        // Используем eval для оценки арифметического выражения
        const result = eval(expr);
        
        // Проверяем, является ли результат допустимым числом
        if (typeof result === 'number' && !isNaN(result)) {
            return result.toString();
        } else {
            return '';
        }
    } catch (error) {
        // Возвращаем пустую строку в случае ошибки
        return '';
    }
}