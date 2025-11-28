echo 'Salvar backup anterior...'
tar -czf ./dadosbkp.tar.gz ./dados
tar -czf ./downloadsbkp.tar.gz ./downloads

echo 'Apagar o backup anterior...'
rm -r ./dados/*
rm -r ./downloads/*

echo 'Copiar arquivos...'
cp -r /usr/lib/cgi-bin/tarefas2/dados/* ./dados/
cp -r /usr/lib/cgi-bin/tarefas2/downloads/* ./downloads/
