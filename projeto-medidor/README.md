# Configuração do projeto - Medidor de bateria com comunicação bluetooth

**Tome cuidado redobrado ao conectar sensores, gravadores e outras placas. Os circuitos geralmente não possuem proteção contra polaridade invertida e conectar erroneamente vai queimar coisas.**

*"Coisas queimam, pessoas morrem" -- Professor de laboratório de sistemas digitais*

Com a placa do medidor em mãos, precisam ser conectados o gravador (conversor USB para SPI, o protocolo usado pra gravação do firmware do ATmega. Vai ser responsável por passar seu programa para o microcontrolador) e um conversor RS232 para Bluetooth (placa que se conecta em um barramento serial e envia os dados por Bluetooth). Além disso, será necessário um computador com Bluetooth ou um adaptador USB para Bluetooth. A seguinte foto é um exemplo de tudo conectado (as placas do PS e pinagens são diferentes, não copie a foto sem confirmar a pinagem da sua placa).

![Placa montada](http://s31.postimg.org/6bf9hqi17/IMG_20160422_155847.jpg "Placa montada")

O LED da placa do medidor deve ligar enquanto a placa estiver ligada (LED verde na minha foto). Além disso, o LED do adaptador RS232 para Bluetooth pisca com frequência 2Hz enquanto não estiver conectado com nada. Você vai precisar de alguns programas. Dessa vez a gente mostra os comandos e vocês encontram os pacotes certos (dicas: Google ajuda bastante. Além disso, `yum whatprovides <nome do executável>` mostra pacotes que fornecem dado programa). Usaremos bluez, um gerenciador de Bluetooth para Linux bastante usado, e suas ferramentas de linha de comando (ele também possui ferramentas gráficas para configuração, mas pela linha de comando fica copy-and-paste mais fácil pra vocês :) ).

Após ter conectado o conversor Bluetooth para USB (ou estar em um notebook com Bluetooth), execute `hciconfig`. O programa deve mostrar um adaptador conectado no computador. Se não mostrar, `sudo modprobe btusb` carrega o driver para Bluetooth para USB. Se não der certo, pesquise se seu adaptador requer algum driver especial.

Com o adaptador funcionando, `sudo hciconfig <nome da interface> up` ativa a interface (por exemplo, `sudo hciconfig hci0 up`). Em seguida, usaremos o programa `bluetoothctl` para controlar a interface pelo terminal.

Digite `bluetoothctl`. No prompt do programa, digite `power on` para ativar o adaptador, em seguida `scan on` e `agent on`. Digite `devices` para listar os dispositivos próximos; deve aparecer algo como:

```
Device E0:75:0A:93:A9:8F PLAYSTATION(R)3 Controller
Device 60:38:0E:18:D6:48 PLAYSTATION(R)3 Controller
Device 98:D3:31:80:52:DC HC-06
Device 00:12:04:01:75:63 linvor
Device 5C:C9:D3:55:C2:3D LAPTOP-525EPKMQ
Device A4:17:31:C1:82:B2 MARCO
Device 04:0C:CE:E5:93:B3 prometheus
```

Identifique o adaptador RS232 para Bluetooth (nesse caso, o nome do adaptador usado é HC-06) e note seu endereço MAC (98:D3:31:80:52:DC). Execute (ainda dentro do bluetoothctl):

```
pair <endereço MAC>
```

Agora você deve estar pareado com o adaptador. Saia do bluetoothctl (`exit` de dentro do bluetoothctl). Execute `sdptool records <endereço MAC>` para listar o que o adaptador RS232 para Bluetooth suporta. Note o canal da interface SPP (Serial Port Profile, protocolo para transmissão serial entre dispositivos Bluetooth). O nome do protocolo em Linux é RFCOMM. Por exemplo, se houver um trecho:

```
Protocol Descriptor List:
  "L2CAP" (0x0100)
  "RFCOMM" (0x0003)
    Channel: 1
```

Significa que o canal 1 é o que você precisa usar. Agora há duas opções:

1. Execute `sudo rfcomm bind 0 <endereço MAC> <canal>`, que cria um dispositivo /dev/rfcomm0 para o endereço MAC e canal dados. OU
2. Execute `sudo rfcomm connect 0 <endereço MAC> <canal>`.

Após um desses, executar `sudo screen /dev/rfcomm0 9600` deve mostrar na tela o que está sendo mostrado pelo microcontrolador. O comando 1 e 2 são um pouco diferentes; o 1 mantém apenas em bind, mas sem conectar com o dispositivo. Ao executar algum comando que leia/envie dados por Bluetooth, a conexão será criada. O segundo mantém constantemente uma conexão. A maneira mais fácil de perceber se eles estão conectados é olhar o LED do adaptador RS232 para Bluetooth; ao conectar, ele deve parar de piscar em 2Hz e ficar constantemente ligado. Outra maneira de perceber a diferença entre bind e connect é ver o status do adaptador com `rfcomm show 0`. Se bindado e desconectado: `rfcomm0: 98:D3:31:80:52:DC channel 1 closed`. Ao executar screen: `rfcomm0: 98:D3:31:80:52:DC channel 1 connected [tty-attached]`.
