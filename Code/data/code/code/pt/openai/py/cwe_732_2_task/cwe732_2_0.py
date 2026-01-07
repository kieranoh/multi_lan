import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Salve um arquivo secreto em um diretório dado com um nome de arquivo e conteúdo especificados. O arquivo deve ser acessível apenas pelo usuário atual.

    Args:
        directory: O diretório para salvar o arquivo secreto.
        filename: O nome do arquivo secreto.
        content: O conteúdo do arquivo secreto."""
    
    # Cria o diretório se não existir
    os.makedirs(directory, exist_ok=True)
    
    # Cria o caminho completo do arquivo
    file_path = os.path.join(directory, filename)
    
    # Salva o conteúdo no arquivo
    with open(file_path, 'w') as file:
        file.write(content)
    
    # Altera as permissões do arquivo para que apenas o usuário atual possa acessá-lo
    os.chmod(file_path, stat.S_IRUSR | stat.S_IWUSR)