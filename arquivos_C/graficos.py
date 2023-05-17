import matplotlib.pyplot as plt

# Leitura dos dados do arquivo
data_i = []
data_j = []
with open("tempo_execucao.txt", "r") as file:
    for line in file:
        n, tempo_i, tempo_j = map(float, line.split())
        data_i.append((n, tempo_i))
        data_j.append((n, tempo_j))

# Verificação se há dados para a curva j
if len(data_j) > 0:
    # Separação dos valores de N e tempos para cada curva
    n_i, tempo_i = zip(*data_i)
    n_j, tempo_j = zip(*data_j)

    # Plotagem do gráfico
    plt.plot(n_i, tempo_i, label="i no loop externo")
    plt.plot(n_j, tempo_j, label="j no loop externo")
    plt.xlabel("N")
    plt.ylabel("Tempo (s)")
    plt.title("Tempo de execução para diferentes ordens de loops")
    plt.legend()
    plt.show()
else:
    print("Não há dados para a curva j no loop externo.")
