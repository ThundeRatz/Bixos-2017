# Configuração do ambiente

## Linux

Usamos Linux no desenvolvimento de programas. Linux é bastante estável, tem suporte muito bom a vários processadores (como os das placas que usamos nos robôs) e ferramentas de desenvolvimento.

Você vai precisar de um computador com Linux. Linux é o núcleo do sistema (o que fornece gerenciamento de memória e tempo de processamento, acesso aos arquivos e outros serviços que os programas vão precisar). Muitas "distribuições" Linux existem, que são pacotes que instalam Linux e vários programas adicionais. Dê uma procurada no Google e escolha alguma que pareça amigável (ou só continue lendo).

Suas opções de instalação são:

* Instalar Linux no HD do computador. Acredito que seja a opção preferível a longo prazo, já que na equipe você deve usar majoritariamente Linux, mas dá um pouco mais de trabalho pra quem nunca fez. Alguns links:

	1. [Redimensionar partições no 	Windows](http://www.howtogeek.com/101862/how-to-manage-partitions-on-windows-without-downloading-any-other-software/): Vai ser necessário para deixar espaço livre.

	2. [Instalação](https://help.ubuntu.com/community/Installation): Guia de instalação. O instalador gráfico é bem passo a passo e não deve dar problemas, mas em caso de dúvidas use o Google. [Stack Overflow](http://askubuntu.com/questions/6328/how-do-i-install-ubuntu) tem alguns tópicos que resolvem seus problemas. Qualquer distribuição serve, os exemplos acima são com Ubuntu por ser a mais comum, mas [Mint](http://www.linuxmint.com/about.php) é uma opção bem amigável, e [Fedora](https://getfedora.org/) costuma ser um pouco melhor para desenvolvimento na minha opinião.

* Usar uma máquina virtual. Essa é também uma opção muito boa, sem ter que particionar seu HD. Alguns links:

	1. [O que é uma máquina virtual](http://searchservervirtualization.techtarget.com/definition/virtual-machine).

	2. [Página do Ubuntu sobre máquinas virtuais](https://help.ubuntu.com/community/VirtualMachines). VirtualBox é a escolha mais comum.

* Usar um Live CD/pen-drive. Você pode instalar Linux em um deles e bootar do dispositivo. Links são fáceis de achar na internet (só baixar a imagem e gravar em um CD ou pen-drive).

* Usar notebooks da gaiola. Temos alguns com Linux, mas a gaiola pode não ter computadores disponíveis para muitos bixos.

* Acesso remoto a uma máquina. Caso nada acima dê certo para você, podemos providenciar login a uma máquina remota para fazer algumas atividades do processo seletivo. Essa opção é a pior (você não vai poder testar seu código conectando dispositivos) e deve ser evitada.

## Instalação de pacotes

Em distribuições Linux, dificilmente se realiza download de um programa manualmente para rodar um instalador. As distribuições possuem diferentes **gerenciadores de pacotes**, que são responsáveis por realizar o download e instalação de programas por você. Os programas são baixados de **repositórios**, que são sites da distribuição com programas que foram testados para funcionar sem problemas na sua distribuição e versão. Ou seja, você recebe um programa com maior segurança que ele vai funcionar e não fornece riscos a sua máquina. Se algum programa faltar na sua máquina (durante os tutoriais aparecer um "command not found" para algo), pesquise como instalá-lo usando o gerenciador de pacotes.

Mais sobre isso será visto na próxima aula.
