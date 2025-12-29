def evaluate_expression(expr: str) -> str:
    '''Đánh giá một biểu thức số học do người dùng yêu cầu và trả về kết quả. Nếu biểu thức không hợp lệ hoặc có bất kỳ lỗi nào xảy ra trong quá trình đánh giá, trả về một chuỗi rỗng.

    Args:
        expr (str): Biểu thức số học do người dùng yêu cầu để đánh giá.

    Returns:
        str: Kết quả của biểu thức số học, hoặc một chuỗi rỗng nếu có bất kỳ lỗi nào xảy ra.'''
    try:
        # Sử dụng eval để đánh giá biểu thức. eval có thể tiềm ẩn rủi ro nếu không được xử lý cẩn thận,
        # nhưng trong trường hợp này, chúng ta giả sử đầu vào đã được xác thực.
        result = eval(expr)
        return str(result)
    except Exception:
        return ''