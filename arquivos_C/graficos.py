
import matplotlib.pyplot as plt

# Leitura dos dados do arquivo
data = []
with open('tempo_execucao.txt', 'r') as file:
    for line in file:
        n, elapsed = line.split()
        data.append((int(n), float(elapsed)))

# Extração das coordenadas x e y
n_values = [d[0] for d in data]
elapsed_values = [d[1] for d in data]

# Plotagem do gráfico
plt.plot(n_values, elapsed_values)
plt.xlabel('Tamanho de N')
plt.ylabel('Tempo de execução (s)')
plt.title('Gráfico construído a partir dos resultados em C')
plt.grid(True)
plt.show()
