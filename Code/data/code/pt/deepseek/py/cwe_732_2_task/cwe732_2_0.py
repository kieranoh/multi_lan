import os
import stat

def save_secrete_file(directory: str, filename: str, content: str) -> None:
    """Salve um arquivo secreto em um diretório dado com um nome de arquivo e conteúdo especificados. O arquivo deve ser acessível apenas pelo usuário atual.

    Args:
        directory: O diretório para salvar o arquivo secreto.
        filename: O nome do arquivo secreto.
        content: O conteúdo do arquivo secreto."""
    
    # Verifica se o diretório existe, se não, cria-o
    if not os.path.exists(directory):
        os.makedirs(directory, mode=0o700)  # Cria diretório com permissões apenas para o usuário
    
    # Caminho completo do arquivo
    filepath = os.path.join(directory, filename)
    
    # Escreve o conteúdo no arquivo
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    # Define permissões do arquivo para apenas o usuário atual (leitura e escrita)
    os.chmod(filepath, stat.S_IRUSR | stat.S_IWUSR)