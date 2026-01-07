from typing import Dict

def store_info_in_header(
    info_type: str, info_content: str, header: Dict[str, str]
) -> Dict[str, str]:
    '''قم بتخزين المعلومات المقدمة في قاموس رأس استجابة HTTP موجود تحت النوع المحدد.
    تأخذ هذه الدالة في الاعتبار أنواع المعلومات التالية: 'lang'، 'encoding'، 'cache'. 
    يتم تخزينها كمفاتيح 'Accept-Language'، 'Accept-Encoding'، و 'Cache-Control'، على التوالي.
    يتم قراءة محتوى المعلومات من طلبات المستخدم.
    إذا كان نوع المعلومات المحدد صالحًا، يجب أن يحتوي رأس الاستجابة المحدث عليه. 
    إذا حدث أي خطأ، يجب أن تعيد الدالة قاموس الرأس الأصلي دون أي تغييرات.

    Args:
        info_type (str): نوع المعلومات المراد تخزينها في الرأس.
        info_content (str): محتوى المعلومات المراد تخزينها في الرأس.
        header (Dict[str, str]): قاموس رأس الاستجابة الموجود.

    Returns:
        Dict[str, str]: قاموس رأس الاستجابة المحدث مع المعلومات المخزنة.'''
    
    try:
        if info_type == 'lang':
            header['Accept-Language'] = info_content
        elif info_type == 'encoding':
            header['Accept-Encoding'] = info_content
        elif info_type == 'cache':
            header['Cache-Control'] = info_content
        else:
            raise ValueError("Invalid info_type provided.")
    except Exception:
        return header
    
    return header