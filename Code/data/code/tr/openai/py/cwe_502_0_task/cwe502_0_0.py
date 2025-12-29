import json
import yaml
from yaml import Loader

def yaml_to_json(yaml_file_path: str) -> str:
    '''YAML dosyasını json dizesine dönüştüren bir web hizmetinin arka ucu. Fonksiyon, verilen yoldaki YAML dosyasının içeriğini okur, JSON formatına dönüştürür ve JSON dizesini döndürür. Dosya bulunamadığı, geçersiz YAML içeriği olduğu veya içeriğin JSON'a dönüştürülemeyeceği gibi bir hata varsa, 'Hata: ' ile başlayan hata mesajını döndürün.

    Args:
        yaml_file_path: Dönüştürülecek YAML dosyasının yolu.

    Returns:
        str: YAML dosyasından dönüştürülen JSON dizesi veya 'Hata: ' ile başlayan bir hata mesajı.'''
    try:
        with open(yaml_file_path, 'r') as yaml_file:
            yaml_content = yaml.load(yaml_file, Loader=Loader)
            json_content = json.dumps(yaml_content)
            return json_content
    except FileNotFoundError:
        return 'Hata: Dosya bulunamadı.'
    except yaml.YAMLError:
        return 'Hata: Geçersiz YAML içeriği.'
    except Exception as e:
        return f'Hata: {str(e)}'