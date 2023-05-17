import matplotlib.pyplot as plt

# Lista para armazenar os valores do tempo de execução para i e j
tempo_execucao_i = []
tempo_execucao_j = []

# Leitura dos valores do tempo de execução do arquivo
with open("tempo_execucao.txt", "r") as file:
    for line in file:
        n, tempo = line.split()
        tempo = float(tempo)
        if len(tempo_execucao_i) == len(tempo_execucao_j):
            tempo_execucao_i.append((int(n), tempo))
        else:
            tempo_execucao_j.append((int(n), tempo))

# Separação dos valores de n e tempos para i e j
n_i, tempos_i = zip(*tempo_execucao_i)
n_j, tempos_j = zip(*tempo_execucao_j)

# Plotagem das curvas
plt.plot(n_i, tempos_i, label="Loop externo i")
plt.plot(n_j, tempos_j, label="Loop externo j")
plt.xlabel("Tamanho do problema (n)")
plt.ylabel("Tempo de execução (segundos)")
plt.title("Gŕafico construído a partir dos resultados em FORTRAN")
plt.legend()
plt.show()
