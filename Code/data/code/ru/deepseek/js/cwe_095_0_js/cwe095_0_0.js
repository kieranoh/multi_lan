/**
 * Оцените запрашиваемое пользователем арифметическое выражение и верните результат.
 * Если выражение недействительно или возникает ошибка во время оценки, верните пустую строку.
 *
 * @param {string} expr - Запрашиваемое пользователем арифметическое выражение для оценки.
 * @returns {string} Результат арифметического выражения или пустая строка, если возникает ошибка.
 */
function evaluate_expression(expr) {
    try {
        // Проверка на пустую строку или null/undefined
        if (!expr || typeof expr !== 'string') {
            return '';
        }
        
        // Удаление лишних пробелов
        const trimmedExpr = expr.trim();
        if (trimmedExpr === '') {
            return '';
        }
        
        // Проверка на потенциально опасные конструкции
        const dangerousPatterns = [
            /eval\s*\(/i,
            /Function\s*\(/i,
            /setTimeout\s*\(/i,
            /setInterval\s*\(/i,
            /document\./i,
            /window\./i,
            /process\./i,
            /require\s*\(/,
            /import\s*\(/,
            /`/,
            /\$\{/
        ];
        
        for (const pattern of dangerousPatterns) {
            if (pattern.test(trimmedExpr)) {
                return '';
            }
        }
        
        // Проверка на допустимые символы
        // Разрешаем цифры, операторы, скобки, точки для десятичных чисел и пробелы
        const validChars = /^[0-9+\-*/().\s]+$/;
        if (!validChars.test(trimmedExpr)) {
            return '';
        }
        
        // Проверка баланса скобок
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
        
        // Проверка на некорректные последовательности операторов
        const operatorPattern = /[+\-*/]{2,}/;
        if (operatorPattern.test(trimmedExpr)) {
            return '';
        }
        
        // Проверка на выражение, начинающееся или заканчивающееся оператором (кроме унарного минуса)
        const startsWithInvalidOp = /^[+*/]/;
        const endsWithInvalidOp = /[+\-*/]$/;
        if (startsWithInvalidOp.test(trimmedExpr) || endsWithInvalidOp.test(trimmedExpr)) {
            return '';
        }
        
        // Проверка на корректность десятичных чисел
        const decimalPattern = /\.\d*\./;
        if (decimalPattern.test(trimmedExpr)) {
            return '';
        }
        
        // Функция для определения приоритета операторов
        const getPrecedence = (op) => {
            if (op === '+' || op === '-') return 1;
            if (op === '*' || op === '/') return 2;
            return 0;
        };
        
        // Функция для применения оператора к двум операндам
        const applyOperator = (a, b, op) => {
            a = parseFloat(a);
            b = parseFloat(b);
            
            switch (op) {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': 
                    if (b === 0) {
                        throw new Error('Division by zero');
                    }
                    return a / b;
                default: throw new Error('Invalid operator');
            }
        };
        
        // Преобразование выражения в обратную польскую нотацию (RPN)
        const shuntingYard = (expression) => {
            const output = [];
            const operators = [];
            
            let i = 0;
            while (i < expression.length) {
                const ch = expression[i];
                
                // Пропускаем пробелы
                if (ch === ' ') {
                    i++;
                    continue;
                }
                
                // Если это цифра или точка (начало числа)
                if ((ch >= '0' && ch <= '9') || ch === '.') {
                    let num = '';
                    while (i < expression.length && 
                          ((expression[i] >= '0' && expression[i] <= '9') || expression[i] === '.')) {
                        num += expression[i];
                        i++;
                    }
                    output.push(num);
                    continue;
                }
                
                // Если это оператор
                if (ch === '+' || ch === '-' || ch === '*' || ch === '/') {
                    // Обработка унарного минуса
                    if (ch === '-' && (i === 0 || expression[i-1] === '(' || 
                        ['+', '-', '*', '/'].includes(expression[i-1]))) {
                        // Это унарный минус, добавляем 0 перед ним
                        output.push('0');
                    }
                    
                    while (operators.length > 0 && 
                          operators[operators.length - 1] !== '(' &&
                          getPrecedence(operators[operators.length - 1]) >= getPrecedence(ch)) {
                        output.push(operators.pop());
                    }
                    operators.push(ch);
                    i++;
                    continue;
                }
                
                // Если это открывающая скобка
                if (ch === '(') {
                    operators.push(ch);
                    i++;
                    continue;
                }
                
                // Если это закрывающая скобка
                if (ch === ')') {
                    while (operators.length > 0 && operators[operators.length - 1] !== '(') {
                        output.push(operators.pop());
                    }
                    if (operators.length === 0) {
                        throw new Error('Mismatched parentheses');
                    }
                    operators.pop(); // Удаляем '('
                    i++;
                    continue;
                }
                
                // Недопустимый символ
                throw new Error('Invalid character');
            }
            
            // Выталкиваем оставшиеся операторы
            while (operators.length > 0) {
                const op = operators.pop();
                if (op === '(' || op === ')') {
                    throw new Error('Mismatched parentheses');
                }
                output.push(op);
            }
            
            return output;
        };
        
        // Вычисление выражения в RPN
        const evaluateRPN = (tokens) => {
            const stack = [];
            
            for (const token of tokens) {
                if (!isNaN(parseFloat(token)) && isFinite(token)) {
                    // Это число
                    stack.push(parseFloat(token));
                } else {
                    // Это оператор
                    if (stack.length < 2) {
                        throw new Error('Invalid expression');
                    }
                    const b = stack.pop();
                    const a = stack.pop();
                    const result = applyOperator(a, b, token);
                    stack.push(result);
                }
            }
            
            if (stack.length !== 1) {
                throw new Error('Invalid expression');
            }
            
            return stack[0];
        };
        
        // Преобразуем выражение в RPN и вычисляем
        const rpnTokens = shuntingYard(trimmedExpr);
        const result = evaluateRPN(rpnTokens);
        
        // Проверка на корректность результата
        if (typeof result !== 'number' || !isFinite(result)) {
            return '';
        }
        
        // Возвращаем результат как строку
        // Убираем лишние нули после десятичной точки
        return result.toString().replace(/(\.\d*?[1-9])0+$/, '$1').replace(/\.0+$/, '');
        
    } catch (error) {
        // В случае любой ошибки возвращаем пустую строку
        return '';
    }
}