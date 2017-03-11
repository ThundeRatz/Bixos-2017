# Git e Github
---
Hoje em dia, em geral, ninguém programa sozinho. O git é uma ferramenta criada para facilitar na colaboração distribuição de códigos. O git pode ser usado em servidores privados, mas no geral, os códigos são enviados para o Github, um site que hospeda os códigos e que também tem uma interface gráfica simples, que facilita a visualização de mudanças feitas por outras pessoas.

Nesse arquivo, tento explicar o uso básico do github e branches, até porque meu conhecimento de git se limita, basicamente, a isso. No caso de alguma dúvida, podem perguntar para alguém da equipe, mas a resposta provavelmente está no google ou no _**stack overflow**_. ~~melhor site~~

## Começando
O git é instalado como qualquer outro programa, seja por um instalador do Windows ou pelo package manager do linux, pelo comando `yum/dnf/apt-get install git`(dependendo da sua distribuição). Depois de instalado, ele já pode ser usado em um terminal, independente do sistema operacional. Uma das primeiras coisas a se fazer é configurar sua conta do github. Isso é importante para seus commits serem mais facilmente identificados. Para isso, é preciso executar 2 comandos:

```
git config --global user.name "Seu Nome"
git config --global user.email seuemail@exemplo.com
```
Depois disso, já podemos começar a usar o git.

## Importando um repositório

Na equipe(e em geral), cada projeto tem seu repositório, como é chamada a *"pasta"* que guarda os arquivps no servidor. Para começar a trabalhar em qualquer repositório, precisamos importar ele no seu computador. Para fazer isso, primeiro navegue até a pasta em que você quer importar o repositório, usando o comando `cd`. Então, basta usar o comando `git clone`, com a URL do repositório no final, para clonar no seu computador. Esse link pode ser obtido indo até o repositório no Github, e clicando em *Clone or Download*. No caso desse repositório, o comando seria:

`git clone https://github.com/ThundeRatz/Bixos-2017.git`

## Trabalhando com o repositório

Agora que você já tem uma cópia do repositório no seu computador, já podemos começar a trabalhar com o código, fazendo as alterações que quisermos. No entanto, é sempre bom executar um `git pull` antes de começar a trabalhar(para evitar conflitos por seu repositório estar desatualizado).  Depois que tivermos feitas as mudanças e estivermos satisfeitos com o código, podemos enviá-lo para o Github. 

O git trabalha com commits, que, em geral, são pequenos "patches" que você e as outras pessoas mandam para o repositório. Esses commits ajudam a realizar apenas as alterações necessárias no repositório remoto(o do Github), e ao mesmo tempo, ajudam a acompanhar todo o histórico de mudanças.

Primeiro, precisamos adicionar as nossas mudanças em um commit. Para vermos essas mudanças, usamos os comandos `git status`(que mostra um resumo) ou `git diff`(que mostra as mudanças linha por linha). Para realmente adicionar no commit, usamos o comando `git add`. Com esse comando, podemos selecionar especificamente quais arquivos ou pastas queremos adicionar no commit, ou podemos usar `git add .` ou `git add -A` para adicionar todos de uma vez.

Depois disso, para criar um commit, usamos o comando `git commit`. Esse comando abre uma janela do editor de texto padrão do sistema operacional, para adicionar uma mensagem de resumo do commit. Esses editores costumam ser meio difíceis de usar, então, pessoalmente, gosto de  o modificador `-m`, que permite enviar a mensagem diretamente. O comando fica assim:

`git commit -m "Essa é a mensagem do commit"`

Os commits são locais, ou seja, eles são só da sua máquina. Eles normalmente são enviados um por um para o servidor, mas você pode usá-los pra se organizar, sem enviar. Depois que você tiver feito quantos commit quiser, e achar que está pronto para enviar seu código para o github, basta executar o comando `git push`. No caso de algum erro, provavelmente seu repositório local está desatualizado, e isso pode ser resolvido com um pull. Caso haja problemas no auto-merge, eu ensino a resolver na parte do uso de branches. Caso não dê nenhum erro, o seu código já está no github. Em resumo, um commit fica normalmente assim:

```
git add .
git commit -m "Mensagem"
git push
```
_PS: Podemos adicionar diretamente ao commit o modificador `-a`, que faz a função do add. No entanto, isso só funciona para modificações de arquivos, sendo que para arquivos que foram criados nesse commit o comando add ainda é necessário_

## Usando branches

O que passei até agora é o básico do github. É o necessário para trabalhar em uma única "versão" do código por vez. No entanto, no git existe a possibilidade de se fazer alterações no código(e compartilhar com outros usuários), sem comprometer um código que já está funcionando. O código do branch *master*(o principal, e o único que existe por padrão) deve ser sempre estável e funcional, com testes sendo feitos em outros branches.

Para criar um novo branch, primeiro execute um `pull`, para garantir que os arquivos estão atualizados. Então, execute `git checkout -b [Nome do branch]`. O modificador `-b` serve para criar um novo branch. Agora, você está em um branch diferente do master, podendo fazer mudanças e commits sem alterar o código original. Para mandar esse branch para o github e criar um branch remoto, usamos o comando `git push origin [Nome do branch]`. Depois da primeira vez, podemos usar o push direto(desde que estejamos no branch certo).

Para mudar de branch, podemos usar o comando `git checkout [Nome do branch]`. Tome cuidado antes de fazer isso, qualquer mudança que você tiver feito e não estiver em um commit será jogada fora. Para evitar isso, crie um commit ou use o comando `git stash` que guarda todas as mudanças sem commit em uma pasta separada, que pode ser recuperada depois.

Se você estiver satisfeito com o trabalho de um branch, e quiser juntá-lo ao master, basta voltar para o master e usar o comando `git merge [Nome do branch]`.
No entanto, caso a mesma parte de um mesmo arquivo tenha sido modificada nos 2 branches, o auto-merge vai falhar, e te avisar quais os arquivos problemáticos. (o mesmo pode acontecer quando você altera coisas sem antes dar pull). Nesses arquivos, ficam as duas versões diferentes daquela parte. Você pode escolher uma delas, e então usar o add e criar um commit para resolver o problema. Agora, você já pode deletar o seu branch antigo, pois tudo está no master.

Com o comando `git branch -a` podemos ver todos os branches, locais ou remotos, do nosso repositório. Para deletar um branch local, usamos `git branch -d [Nome do branch]`. Já para deletar um branch remoto, usamos `git push origin :[Nome do branch]`(note os dois pontos).
