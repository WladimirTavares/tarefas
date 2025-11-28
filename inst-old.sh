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


# compila sistema e copia executável para o diretório do sistema

./makelocal.sh



# copiar arquivos
#
#cp tarefas.cgi "$dirTarefas"/
#cp -r html/* "$dirTarefas"/html/

# carregar backups
#
# nos diretórios dados e downloads devem ter backups dos dados necessários
# as linhas abaixo devem ser substituídas por versão inicial do banco de dados
# aqui, eu carrego a última versão salva dos dados (backup feito em toda compilação, make.sh)
#
#cp -r dados/* "$dirTarefas"/dados
#cp -r downloads/* "$dirTarefas"/downloads

# criar o banco de dados no diretório de dados dos sistema ("$dirTarefas"/dados)

sqlite3 /usr/lib/cgi-bin/tarefas2/dados/tarefas.bd < tarefas.bd.schema20250426

# Configurar permissões de arquivos e diretórios

chown -R www-data:www-data "$dirTarefas"
