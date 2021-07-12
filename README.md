# Escalonamento de Transações em Bancos de Dados

<p>Implementação de dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes. Estes algoritmos permitem o aluno compreender gargalos no processamento de transações.</p>
<h3></h3>
<h3>Algoritmo de teste de seriabilidade quanto ao conflito:</h3>
<p> </p>
<ul>
<li>Crie um nó para cada T do escalonamento S</li>
<li>Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada r(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub></li>
<li>Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de r(x) em T<sub>i</sub></li>
<li>Aresta T<sub>i</sub> -&gt; T<sub>j</sub> para cada w(x) em T<sub>j</sub> depois de w(x) em T<sub>i</sub></li>
<li>S é serial se não existe ciclo no grafo </li>
</ul>
<h3>Algoritmo de teste de equivalencia por visão</h3>

Dois agendamentos S e S' são equivalentes por visão, se atenderem as seguintes condições:
<ul>
<li>O mesmo conjunto de transações e operações participam em S e S'</li>
<li>Para cada r(x) de T<sub>i</sub>, se o valor de x lido for escrito por w(x) de T<sub>j</sub>, o mesmo deve permanecer para r(x) de T<sub>i</sub> em S'</li>
<li>Se o operador w(y) em T<sub>k</sub> é a ultima escrita de y em S, então w(y) em T<sub>k</sub> deve ser a última escrita em S'</li>
</ul>

<h3>Entrada:</h3>
<p>A entrada é feita pela entrada padrão (<code>stdin</code>). O  arquivo é formado por uma sequência de linhas, onde cada linha  representa uma transação chegando. Cada linha tem 4 campos: o primeiro é o  tempo de chegada, o segundo é o identificador da transação, o terceiro é a operação (R=read, W=write, C=commit) e o quarto o atributo que será lido/escrito. Estas linhas estão ordenadas pelo  primeiro campo (tempos menores no início indicando a linha do tempo).</p>
<h3>Saída:</h3>
<p>A saída é feita pela saída padrão (<code>stdout</code>). O  arquivo será composto por uma sequência de linhas. Uma linha para cada escalonamento. Cada linha tem 4 campos  separados por espaço (um único espaço entre cada par de campos). O  primeiro campo é o identificador do escalonamento. O segundo campo é a lista de transações. E o terceiro apresenta o resultado do algoritmo da garantia da seriabilidade, onde SS e NS significam respectivamente serial (SS) ou não serial (NS). O quarto campo é o resultado do algoritmo de teste de equivalência de visão, onde SV e NV significam respectivamente equivalente (SV) ou não equivalente (NV) .</p>
<p>Exemplo de arquivos com uma entrada e uma saída válida:</p>
<div class="visualClear">
<table class="plain" border="1">
<tbody>
<tr>
<td>Entrada</td>
<td>Saída</td>
</tr>
<tr>
<td><b>
<div class="visualClear" style="text-align: left; ">1 1 R X</div>
<div class="visualClear" style="text-align: left; "><b>2 2 R X</b></div>
<div class="visualClear" style="text-align: left; "><b>3 2 W X</b></div>
<div class="visualClear" style="text-align: left; "><b>4 1 W X</b></div>
<div class="visualClear" style="text-align: left; "><b>5 2 C -<br /></b></div>
</b><b>
<div class="visualClear" style="text-align: left; "><b>6 1 C -<br /></b></div>
<div class="visualClear" style="text-align: left; "><b>7 3 R X</b></div>
<div class="visualClear" style="text-align: left; "><b>8 3 R Y<br /></b></div>
</b><b>
<div class="visualClear" style="text-align: left; "><b>9 4 R X</b></div>
<div class="visualClear" style="text-align: left; "><b>10 3 W Y<br /></b></div>
<div class="visualClear" style="text-align: left; "><b>11 4 C -</b><b>
<div class="visualClear" style="text-align: left; "><b>12 3 C -<br /></b></div>
</b></div>
</b></td>
<td>
<div class="visualClear">1 1,2 NS NV</div>
<div class="visualClear">2 3,4 SS SV</div>
<div class="visualClear">
<div class="visualClear" style="text-align: left; "></div>
</div>
</td>
</tr>
</tbody>
</table>
</div>

# Uso

```
make
./escalona < tests/test.txt
```
