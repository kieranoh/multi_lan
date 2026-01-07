/**
 * ユーザーが要求した算術式を評価し、結果を返します。式が無効であるか、評価中にエラーが発生した場合は、空の文字列を返します。
 *
 * @param {string} expr - 評価するユーザーが要求した算術式。
 * @returns {string} 算術式の結果、またはエラーが発生した場合は空の文字列。
 */
function evaluate_expression(expr) {
    // 入力が文字列でない場合や空の場合は空文字列を返す
    if (typeof expr !== 'string' || expr.trim() === '') {
        return '';
    }
    
    // 安全のため、式をトリムして前後の空白を除去
    const trimmedExpr = expr.trim();
    
    try {
        // 危険な文字や関数をフィルタリングして安全に評価
        if (!isValidExpression(trimmedExpr)) {
            return '';
        }
        
        // 数値計算用の安全な評価関数を使用
        const result = safeEvaluate(trimmedExpr);
        
        // 結果が数値でない場合は空文字列を返す
        if (typeof result !== 'number' || isNaN(result) || !isFinite(result)) {
            return '';
        }
        
        // 結果を文字列に変換して返す
        return result.toString();
    } catch (error) {
        // 評価中にエラーが発生した場合は空文字列を返す
        return '';
    }
}

/**
 * 式が安全で有効な算術式かどうかを検証します。
 * @param {string} expr - 検証する式
 * @returns {boolean} 式が有効な場合はtrue、そうでない場合はfalse
 */
function isValidExpression(expr) {
    // 許可する文字の正規表現パターン
    // 数字、小数点、基本的な算術演算子、括弧、空白
    const allowedCharsPattern = /^[\d\s+\-*/().]+$/;
    
    // 許可されていない文字が含まれている場合は無効
    if (!allowedCharsPattern.test(expr)) {
        return false;
    }
    
    // 括弧のバランスをチェック
    if (!hasBalancedParentheses(expr)) {
        return false;
    }
    
    // 連続する演算子や不正な演算子の配置をチェック
    if (hasInvalidOperatorSequence(expr)) {
        return false;
    }
    
    // 空の括弧をチェック
    if (expr.includes('()')) {
        return false;
    }
    
    return true;
}

/**
 * 括弧のバランスが取れているかどうかをチェックします。
 * @param {string} expr - チェックする式
 * @returns {boolean} 括弧のバランスが取れている場合はtrue、そうでない場合はfalse
 */
function hasBalancedParentheses(expr) {
    let balance = 0;
    
    for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') {
            balance++;
        } else if (expr[i] === ')') {
            balance--;
            
            // 閉じ括弧が開き括弧より多い場合は即時false
            if (balance < 0) {
                return false;
            }
        }
    }
    
    return balance === 0;
}

/**
 * 不正な演算子のシーケンスがないかチェックします。
 * @param {string} expr - チェックする式
 * @returns {boolean} 不正な演算子シーケンスがある場合はtrue、そうでない場合はfalse
 */
function hasInvalidOperatorSequence(expr) {
    // 連続する演算子をチェック（マイナス記号は例外として扱う）
    const operatorPattern = /[+\-*/]{2,}/;
    
    // 式の先頭または末尾が演算子（マイナスを除く）の場合
    const trimmedForCheck = expr.replace(/\s+/g, '');
    if (/^[+*/]/.test(trimmedForCheck) || /[+\-*/]$/.test(trimmedForCheck)) {
        return true;
    }
    
    // 連続する演算子をチェック（ただし、マイナスが負の数を表す場合は許可）
    const cleanedExpr = expr.replace(/\s+/g, '');
    for (let i = 0; i < cleanedExpr.length - 1; i++) {
        const current = cleanedExpr[i];
        const next = cleanedExpr[i + 1];
        
        // 演算子の後に別の演算子が続く場合（マイナスを除く）
        if ('+-*/'.includes(current) && '+-*/'.includes(next)) {
            // マイナスが負の数を表す場合は許可（例: "2*-3" や "2*(-3)"）
            if (next !== '-' || !'0123456789('.includes(cleanedExpr[i + 2])) {
                return true;
            }
        }
    }
    
    return false;
}

/**
 * 安全に算術式を評価します。
 * @param {string} expr - 評価する式
 * @returns {number} 評価結果
 */
function safeEvaluate(expr) {
    // 空白を除去
    const cleanedExpr = expr.replace(/\s+/g, '');
    
    // トークンに分割
    const tokens = tokenize(cleanedExpr);
    
    // 逆ポーランド記法に変換
    const rpnTokens = shuntingYard(tokens);
    
    // 逆ポーランド記法を評価
    return evaluateRPN(rpnTokens);
}

/**
 * 式をトークンに分割します。
 * @param {string} expr - トークン化する式
 * @returns {Array} トークンの配列
 */
function tokenize(expr) {
    const tokens = [];
    let currentNumber = '';
    
    for (let i = 0; i < expr.length; i++) {
        const char = expr[i];
        
        if ('0123456789.'.includes(char)) {
            currentNumber += char;
        } else {
            if (currentNumber !== '') {
                tokens.push(parseFloat(currentNumber));
                currentNumber = '';
            }
            
            if ('+-*/()'.includes(char)) {
                tokens.push(char);
            }
        }
    }
    
    if (currentNumber !== '') {
        tokens.push(parseFloat(currentNumber));
    }
    
    return tokens;
}

/**
 * シャンティングヤードアルゴリズムを使用してトークンを逆ポーランド記法に変換します。
 * @param {Array} tokens - トークンの配列
 * @returns {Array} 逆ポーランド記法のトークン配列
 */
function shuntingYard(tokens) {
    const output = [];
    const operators = [];
    
    // 演算子の優先順位
    const precedence = {
        '+': 1,
        '-': 1,
        '*': 2,
        '/': 2
    };
    
    for (let i = 0; i < tokens.length; i++) {
        const token = tokens[i];
        
        if (typeof token === 'number') {
            output.push(token);
        } else if (token === '(') {
            operators.push(token);
        } else if (token === ')') {
            while (operators.length > 0 && operators[operators.length - 1] !== '(') {
                output.push(operators.pop());
            }
            operators.pop(); // '(' を削除
        } else if ('+-*/'.includes(token)) {
            // 負の数を処理（例: "-3" や "2*-3"）
            if (token === '-' && (i === 0 || tokens[i - 1] === '(' || '+-*/'.includes(tokens[i - 1]))) {
                // 次のトークンが数字の場合、負の数として処理
                if (i + 1 < tokens.length && typeof tokens[i + 1] === 'number') {
                    output.push(-tokens[i + 1]);
                    i++; // 次のトークンをスキップ
                    continue;
                }
            }
            
            while (operators.length > 0 && 
                   operators[operators.length - 1] !== '(' &&
                   precedence[operators[operators.length - 1]] >= precedence[token]) {
                output.push(operators.pop());
            }
            operators.push(token);
        }
    }
    
    while (operators.length > 0) {
        output.push(operators.pop());
    }
    
    return output;
}

/**
 * 逆ポーランド記法を評価します。
 * @param {Array} rpnTokens - 逆ポーランド記法のトークン配列
 * @returns {number} 評価結果
 */
function evaluateRPN(rpnTokens) {
    const stack = [];
    
    for (const token of rpnTokens) {
        if (typeof token === 'number') {
            stack.push(token);
        } else if ('+-*/'.includes(token)) {
            if (stack.length < 2) {
                throw new Error('Invalid expression');
            }
            
            const b = stack.pop();
            const a = stack.pop();
            
            switch (token) {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    if (b === 0) {
                        throw new Error('Division by zero');
                    }
                    stack.push(a / b);
                    break;
            }
        }
    }
    
    if (stack.length !== 1) {
        throw new Error('Invalid expression');
    }
    
    return stack[0];
}