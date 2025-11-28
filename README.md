# 📝 Tarefas2 — Sistema de Gerenciamento de Tarefas

Um sistema simples e eficiente para gerenciamento de tarefas, desenvolvido para ser executado em um servidor web Linux ou via Docker. Ideal para estudos, deploy rápido e demonstrações.

---

## 📁 Estrutura do Projeto


---

## 🚀 Formas de Instalação

### ✔️ 1. Instalação Automática no Linux


Ao final, o sistema estará disponível em:

👉 http://localhost/tarefas2

---

### 🐳 2. Instalação via Docker (RECOMENDADA)


---

### 🔧 3. Instalação Manual (Opcional)

```bash
sudo apt update
sudo apt install apache2 php libapache2-mod-php unzip -y

sudo cp -r public/ /var/www/html/tarefas2/
sudo cp tarefas2.conf /etc/apache2/sites-available/

sudo a2ensite tarefas2.conf
sudo systemctl restart apache2
```

---

## ⚙️ Arquivo de Configuração (tarefas2.conf)

Exemplo para Apache:

```apache
<VirtualHost *:80>
   ServerName localhost
   DocumentRoot /var/www/html/tarefas2/public

   <Directory /var/www/html/tarefas2/public>
      AllowOverride All
      Require all granted
   </Directory>
</VirtualHost>
```

---

## 🐳 Docker — Arquivo docker-compose.yml

```yaml
version: "3.9"
services:
  tarefas2:
    build: .
    container_name: tarefas2_app
    ports:
      - "8080:80"
    volumes:
      - ./public:/var/www/html/tarefas2
    restart: always
```

---

## 🧪 Testes Rápidos


---

## 📄 Licença

Este projeto é livre para uso acadêmico e estudos.  
Você pode modificar e redistribuir, desde que mantenha os créditos originais.

---

## 🤝 Contribuição


---

## 📬 Contato

