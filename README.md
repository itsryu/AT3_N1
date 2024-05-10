<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">

<body>
    <div id="container">
        <div align="center" style="display: inline_block">
            <h1>Gerenciador de Sistema de Reserva de Hotel</h1>
            <p>Este é um projeto de console desenvolvido utilizando a linguagem de programação C para o gerenciamento
                (Inserir,Listar,Buscar,Editar,Liberar e Salvar) de quartos de hotel em um arquivo de tipo CSV. Contém
                um menu interativo onde o usuário tem a liberdade para realizar ações de reserva e gerenciamento de
                quartos.</p>
        </div>
        <div>
            <h2>Funcionalidades</h2>
            <ul>
                <li>Inserir hóspedes em um quarto vazio (um quarto pode ter mais de um hóspede);</li>
                <li>Listar hóspedes por ordem alfabética;</li>
                <li>Buscar hóspede;</li>
                <li>Editar hóspede;</li>
                <li>Liberar um quarto;</li>
                <li>Mostrar os números dos quartos vazios;</li>
                <li>Salvar lista de hóspedes com respectivos quartos em arquivo;</li>
            </ul>
            <h2>Como Usar</h2>
            <ol>
                <li>
                    <strong>Clonar o repositório:</strong> Para clonar o repositório, execute o seguinte comando em seu
                    terminal (Obs: necessário ter o <a href="https://git-scm.com/downloads">git</a> instalado em sua
                    máquina):
                    <pre><code>git clone https://github.com/itsryu/AT3_N1.git</code></pre>
                </li>
                <li>
                    <strong>Compilação:</strong> Vá para a pasta AT3 dentro de onde o projeto foi clonado e execute o arquivo windows.bat (Windows) ou linux.sh (Linux):
                    <pre><code>windows.bat</code></pre>
                    <pre><code>sh linux.sh</code></pre>
                </li>
                <li>
                    <strong>Compilação:</strong> Ou se quiser compilar utilizando linha de comando abra um terminal na pasta AT3 dentro de onde o projeto foi clonado e compile o
                    programa utilizando o GCC (GNU Compiler Collection):
                    <pre><code>gcc ./functions/functions.c ./functions/menu.c ./main.c -o main.exe</code></pre>
                </li>
                <li>
                    <strong>Execução:</strong> Após a compilação, execute o arquivo 'main.exe' para inicializar o
                    programa.
                    <pre><code>main.exe</code></pre>
                </li>
                <li><strong>Interagindo com o programa:</strong> Siga as instruções do menu para realizar as ações
                    desejadas.</li>
            </ol>
            <h2>Ferramentas de desenvolvimento utilizadas</h2>
            <ol>
                <li><strong>Visual Studio Community 2022</strong> (Utilizada para o desenvolvimento e depuração do
                    código)</li>
                <li><strong>GitHub</strong> (Utilizada para o versionamento)</li>
                <li><strong>Discord</strong> (Utilizado para comunicação entre os desenvolvedores)</li>
            </ol>
            <h2 align="center">Desenvolvedores</h2>
            <table align="center">
                <thead>
                    <tr>
                        <th align="center">Nome</th>
                        <th align="center">Github</th>
                        <th align="center">Matricula</th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td align="center">João Victor</td>
                        <td align="center"><a href="https://github.com/itsryu">@itsryu</a></td>
                        <td align="center">UC23103118</td>
                    </tr>
                    <tr>
                        <td align="center">Arthur Batista</td>
                        <td align="center"><a href="https://github.com/ArthurUCB">@ArthurUCB</a></td>
                        <td align="center">UC23200833</td>
                    </tr>
                    <tr>
                        <td align="center">Rogério Teixeira</td>
                        <td align="center"><a href="https://github.com/G3rin">@G3rin</a></td>
                        <td align="center">UC23200885</td>
                    </tr>
                    <tr>
                        <td align="center">Gustavo Nunes</td>
                        <td align="center"><a href="https://github.com/GustavoNSBr">@GustavoNSBr</a></td>
                        <td align="center">UC23200427</td>
                    </tr>
                    <tr>
                        <td align="center">Nichollas Holz</td>
                        <td align="center"><a href="https://github.com/NickDevHolz">@NickDevHolz</a></td>
                        <td align="center">UC23200092</td>
                    </tr>
                </tbody>
            </table>
        </div>
    </div>
</body>

</html>
