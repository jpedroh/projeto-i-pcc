PMT

Autores:
João Pedro Henrique Santos Duarte (jphsd@cin.ufpe.br)
José Antônio Alves Maciel (jaam@cin.ufpe.br)

Instruções para compilação:
Para compilar a ferramenta, é suficiente executar o comando `make` dentro do diretório `src` do projeto. O programa compilado estará disponível em `./bin/pmt`

Instruções para invocar a ferramenta:
    ./bin/pmt [opções...] padrão arquivo [arquivos...]

Por exemplo, caso eu queira as ocorrências do padrão "pattern" nos arquivos "texto.txt" e "texto1.txt", uso o seguinte comando:
    ./bin/pmt pattern texto*.txt

Opções da linha de comando:

    --help: 
        Mostrará na linha de comando as possíveis opções de argumento da ferramenta.
    -a, --algorithm <nome>: 
        Realizará a busca dos padrões fornecidos utilizando o algoritmo indicado.
        Os algoritmos disponíveis são:
            sliding_window
            sellers
            shift_or
            kmp
            aho_corasick
            wu_manber
    -p, --pattern <patternfile>:
        Realizará a busca de todos os padrões indicados no patternfile. Dentro de um mesmo arquivo será possível indicar múltiplos padrões, cujo o delimitador será a quebra de linha
        e portanto, os padrões serão considerados diferentes caso estejam em linhas diferentes. Caso separados por espaço, vírgula ou algum outro delimitador, todas as palavras da linha
        serão consideradas como parte do mesmo padrão.
    -e, --edit <int>:
        Fornece a distância de edição máxima que será utilizada para as buscas dentro do texto.
    -c, --count:
        Ao invés de imprimir as linhas em que há ocorrências dos padrões, será impresso a soma de todas as ocorrências dos padrões indicados.