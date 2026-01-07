import ast
import operator

def evaluate_expression(expr: str) -> str:
    '''एक उपयोगकर्ता-निर्धारित अंकगणितीय अभिव्यक्ति का मूल्यांकन करें और परिणाम लौटाएं। यदि अभिव्यक्ति अमान्य है या मूल्यांकन के दौरान कोई त्रुटि होती है, तो एक खाली स्ट्रिंग लौटाएं।

    Args:
        expr (str): मूल्यांकन के लिए उपयोगकर्ता-निर्धारित अंकगणितीय अभिव्यक्ति।

    Returns:
        str: अंकगणितीय अभिव्यक्ति का परिणाम, या यदि कोई त्रुटि होती है तो एक खाली स्ट्रिंग।'''
    
    # सुरक्षित ऑपरेटर मैपिंग
    _safe_operators = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Pow: operator.pow,
        ast.FloorDiv: operator.floordiv,
        ast.Mod: operator.mod,
        ast.USub: operator.neg,
        ast.UAdd: operator.pos,
    }
    
    def _eval_node(node):
        """AST नोड का सुरक्षित रूप से मूल्यांकन करें।"""
        if isinstance(node, ast.Num):  # Python 3.7 और नीचे के लिए
            return node.n
        elif isinstance(node, ast.Constant):  # Python 3.8+ के लिए
            return node.value
        elif isinstance(node, ast.BinOp):
            try:
                left = _eval_node(node.left)
                right = _eval_node(node.right)
                op_type = type(node.op)
                if op_type in _safe_operators:
                    # शून्य से विभाजन की जाँच करें
                    if op_type is ast.Div and right == 0:
                        raise ZeroDivisionError("शून्य से विभाजन")
                    elif op_type is ast.FloorDiv and right == 0:
                        raise ZeroDivisionError("शून्य से फ्लोर विभाजन")
                    elif op_type is ast.Mod and right == 0:
                        raise ZeroDivisionError("शून्य से मॉड्यूलो")
                    return _safe_operators[op_type](left, right)
                else:
                    raise ValueError("असमर्थित ऑपरेटर")
            except (ZeroDivisionError, ValueError, TypeError):
                raise
        elif isinstance(node, ast.UnaryOp):
            operand = _eval_node(node.operand)
            op_type = type(node.op)
            if op_type in _safe_operators:
                return _safe_operators[op_type](operand)
            else:
                raise ValueError("असमर्थित यूनरी ऑपरेटर")
        else:
            raise ValueError("असमर्थित AST नोड")
    
    try:
        # इनपुट स्ट्रिंग की जाँच करें
        if not expr or not isinstance(expr, str):
            return ""
        
        # अभिव्यक्ति को पार्स करें
        tree = ast.parse(expr, mode='eval')
        
        # AST का मूल्यांकन करें
        result = _eval_node(tree.body)
        
        # परिणाम को स्ट्रिंग में बदलें
        # पूर्णांकों के लिए दशमलव बिंदु से बचें
        if isinstance(result, int):
            return str(result)
        elif isinstance(result, float):
            # यदि परिणाम पूर्णांक है तो दशमलव भाग हटाएं
            if result.is_integer():
                return str(int(result))
            else:
                # उचित सटीकता बनाए रखें
                return str(result)
        else:
            # अन्य प्रकारों के लिए (जैसे जटिल संख्याएँ)
            return str(result)
            
    except (SyntaxError, ValueError, ZeroDivisionError, TypeError, 
            MemoryError, RecursionError, AttributeError, 
            NameError, KeyError, IndexError):
        # किसी भी त्रुटि के मामले में खाली स्ट्रिंग लौटाएं
        return ""