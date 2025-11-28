#!/usr/bin/env bash
set -e

echo "🚀 Atualizando sistema..."
sudo apt update && sudo apt upgrade -y

echo "📦 Instalando Apache, GCC (para CGI) e unzip..."
sudo apt install -y apache2 apache2-utils gcc unzip

echo "🧩 Habilitando CGI..."
sudo a2enmod cgi

echo "📁 Criando diretório /var/www/tarefas2..."
sudo mkdir -p /var/www/tarefas2

echo "📂 Copiando arquivos do sistema..."
sudo cp -r ./ /var/www/tarefas2

echo "🔧 Compilando CGI (se existir..."
if ls /var/www/tarefas2/src/*.c 1> /dev/null 2>&1; then
    cd /var/www/tarefas2/src
    for f in *.c; do
        gcc "$f" -o "${f%.c}.cgi"
        sudo mv "${f%.c}.cgi" /usr/lib/cgi-bin/
        sudo chmod +x /usr/lib/cgi-bin/"${f%.c}.cgi"
    done
fi

echo "📝 Criando arquivo de configuração do Apache..."
sudo tee /etc/apache2/sites-available/tarefas2.conf > /dev/null << 'EOF'
<VirtualHost *:80>
    ServerName localhost
    DocumentRoot /var/www/tarefas2

    <Directory /var/www/tarefas2>
        AllowOverride All
        Options Indexes FollowSymLinks
        Require all granted
    </Directory>

    ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/
    <Directory "/usr/lib/cgi-bin/">
        Options +ExecCGI
        AddHandler cgi-script .cgi .pl
        Require all granted
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/tarefas2-error.log
    CustomLog ${APACHE_LOG_DIR}/tarefas2-access.log combined
</VirtualHost>
EOF

echo "🔌 Habilitando site e reiniciando Apache..."
sudo a2dissite 000-default.conf || true
sudo a2ensite tarefas2.conf
sudo systemctl restart apache2

echo "✨ Instalação completa!"
echo "Acesse: http://localhost"
