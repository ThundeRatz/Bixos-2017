# Linha de comando
---

A linha de comando é aquele ambiente assustador onde as pessoas ficam digitando e vendo letras descerem. Vamos ensinar o básico de seu uso. A principal vantagem de usar a linha de comando ao invés de uma interface gráfica é a possibilidade de automatizar e repetir mecanicamente tarefas. Para alguma ação complicada de renomear ou mover arquivos que demoraria minutos, por exemplo, você pode digitar um comando que o realize automaticamente. Para executar novamente, é só recuperar o comando no histórico.

Há muitos tutoriais bons sobre uso de "shells" na internet, [como esse](http://linuxcommand.org/lc3_learning_the_shell.php). Aqui será dado um básico do que é necessário para o PS, mas com o tempo você deve se familiarizar com mais comandos. É recomendável que você acompanhe executando os comandos para entender.

## Terminal e shell

Primeiramente, abra um **terminal**. A sua distribuição provavelmente já vem com um instalado. O terminal é o programa gráfico que abre uma janela, executando um programa (o shell), aceita entrada do teclado (o que você digitar será enviado ao shell) e mostra saída do shell. A aparência do terminal ao ser aberto é mais ou menos essa:

![Imagem pega de http://linuxcommand.org/](http://linuxcommand.org/images/Screenshot-Terminal.png "Imagem pega de http://linuxcommand.org/")

O **shell** é um interpretador de comandos. Para cada linha que você digitar, ele vai interpretar o que é desejado e realizar alguma ação, e possivelmente mostrar algo de volta na tela. O shell é uma linguagem de programação completa: você pode ter condições e laços, por exemplo, feitos diretamente no terminal. O shell mais usado em Linux se chama Bash.

## Funcionalidades do shell

Antes de começar com comandos, vejamos algumas funcionalidades básicas do shell. Ele geralmente apresenta o nome de usuário e da máquina, seguido da pasta atual e um caractere $, como visto acima. Esse texto inicial é configurável e pode ser diferente no seu. O $ separa o início de seu comando. Digite *exemplo* no terminal, que deve ficar assim:

```bash
$ exemplo
```

Ao apertar Enter, você verá o seguinte (ou uma mensagem de erro parecida):

```
bash: exemplo: command not found
```

Isso é o bash te avisando que não há nenhum programa chamado exemplo instalado. O terminal desceu para outra linha, que deve estar vazia, para você digitar outro comando:

![](http://s24.postimg.org/3ktz2eul1/2016_02_08_165621_815x434_scrot.png)

Você pode digitar outro comando ou voltar no histórico. Seu histórico de comandos fica salvo em um arquivo e há atalhos para executá-los novamente. Ao apertar seta para cima, o último comando (*exemplo*) vai aparecer na linha atual. Volte ao começo da linha e insira o seguinte comando (sem digitar o $, claro):

```bash
$ echo exemplo
```

echo é um comando interno do bash que mostra na saída os argumentos que receber. Desse jeito, ele funciona como um print.

Outra opção para voltar no histórico é o atalho Ctrl + R, que permite buscar por um pedaço de texto em todo o histórico. Digite outros comandos (por exemplo, *echo outra linha*). Imagine que, após essa série de comandos, você quer voltar para um muito antigo, mas sem apertar seta para cima várias vezes. Usar Ctrl + R abre um diálogo de busca. Digitar *exemp* volta para o comando *echo exemplo* (ou o último que contiver o texto "exempl").

Se algum programa seu travar, Ctrl + C envia um sinal de interrupção ao programa (um sinal que geralmente vai parar seu programa e voltar ao shell).

Um comando que vale a pena citar antes de mostrar mais detalhes do shell é `man`. O comando man mostra o manual de algum programa ou função e vai ser muitas vezes seu melhor amigo quando estiver perdido. Digite, por exemplo:

```bash
man echo
```

Para ver o manual do comando echo. Manuais podem ser um pouco extensos por documentarem todas as funcionalidades principais de um programa, então é interessante apreder a usá-los e pesquisar termos neles com rapidez.

Se quiser saber mais sobre o programa man, digite:

```bash
man man
```

## Navegação

Até agora, o shell indicou aquele "~" na nossa linha de comando como pasta atual. O "~" representa a sua HOME, que é sua pasta pessoa. Podemos mudar de pasta e executar os comandos relativos à outra pasta.

Crie um arquivo de texto com algum conteúdo na sua home e uma pasta vazia. Vou chamá-los de "texto" e "pasta". Ao executar `cat texto`, o seguinte deve ocorrer:

```
$ cat texto
Conteúdo do arquivo
```

cat é o comando que con`cat`ena arquivos. Para cada arquivo que é passado para ele, ele vai colocar na saída de texto seus conteúdos. Execute agora:

```
$ cd pasta
$ cat texto
cat: texto: No such file or directory
```

Primeiramente, `cd` muda a pasta atual (change directory). Ao entrar na nova pasta, seu shell deve ter mudado a linha antes do $ (por exemplo, para **tiago@shibata-arch:~/pasta$** no meu). Ao tentar mostrar o conteúdo de texto, você receberá um erro, pois não há um arquivo chamado texto na nova pasta. Para voltar a pasta superior, execute `cd ..`. Se for executado sem argumentos (apenas `cd`), ele volta para a home.

Para listar os conteúdos de uma pasta, use o comando *ls*. Seu comportamento padrão é mostrar apenas o nome dos arquivos, mas seu manual mostra flags adicionais para formatar o conteúdo ou mostrar mais informações (como tamanho, dono e permissões). Rodar ls na pasta home mostra o seguinte:

```bash
$ ls
pasta texto
```

## Redirecionamento

A entrada e saída padrões de um programa podem ser redirecionadas, ou seja, ao invés de digitar o que o programa recebe e ver o que ele mostra, você pode pedir para ele ler de um arquivo ou de outro programa e gerar a saída em um arquivo ou outro programa. Isso não deve ser muito usado no processo seletivo, mas é importante de saber para salvar os dados de um programa ou automatizar entrada de dados.

Os operadores `>` e `<` redirecionam a saída para um arquivo ou a entrada de um arquivo. Por exemplo, `echo Primeira mensagem > dados` salva "Primeira mensagem" em dados. O comando `echo` mostra a mensagem na saída padrão, mas o shell redirecionou a saída dele para o arquivo dados.

Um dado importante sobre `>` é que ele sobrescreve os dados antigos do arquivo. Executar `echo Segunda mensagem > dados` e depois mostrar o conteúdo de dados resulta no seguinte:

```bash
$ echo Segunda mensagem > dados
$ cat dados
Segunda mensagem
```

Apenas "Segunda mensagem" está salva (e não "Primeira mensagem" na primeira linha). Para concatenar em um arquivo, use `>>`.

`<` abre um arquivo como entrada padrão do comando. Por exemplo, faça um programa que leia uma string, o nome do usuário, e a mostre na saída (exemplo em Python):

```bash
$ python -c "print('Seu nome é ' + input('Digite seu nome: '))"
Digite seu nome: Tiago
Seu nome é Tiago
```

Com redirecionamento da entrada:

```bash
$ python -c "print('Seu nome é: ' + input('Digite seu nome: '))" <python -c "print('Seu nome é: ' + input('Digite seu nome: '))" < dados
Digite seu nome: Seu nome é: Segunda mensagem
```

Um operador mais interessante é `|`. Ele manda a saída de um programa para a entrada de outro. Por exemplo, fazemos um programa (agora em C, que vocês estão mais acostumados):

```c
#include <stdio.h>

int main() {
	char input[90];
	while (fgets(input, sizeof(input), stdin)) {
		printf("Meu programa recebeu %s\n", input);
	}
	return 0;
}
```

Após compilar o programa com o nome read_input, podemos executar `ls | ./read_input` e ele mostrará cada arquivo com "Meu programa recebeu " antes.

Isso é o básico para vocês, é importante que lembrem comandos de navegação e se sintam seguros usando um terminal.

## Permissões

Vários usuários e grupos podem coexistir em um sistema. Não vamos nos aprofundar em como eles funcionam, mas é importante saber que grupos podem definir permissões de acesso a recursos (você pode, por exemplo, adicionar alguns usuários confiáveis no grupo que pode usar uma impressora, e deixar visitantes de fora). Há um usuário e grupo muito especiais, chamados de root. A conta root possui acesso a todos os usuários e é usada para administração. Você verá, por exemplo, que não consegue instalar pacotes executando apenas o gerenciador de pacotes; você precisa preceder o comando por **sudo**. sudo é um comando que muda temporariamente para a conta root, executa o que lhe foi passado, e volta para seu usuário.
