import noise
import random

# Taille de l'image de bruit de Perlin
width = 28
height = 100

# Facteur d'échelle pour le bruit de Perlin
scale = 75.0

# Générer le bruit de Perlin
perlin = [[0 for y in range(height)] for x in range(width)]
for x in range(width):
    for y in range(height):
        perlin[x][y] = noise.pnoise2(x/scale, y/scale, octaves=6, persistence=0.5, lacunarity=2.0, repeatx=width, repeaty=height, base=0)

# Ajouter des taches d'astéroïdes
for i in range(200):
    x = random.randint(0, width-1)
    y = random.randint(0, height-1)
    size = random.randint(3, 8)
    for dx in range(-size, size+1):
        for dy in range(-size, size+1):
            if 0 <= x+dx < width and 0 <= y+dy < height:
                perlin[x+dx][y+dy] += random.uniform(0.5, 1.0)


# Normaliser les valeurs de bruit de Perlin entre 0 et 1
min_value = min(min(perlin))
max_value = max(max(perlin))
perlin = [[(p-min_value)/(max_value-min_value) for p in row] for row in perlin]

# Écrire le bruit de Perlin avec les taches d'astéroïdes dans un fichier texte
with open("map.txt", "w") as file:
    for y in range(height):
        for x in range(width):
            if perlin[x][y] < 0.6:
                file.write("0")
            else:
                file.write("1")
        file.write("\n")
