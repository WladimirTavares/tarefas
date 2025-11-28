# script de instalação do tarefas

# variaveis globais

dirBase=/usr/lib/cgi-bin
#dirTarefas=/usr/lib/cgi-bin/tarefas2dev
dirTarefas=/usr/lib/cgi-bin/tarefas2


# criação dos diretórios do sistema

#mkdir "$dirBase"
mkdir "$dirTarefas"


mkdir "$dirTarefas"/dados
mkdir "$dirTarefas"/dados/tarefas
mkdir "$dirTarefas"/dados/trabalhos

mkdir "$dirTarefas"/downloads
mkdir "$dirTarefas"/downloads/tarefas
mkdir "$dirTarefas"/downloads/trabalhos

mkdir "$dirTarefas"/html


# as permissões do diretório de dados devem restringir escrita
# para evitar que diretórios sejam removidos de forma indevida
# além disso, alguns subdiretórios do diretório de dados devem
# ter permissão de escrita restrita
#
# o mesmo do diretório de respostas

# copiar arquivo do codemirror

cp -r downloads/editor.bundle.js "$dirTarefas"/downloads

# compila sistema e copia executável para o diretório do sistema

./makelocal.sh

# criar o banco de dados no diretório de dados dos sistema ("$dirTarefas"/dados)

sqlite3 /usr/lib/cgi-bin/tarefas2/dados/tarefas.bd < tarefas.bd.schema20250426

# Configurar permissões de arquivos e diretórios

chown -R www-data:www-data "$dirTarefas"
