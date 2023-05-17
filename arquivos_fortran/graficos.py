import matplotlib.pyplot as plt

# Lê os dados do arquivo de tempos de execução
n_values = []
time_values = []
with open('tempo_execucao.txt', 'r') as file:
    for line in file:
        line = line.strip()
        if line:
            n, time = line.split()
            n_values.append(int(n))
            time_values.append(float(time))

# Plota o gráfico
plt.plot(n_values, time_values, marker='o')
plt.xlabel('Tamanho do problema')
plt.ylabel('Tempo de execução (s)')
plt.title('Tempo de Execução em Função do Tamanho do Problema')
plt.grid(True)
plt.show()
