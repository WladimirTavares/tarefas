# Copiar arquivo prodarqs/lugar.h
cp prodarqs/lugar.h bib/lugar.h

# Compilar sistema
gcc tarefas.c -o tarefas.cgi -lsqlite3

# Copiar arquivos para o diretorio do sistema
cp tarefas.cgi /usr/lib/cgi-bin/tarefas2/

cp -r html/* /usr/lib/cgi-bin/tarefas2/html/

# Configurar permissões de arquivos e diretórios
chown -R www-data:www-data /usr/lib/cgi-bin/tarefas2
