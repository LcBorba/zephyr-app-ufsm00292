# Entrega 1 - Instalação e Validação do Ambiente Zephyr + Renode

## 1. Objetivo
O objetivo desta fase inicial foi a criação e validação de um ambiente de desenvolvimento completo no **Windows** para o **Zephyr RTOS**, com foco na simulação de firmware para a placa **SAMR21**, utilizando o simulador de hardware **Renode**.

## 2. Etapas Concluídas

### a. Instalação do Ambiente de Desenvolvimento
Foram instaladas e configuradas todas as ferramentas necessárias para o desenvolvimento com Zephyr:

- **Ferramentas de Host**: CMake, Python, Git, Ninja, etc. (gerenciadas via Chocolatey)  
- **Workspace Zephyr**: inicializado com a ferramenta `west`, incluindo o download do código-fonte do Zephyr e de seus módulos  
- **Zephyr SDK**: instalação da toolchain ARM (compilador, bibliotecas, etc.) integrada ao ambiente  

### b. Instalação do Ambiente de Simulação
- Instalação e configuração do **Renode**, garantindo pleno funcionamento do simulador localmente.

### c. Validação do Ambiente com Exemplo Pré-compilado
- Obtenção de artefatos de um exemplo **blinky** pré-compilado (Zephyr/Antmicro).  
- Arquivos utilizados:
  - `blinky.elf`  
  - Scripts de configuração do Renode (`.resc` e `.repl`)  
- A simulação foi executada com sucesso no Renode, validando a instalação e confirmando que o ambiente é capaz de carregar e rodar firmware para a placa **samr21_xpro**.

---

# Entrega 2 - Compilação de uma aplicação Zephyr e simulação com o Renode / Pesquisa sobre os periféricos da SAMR21 já portados para o Zephyr

- Durante esta semana foi compilada uma aplicação Zephyr que consiste em um simples contador utilizando a função printk, a aplicação foi simulada com sucesso com o Renode.

- Além disso, foram iniciadas pesquisas sobre os periféricos da placa de desenvolvimento SAMR21 para análise de possíveis aplicações Zephyr utilizando os seus drivers já portados para o RTOS.


---


# Entrega 3 - Escolha de projeto -Comunicação entre duas SAMR21 com OpenThread-

- Durante esta semana foi escolhida como parte do meu desenvolvimento para a aplicação zephyr a comunicação com openthread entre duas placas utilizando as antenas padrão IEEE802154.


---


# Entrega 4 - Exemplo COAP muito grande para SAMR21 e problemas com o sample Echo Client/Server-

- Durante esta semana foi realizada tentativa de compilar e rodar o exemplo do zephyr com Openthread COAP, contúdo, foi observado um overflow na memória ram de 30KB e mesmo com otimizações o overflow continuou ocorrendo com cerca de 9KB. Com isto, foi escolhido o sample Echo Client/Server que é um pouco mais simples e visa estabelecer uma conexão Ipv6 entre duas SAMR21 via IEEE 802.15.4. Inicialmente observou-se uma compilacão correta e sem problemas para o Client, já no Server ocorreu um pequeno Overflow de 900B que foi corrigido com algumas reduções em stacks da aplicação. Partindo para o flash e execução na placa o Client executou perfeitamente mas no Server ocorreu um problema de erro de HARD FAULT.

OBS: Ainda não foi realizado o commit dos arquivos de build e codigo fonte do sample para evitar confusão, assim que estiver tudo em completo funcionamento o commit sera efetuado.


---


# Entrega 5 - Depuração do Hard Fault e Sucesso na Comunicação UDP/IPv6

## 1. Objetivo
- O objetivo desta etapa foi diagnosticar e corrigir o HARD FAULT que ocorria na aplicação Echo Server (Entrega 4). A meta era estabelecer uma comunicação funcional as placas SAMR21, enviando dados via UDP/IPv6 sobre a rede IEEE 802.15.4.

## 2. Diagnóstico do HARD FAULT
- A depuração revelou que o HARD FAULT  era um  problema de redução drástica de buffers TX E RX:

- Observação Inicial: O HARD FAULT no Servidor ocorria exatamente no momento em que o Cliente enviava o primeiro pacote.

- Diagnóstico: buffers como CONFIG_NET_PKT_RX_COUNT, CONFIG_NET_PKT_TX_COUNT, CONFIG_NET_BUF_RX_COUNT e CONFIG_NET_BUF_TX_COUNT que já eram reduzidos para os 32Kb de RAM da samr21 foram reduzidos ainda mais na tentativa de evitar o overflow, com isso a compilação ocorria de forma correta mas na hora de receber os pacotes o server não tinha espaço para armazenar os pacotes.

## 3. Correção: buffers de tamanho originais e redução do tamanho de algumas stacks
- Com os buffers de tamanhos originais o problema inicial de overflow de RAM voltou a ocorrer a solução foi reduzir o tamanho de algumas stacks de 2048 para 1800, são elas:CONFIG_MAIN_STACK_SIZE, CONFIG_ISR_STACK_SIZE, CONFIG_SYSTEM_WORKQUEUE_STACK_SIZE.



## 4. Implementação da Aplicação de Sensor (Simulada)
- O exemplo echo client/servidor original era um teste robusto de comunicação, ou seja, o client enviava centenas de pacotes aleatórios e grandes para o server que recebia e ecoava de volta para o client, isso consumia muita memoria, como o nosso objetivo é enviar dados de uma placa para a outra isto foi modificado.

- Agora o client envia pacotes a cada 5 segundos, o server apenas recebe estes pacotes e não ecoa novamente para o client

- Inicialmente o pacote era aleatório gerado por um lorem_ipsum, isto foi alterado para um string fixa "Hello World" e em seguida foi criada uma função que emula um sensor de temperatura para simularmos o que seria o mais próximo da aplicação final após as integrações necessárias.

## 5. Resultado Final
- A depuração foi bem-sucedida. A comunicação entre as duas placas SAMR21 está a funcionar perfeitamente, com o cliente a enviar dados de um sensor simulado e o servidor a recebê-los e a imprimi-los. A base de comunicação para o projeto está completa e validada.





