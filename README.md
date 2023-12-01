# ITPFinalProject

1. **Clone o repositório para o seu PC:**
    * Dependendo do método de autenticação (SSH ou HTTPS), você pode dar um desses dois comandos (Acho que no seu caso provavelmente vai ser HTTPS).
      ```
      git clone https://github.com/Dio720/ITPFinalProject.git -- HTTPS
      git clone git@github.com:Dio720/ITPFinalProject.git     -- SSH
      ```
2. **Crie uma branch para commita'r suas mudanças:**
    * Abra o terminal na pasta desejada no seu PC, verifique o status atual do repositório com `git status` incluindo a branch que você ta (boa prática).
      ```
      git checkout -b <nome_da_branch>   -- Esse comando cria a branch e já muda pra ela
      git branch <nome_da_branch>        -- Cria a branch
      git checkout <nome_da_branch>      -- Muda para 
      ```
3. **Commits (FAÇA NA SUA BRANCH):**
    * Quando você fizer seus commits, vai aparecer mensagens como essa na sua branch do repo.
      ![image](https://github.com/Dio720/ITPFinalProject/assets/88192738/c54ac4c1-78f9-4936-864d-91fc8adc3a9d)
    * Clicando no hiperlink vai haver a opção de fazer um pull request, faça-o com os comentários que achar necessário, que eu te darei um retorno.

Sobre os pull requests eu também os farei e você vai dar aquela olhada pra a gente dar merge com a main.

Qualquer informação a mais que precisar e eu esqueci, vou colocar aqui.

# Compilando e Rodando pelo terminal

Primeiro de tudo, instale o CMake para seu S.O. e baixe ou clone o repo do projeto.

* **Windows:**
    1. Baixe-o pelo site oficial do CMake: https://cmake.org/download/
    2. Precisa de um desses compiladores MinGW, Clang ou Visual Studio instalados e configurados no computador.
    3. Na pasta do projeto, crie um diretório para a construção do projeto: `mkdir build && cd build`
    4. Navegue até onde o CMakeLists.txt está e execute o CMake para configurar o projeto:
        * Visual Studio:
          ```
          cmake .. -G "<versao_do_VS>"
          cmake --build . --config Release
          ```
        * MinGW:
          ```
          cmake .. -G "MinGW Makefiles" 
          cmake --build .
          ```
        * Clang:
          ```
          set CC=clang
          cmake .. -G
          ```
    5. Execute o programa (estando na pasta do executavel): `main` ou `.\main.exe`

* **Linux & MacOS (bem mais fácil):**
    1. Instale o CMake :
       Ubuntu ou Debian:
       ```
       sudo apt-get install cmake
       ```
       MacOS:
       ```
       brew install cmake
       ```
    2. Configure, compile e execute:
       ```
       mkdir build && cd build
       cmake ..
       make
       ./main
       ```
    
