import random
import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt

# Configurações iniciais
num_regions = 5
streets_per_region = 4
crossings_per_street = 6

# Gerar dados fictícios
regions = [str(random.randint(10000, 99999)) for _ in range(num_regions)]

streets = []
segments = []
crossings = {}

# Gerar ruas e cruzamentos
for region in regions:
    all_streets_in_region = []  # Lista de todas as ruas dentro da região
    for street_index in range(streets_per_region):
        street_name = f"Rua_{region}_{street_index + 1}"
        crossing_list = []

        # Criar cruzamentos internos da rua (dentro da mesma rua)
        for crossing_index in range(crossings_per_street):
            crossing_id = f"{region}_{street_index}_{crossing_index}"
            if crossing_id not in crossings:
                crossings[crossing_id] = []
            crossings[crossing_id].append(street_name)
            crossing_list.append(crossing_id)

        # Criar cruzamentos com ruas vizinhas
        # Adicionando cruzamentos de ruas vizinhas (ex: rua anterior ou rua seguinte)
        if street_index > 0:  # Se não for a primeira rua, pegar rua anterior
            neighbor_street_name = f"Rua_{region}_{street_index - 1}"
            neighbor_crossing = f"{region}_{street_index - 1}_{random.randint(0, crossings_per_street - 1)}"
            # Criar a chave para o cruzamento vizinho se ainda não existir
            if neighbor_crossing not in crossings:
                crossings[neighbor_crossing] = []
            crossings[neighbor_crossing].append(neighbor_street_name)
            crossing_list.append(neighbor_crossing)
        
        if street_index < streets_per_region - 1:  # Se não for a última rua, pegar rua seguinte
            neighbor_street_name = f"Rua_{region}_{street_index + 1}"
            neighbor_crossing = f"{region}_{street_index + 1}_{random.randint(0, crossings_per_street - 1)}"
            # Criar a chave para o cruzamento vizinho se ainda não existir
            if neighbor_crossing not in crossings:
                crossings[neighbor_crossing] = []
            crossings[neighbor_crossing].append(neighbor_street_name)
            crossing_list.append(neighbor_crossing)

        # Adicionar a rua e seus cruzamentos
        streets.append([region, street_name, ", ".join(crossing_list)])
        all_streets_in_region.append(street_name)

        # Criar segmentos entre cruzamentos
        for i in range(len(crossing_list) - 1):
            start = crossing_list[i]
            end = crossing_list[i + 1]
            length = random.randint(50, 200)  # Comprimento em metros
            excavation_cost = random.randint(100, 1000)  # Custo de escavação
            direction = random.choice(['Único', 'Duplo'])
            segments.append([start, end, length, excavation_cost, direction])

# Criar DataFrames para os CSVs
# Ruas de uma região
df_streets = pd.DataFrame(streets, columns=['CEP', 'Rua', 'Cruzamentos'])
df_streets.to_csv('ruas.csv', index=False)

# Informações dos segmentos
df_segments = pd.DataFrame(segments, columns=['Cruzamento_1', 'Cruzamento_2', 'Comprimento_m', 'Custo_Excavacao', 'Sentido'])
df_segments.to_csv('segmentos.csv', index=False)

# Exibir primeiras linhas de cada CSV gerado
df_streets.head(), df_segments.head()


# CRIA OS IMÓVEIS

# Carregar o CSV das ruas
df_ruas = pd.read_csv('ruas.csv')

# Tipos de imóveis possíveis
building_types = ['Residencial', 'Comercial', 'Industrial', 'Turística']

# Lista para armazenar os imóveis gerados
imoveis = []

# Para cada rua, gerar imóveis
for _, row in df_ruas.iterrows():
    cep = row['CEP']
    rua = row['Rua']
    
    # Definir um número aleatório de imóveis por rua (ex: entre 10 e 50)
    num_imoveis = random.randint(10, 50)
    
    # Gerar imóveis com números sequenciais e tipos aleatórios
    for numero in range(1, num_imoveis + 1):
        tipo_imovel = random.choice(building_types)
        imoveis.append([cep, rua, numero, tipo_imovel])

# Criar DataFrame para os imóveis
df_imoveis = pd.DataFrame(imoveis, columns=['CEP', 'Rua', 'Número', 'Tipo_Imovel'])

# Exportar para CSV
df_imoveis.to_csv('imoveis.csv', index=False)

# Mostrar as primeiras linhas do DataFrame de imóveis
print(df_imoveis.head())



# Carregar os CSVs
df_streets = pd.read_csv('ruas.csv')
df_segments = pd.read_csv('segmentos.csv')

# Criar o grafo direcionado
G = nx.DiGraph()

# Adicionar os nós (cruzamentos) ao grafo, considerando cruzamentos compartilhados entre ruas
for _, row in df_streets.iterrows():
    cruzamentos = row['Cruzamentos'].split(", ")
    for cruzamento in cruzamentos:
        # Adiciona o cruzamento como nó, se ainda não existir
        if cruzamento not in G:
            G.add_node(cruzamento)

# Adicionar as arestas (segmentos) ao grafo com os atributos
for _, row in df_segments.iterrows():
    start = row['Cruzamento_1']
    end = row['Cruzamento_2']
    length = row['Comprimento_m']
    cost = row['Custo_Excavacao']
    direction = row['Sentido']
    
    # Arestas com custo de escavação como peso (opcional: usar comprimento)
    G.add_edge(start, end, weight=cost, length=length, direction=direction)

# Visualizar o grafo
plt.figure(figsize=(10, 10))

# Posicionar os nós de forma mais legível (uso do layout de força)
pos = nx.spring_layout(G, k=0.15, iterations=20)

# Desenhar o grafo
nx.draw(G, pos, with_labels=True, node_size=500, node_color="skyblue", font_size=10, font_weight="bold", edge_color="gray")

# Exibir os custos como rótulos nas arestas
edge_labels = nx.get_edge_attributes(G, 'weight')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

# Exibir a visualização
plt.title("Grafo da Cidade - Cruzamentos e Segmentos")
plt.savefig('grafo_cidade.png', format='png', dpi=300)
plt.show()
