# cli-tcp-chat

<h2>Trabalho 1 de SSC0641 - Redes de computadores</h2>

Desenvolvido por:
<ul>
  <li>João Gabriel Zanão Costa          - 11234266</li>
  <li>Marcos Vinícius Firmino Pietruci  - 10770072</li>
  <li>Matheus Vieira Gonçalves          - 11200397</li>
  <li>Murilo Mussatto                   - 11234245</li>
  <li>Thiago Henrique Vicentini         - 11234270</li>
</ul>

<h2>Sobre o trabalho</h2>

Cumprindo os requisitos do trabalho, nós desenvolvemos um <i>chatroom</i> usando o protocolo TCP. É necessário executar um servidor local, então os clientes poderão se conectar à sala de bato papo e trocar mensagem em tempo real.

<h2>Como executar</h2>

Para executar o nosso programa, basta utilizar o Makefile. Primeiro, entre no diretório do programa. Depois, execute os seguintes comandos

<code>$ make init <br>$ make</code>

Nesse momento todos os arquivos estão compilados e prontos para serem executados

<h4>Executar o servidor</h4>

<code>$ ./build/TCP-server </code>

<h4>Executar o cliente</h4>

<code>$ ./build/TCP-client </code>

<h4>Para fechar o cliente e o servidor</h4>

Inserir <code>:q</code> para os clientes e <code>CTRL+C</code> no servidor.


