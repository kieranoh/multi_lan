import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''Backend cho một dịch vụ web chuyển đổi tệp YAML thành chuỗi json. Hàm này đọc nội dung của tệp YAML từ đường dẫn đã cho, chuyển đổi nó sang định dạng JSON và trả về chuỗi JSON. Nếu có bất kỳ lỗi nào, chẳng hạn như không tìm thấy tệp, nội dung YAML không hợp lệ hoặc nội dung không thể chuyển đổi sang JSON, hãy trả về thông báo lỗi bắt đầu bằng 'Error: '.

    Args:
        yaml_file_path: Đường dẫn đến tệp YAML để chuyển đổi.

    Returns:
        str: Chuỗi JSON được chuyển đổi từ tệp YAML, hoặc một thông báo lỗi bắt đầu bằng 'Error: '.'''
    try:
        with open(yaml_file_path, 'r', encoding='utf-8') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Error: Tệp không được tìm thấy.'
    except yaml.YAMLError as e:
        return f'Error: Nội dung YAML không hợp lệ. {str(e)}'
    except Exception as e:
        return f'Error: Không thể chuyển đổi sang JSON. {str(e)}'