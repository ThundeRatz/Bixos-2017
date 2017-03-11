# Dispositivos
---

Uma coisa bem legal e simples de Linux é o uso e abuso de arquivos. A interface de abertura, escrita, leitura e fechamento pode ser usada em arquivos e pastas, mas também em coisas abstratas ou temporárias, como dispositivos e canais de comunicação. Funções como `open()`, `read()`, `write()` e `close()` serão bastante usadas aqui e é recomendável dar uma olhada no manual e buscar as flags que estão sendo usadas.

Essa interface unificada de acesso funciona da seguinte maneira:

* Cada processo possui uma lista de arquivos abertos, identificados por descriptors (um número que indica qual arquivo é qual). Se o processo abre um novo arquivo, é retornado um novo file descriptor. Os file descriptors (muitas vezes abreviados por fd em código e documentação) começam em 0 para cada processo e vão aumentando conforme são abertos novos arquivos. Note que ao iniciar seu programa já há alguns fd abertos (entrada, saída e saída de erro padrões), então o primeiro arquivo que você abrir geralmente é o 3. O fd, que é um identificador do arquivo, é passado para as funções read, write, close e similares. Por exemplo, para abrir um arquivo, escrever algo e fechar, devo chamar `open()`, salvar o fd em uma variável, e passar esse fd para `write()` e `close()`.

Um exemplo comentado de abertura e leitura está no arquivo leitura_arquivo.c, leia aquele arquivo e compreenda a parte de abertura e leitura. `open` retorna um fd. `read` lê de fd e salva em buffer.

O interessante é o que pode ser aberto. Muitas coisas em computação funcionam como um canal de leitura e escrita e poderiam ser encaixadas nessa mesma interface. O que realmente acontece em Linux é que podemos abrir um arquivo, caso no qual as chamadas de `write()` e `read()` vão para um driver que gerencia o sistema de arquivos, ou uma conexão com a internet, por exemplo, e as chamadas de `write()` e `read()` serão enviadas para um driver que gerencia os dados pela rede.

Pode parecer um pouco obscuro, mas o fundamental é que acesso a dispositivos e recursos são geralmente feitos com `read()` e `write()`, que não servem apenas para ler e escrever de arquivos em disco. Essas funções são canais de comunicação com drivers para realizar tarefas diversas.

Um pequeno driver vai ser dado para vocês compilarem e mexerem com leitura. Vocês não vão ter que compreender o código do driver ou editá-lo; o objetivo  é que vocês aprendam o básico de compilação de um driver e tenham base para fazerem leitura da serial, que será usada para comunicação com o medidor de bateria.

O driver está no [GitHub do PS](https://github.com/ThundeRatz/Bixos-2017/tree/master/hello-thunderatz-driver). O arquivo **hello_thunderatz.c** possui o código. Veremos como conseguir abrir um fd para comunicação com esse driver, mas o que precisa ficar claro:

* Vai haver um jeito de um programa (seu programa, por exemplo) criar um fd que permita comunicação com nosso driver. A abertura de um arquivo para comunicação com o driver vai ser explicada mais para frente.
* De posse do fd, as funções `read()` e `write()` permitem comunicação com o driver. Ao chamar `read()`, `hello_thunderatz_read()` será chamado. Agora, estamos no nível de execução do driver, onde é permitido acessar dispositivos e manipular o sistema. Nesse exemplo, a função retorna um string, mas em um driver de verdade ela poderia fazer muito mais coisa (por exemplo, ler um sensor magnético e retornar a orientação de um robô).

É realmente isso: um driver diz quais operações suporta, e ao chamar read e write em um programa comum o driver decide o que fazer e o que retornar. O driver hello_thunderatz não suporta `write()` e escrever nele gerará um erro.

Para compilar o driver, execute `make` na pasta. Você precisa de um pacote de desenvolvimento do kernel (que possuem os cabeçalhos das funções do kernel). Geralmente ele se chama linux-headers (`apt-get install linux-headers` ou `yum install linux-headers`).

Se der tudo certo, `make` deve terminar sem erros:

```
make -C /lib/modules/4.4.1-2-ARCH/build M=/home/tiago/code/TR/Bixos-2017/hello-thunderatz-driver modules
make[1]: Entering directory '/usr/lib/modules/4.4.1-2-ARCH/build'
  CC [M]  /home/tiago/code/TR/Bixos-2017/hello-thunderatz-driver/hello_thunderatz.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/tiago/code/TR/Bixos-2017/hello-thunderatz-driver/hello_thunderatz.mod.o
  LD [M]  /home/tiago/code/TR/Bixos-2017/hello-thunderatz-driver/hello_thunderatz.ko
make[1]: Leaving directory '/usr/lib/modules/4.4.1-2-ARCH/build'
```

Para instalar o módulo: `insmod hello_thunderatz.ko`. O comando carrega o módulo no kernel até ser descarregado ou o kernel ser reiniciado (se você reiniciar o computador, terá que carregá-lo de novo).

## /dev

Bom, e como conseguimos o fd para nosso driver? Há um diretório, /dev, que é usado para manter entradas de dispositivos. Abrir um dos arquivos contidos lá retorna um fd para comunicação com seu driver. Execute `ls /dev` e veja que há dispositivos para acesso a HD (sda), CD (cdrom), câmeras (video0), entre outros. Deve aparecer também o hello_thunderatz entre eles.

Pegue o programa leitura_arquivo.c (que está na mesma pasta desse tutorial), leia seu código e compile-o (`gcc leitura_arquivo.c -o leitura_arquivo`). Se tiver dúvidas sobre alguma função dê uma olhada no manual e leia os comentários. Você pode testá-lo em um arquivo qualquer e ele deve mostrar seu conteúdo em hexadecimal e ASCII.

Para ler de nosso driver, temos apenas que abrir o arquivo /dev/hello_thunderatz ao invés de um arquivo comum. Executar `./leitura_arquivo /dev/hello_thunderatz` vai gerar um erro `open: Permission denied`, já que não é permitido que usuários sem permissão se comuniquem diretamente com um dispositivo. Executar `sudo ./leitura_arquivo /dev/hello_thunderatz` gera a seguinte saída:

```
48 65 6c 6c 6f 20 54 68 75 6e 64 65 52 61 74 7a 21 0a 00
 H  e  l  l  o     T  h  u  n  d  e  R  a  t  z  !  .  .
```

A leitura da serial é um pouco mais complicada por requer maior configuração (há muitas configurações diferentes para a serial, com diferentes taxas de transmissão e capacidades). Após abrir o dispositivo, vocês terão que chamar mais funções para configuração, mas a ideia é a mesma.
