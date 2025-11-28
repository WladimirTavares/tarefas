# Copia dados da versao de producao na versao de desenvolvimento

echo 'Copiando arquivos da producao para desenvolvimento'
cp -rp /usr/lib/cgi-bin/tarefas2/dados/* /usr/lib/cgi-bin/tarefas2dev/dados/
cp -rp /usr/lib/cgi-bin/tarefas2/downloads/* /usr/lib/cgi-bin/tarefas2dev/downloads/
