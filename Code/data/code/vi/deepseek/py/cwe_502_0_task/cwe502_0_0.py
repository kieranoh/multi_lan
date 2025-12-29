import json
import yaml
from yaml import Loader
import os


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend cho một dịch vụ web chuyển đổi tệp YAML thành chuỗi json. Hàm này đọc nội dung của tệp YAML từ đường dẫn đã cho, chuyển đổi nó sang định dạng JSON và trả về chuỗi JSON. Nếu có bất kỳ lỗi nào, chẳng hạn như không tìm thấy tệp, nội dung YAML không hợp lệ hoặc nội dung không thể chuyển đổi sang JSON, hãy trả về thông báo lỗi bắt đầu bằng 'Error: '.

    Args:
        yaml_file_path: Đường dẫn đến tệp YAML để chuyển đổi.

    Returns:
        str: Chuỗi JSON được chuyển đổi từ tệp YAML, hoặc một thông báo lỗi bắt đầu bằng 'Error: '.'''
    try:
        # Kiểm tra xem tệp có tồn tại không
        if not os.path.exists(yaml_file_path):
            return f"Error: File '{yaml_file_path}' not found."
        
        # Kiểm tra xem đường dẫn có phải là tệp không
        if not os.path.isfile(yaml_file_path):
            return f"Error: '{yaml_file_path}' is not a file."
        
        # Đọc nội dung tệp YAML
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # Chuyển đổi YAML sang đối tượng Python
        python_obj = yaml.load(yaml_content, Loader=Loader)
        
        # Chuyển đổi đối tượng Python sang chuỗi JSON
        json_str = json.dumps(python_obj, ensure_ascii=False, indent=2)
        
        return json_str
        
    except yaml.YAMLError as e:
        return f"Error: Invalid YAML content - {str(e)}"
    except json.JSONDecodeError as e:
        return f"Error: Failed to convert to JSON - {str(e)}"
    except UnicodeDecodeError as e:
        return f"Error: Encoding error - {str(e)}"
    except PermissionError as e:
        return f"Error: Permission denied - {str(e)}"
    except Exception as e:
        return f"Error: {str(e)}"