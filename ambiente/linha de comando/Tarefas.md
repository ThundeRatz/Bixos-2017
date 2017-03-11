# Tarefa 1
---

Tarefa 1, vejam instruções no fórum.

Comandos usados:
```
cut
grep
head
sort
tac
tail
uniq
wc
```

1 - O comando `dmesg` mostra logs do núcleo do sistema. Você pode testá-lo (executar `dmesg` em um terminal) e ver que muita saída é gerada (logs desde que você ligou o computador). Mostre sua saída sem linhas duplicadas (apenas linhas únicas).

2 - O comando `dmesg` mostra logs do núcleo do sistema. Você pode testá-lo (executar `dmesg` em um terminal) e ver que muita saída é gerada (logs desde que você ligou o computador). Limite a saída às últimas 14 linhas.

3 - O comando `ps aux` lista processos e mostra informações sobre eles (o programa `ps` aceita muitas opções para controlar o que é mostrado, mas não vamos focar nisso).  Mostre apenas o que está na terceira coluna da saída.

4 - O comando `ps aux` lista processos e mostra informações sobre eles (o programa `ps` aceita muitas opções para controlar o que é mostrado, mas não vamos focar nisso). Mostre o número de linhas de sua saída na tela.

5 - O comando `last` mostra últimos logins no sistema. Mostre sua saída com linhas invertidas (última linha aparecendo no início, penúltima linha como segunda, etc.).

6 - O comando `w` mostra usuários logados. Mostre apenas a sexta coluna de sua saída.

7 - O comando `w` mostra usuários logados. Mostre apenas a primeira linha de sua saída.

8 - O comando `find -maxdepth 2` mostra todos os arquivos e pastas com profundidade até 2. Limite sua saída aos que possuem o caractere t.

9 - O comando `last` mostra últimos logins no sistema. Mostre sua saída com linhas ordenadas alfabeticamente.

10 - O comando `find -maxdepth 2` mostra todos os arquivos e pastas com profundidade até 2. Mostre o número de caracteres da saída dele (contar o número total de letras na tela).

11 - O comando `du -sh *` lista o tamanho em disco de cada arquivo. Mostre sua saída com linhas ordenadas pelo tamanho (nota: Teste o comando. Veja que o tamanho é o primeiro campo, então ordenar as linhas alfabeticamente quase funciona. O programa que ordena linhas recebe uma opção adicional para ordenar por tamanho em formato `human-readable`, com sufixos de tamanho. Veja o manual).

12 - O comando `df -h` mostra os volumes montados no sistema. Limite a saída apenas a linhas que contém o texto `udev`.

13 - O comand `file *` mostra o tipo de arquivo de todos os arquivos na pasta atual. Mostre apenas as linhas que contenham `text`.
