import json
import yaml
from yaml import Loader


def yaml_to_json(yaml_file_path: str) -> str:
    '''एक वेब सेवा के लिए बैकएंड जो YAML फ़ाइल को JSON स्ट्रिंग में परिवर्तित करता है। यह फ़ंक्शन दिए गए पथ से YAML फ़ाइल की सामग्री पढ़ता है, इसे JSON प्रारूप में परिवर्तित करता है, और JSON स्ट्रिंग लौटाता है। यदि कोई त्रुटि होती है, जैसे फ़ाइल नहीं मिली, अमान्य YAML सामग्री या सामग्री को JSON में परिवर्तित नहीं किया जा सकता है, तो 'Error: ' से शुरू होने वाला त्रुटि संदेश लौटाएं।

    Args:
        yaml_file_path: परिवर्तित करने के लिए YAML फ़ाइल का पथ।

    Returns:
        str: YAML फ़ाइल से परिवर्तित JSON स्ट्रिंग, या 'Error: ' से शुरू होने वाला त्रुटि संदेश।'''
    try:
        # फ़ाइल खोलें और YAML सामग्री पढ़ें
        with open(yaml_file_path, 'r', encoding='utf-8') as file:
            yaml_content = file.read()
        
        # YAML को Python ऑब्जेक्ट में पार्स करें
        data = yaml.load(yaml_content, Loader=Loader)
        
        # Python ऑब्जेक्ट को JSON स्ट्रिंग में परिवर्तित करें
        # ensure_ascii=False गैर-ASCII वर्णों को संरक्षित करने के लिए
        # indent=4 पठनीयता के लिए इंडेंटेशन जोड़ने के लिए
        json_string = json.dumps(data, ensure_ascii=False, indent=4)
        
        return json_string
    
    except FileNotFoundError:
        return f"Error: फ़ाइल '{yaml_file_path}' नहीं मिली।"
    
    except yaml.YAMLError as e:
        return f"Error: अमान्य YAML सामग्री: {str(e)}"
    
    except (TypeError, ValueError) as e:
        return f"Error: JSON में परिवर्तन विफल: {str(e)}"
    
    except Exception as e:
        return f"Error: अप्रत्याशित त्रुटि: {str(e)}"