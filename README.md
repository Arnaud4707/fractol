# 🌌 Fract'ol — Interactive Fractals with Audio & Animation

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg?style=flat&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![MiniLibX](https://img.shields.io/badge/Graphics-MiniLibX-orange)](https://harm-smits.github.io/42docs/libs/minilibx)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build](https://img.shields.io/badge/build-Makefile-red)](#-installation)

> 🇫🇷 Version française ci-dessous — 🇬🇧 English version below.

---

## 🇫🇷 Présentation

**Fract'ol** est une application interactive qui combine :
- **Fractales** (Mandelbrot, Julia, Buddhabrot, Burning Ship, Dragon, Menger Sponge, etc.)
- **Animations dynamiques**
- **Visualisations audio synchronisées avec la musique**

Le rendu est calculé en **temps réel** grâce au multithreading et optimisé avec **FFTW** pour l’analyse spectrale audio.  
Le tout est affiché avec **MiniLibX** (MLX).

---

## ✨ Fonctionnalités

- 🔮 **Fractales multiples** : Mandelbrot, Julia, Burning Ship, Dragon, Menger Sponge, Buddhabrot…
- 🎶 **Analyse audio (FFT)** : spectre sonore transformé en animations visuelles
- 🎨 **Couleurs dynamiques** : palettes changeables en direct
- 🖱️ **Interaction temps réel** : zoom, déplacements, rotation
- 🖼️ **Menu visuel** : introduction, overlays et effets graphiques

---

## 🛠️ Installation

### Prérequis
- Linux (Ubuntu/Debian conseillé)
- `gcc`, `make`
- Bibliothèques :
  - **MiniLibX** (inclus dans le dépôt)
  - **libft** (inclus dans le dépôt)
  - **FFTW3**
  - **libsndfile**

### Installer les dépendances :
```
bash
sudo apt-get install build-essential libfftw3-dev libsndfile1-dev
```

## Compilation
- make
- Nettoyer :
    - make clean    # Supprimer les objets
    - make fclean   # Nettoyer + supprimer binaire
    - make re       # Recompiler proprement

## 🎮 Utilisation

### Lancer le programme
  - ./prog <fractale> [paramètres]

### Exemples
  - ./prog Mandelbrot
  - ./prog Julia 0.285 0.01
  - ./prog Buddhabrot

## 🎹 Contrôles

- Flèches : déplacer la fractale

- Molette souris : zoom avant/arrière

- R, G, B, Y, C, Espace : changer de palette

- S / P : pause / reprise animation Julia

- Échap : quitter

## 📂 Organisation du projet

- fractal/ → fractales & animations

- menu/ → menus, intro, effets (cube, vagues, etc.)

- mlx/ → MiniLibX

- libft/ → fonctions utilitaires

- Makefile → compilation

## 👤 Auteur

Projet développé par [Arnaud Mugisha / Arnaud4707].
Basé sur le projet fractol de l’école 42, enrichi avec audio, animations et menus.
