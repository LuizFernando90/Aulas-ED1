# 🛡️ Meu Jogo Knight — Um projeto feito com C e Allegro

[![Licença: MIT](https://img.shields.io/badge/Licen%C3%A7a-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Olá! 👋 Seja bem-vindo ao meu projeto de jogo 2D. 

Esta é uma aventura no estilo *survivor-like* (inspirada em jogos como **Vampire Survivors**) que desenvolvi como trabalho acadêmico. Nele, você controla um cavaleiro, coleta moedas, enfrenta hordas de golems e gerencia power‑ups usando uma estrutura de dados **fila** que implementei do zero. Tudo feito em **C** com a biblioteca **Allegro 5**.

---

## 🎮 Sobre o jogo – o que você vai encontrar

A ideia central é simples: **sobreviver o máximo de tempo possível** enquanto acumula pontos. Para isso:

- **Movimentação:** use `W`, `A`, `S`, `D` para andar pelo mapa.
- **Moedas:** colete as moedas douradas. Cada uma vale +10 pontos.
- **Power‑ups:** a cada 3 moedas coletadas, um power‑up é gerado e entra em uma **fila**. Você pode ver quantos tem na fila no canto superior esquerdo.
- **Uso dos power‑ups:** pressione a tecla `E` para usar o próximo da fila. Cada uso dá +50 pontos (ou +20 se você pegar o power‑up flutuante).
- **Inimigos:** golems perseguem você. Se encostarem, você perde 5 pontos.
- **Leaderboard:** suas pontuações são salvas num arquivo `Scores.txt` e exibidas no canto direito da tela.
- **Persistência:** a fila de power‑ups é salva em `powerups.bin`. Quando você reabre o jogo, ela é carregada automaticamente.

---

## 🧰 Tecnologias e ferramentas

- **Linguagem:** C (a base de tudo)
- **Biblioteca gráfica:** Allegro 5 (gerencia janela, imagens, teclado e timer)
- **Estrutura de dados:** Fila (implementada manualmente, com inserção, remoção, salvamento e carregamento)
- **Persistência:** arquivos `.txt` (para scores) e `.bin` (para a fila)

---

## 🏗️ Como organizei o código – a modularização

Uma das partes que mais me orgulha neste projeto é a **organização**. Separei a lógica do jogo da estrutura de dados, usando arquivos `.c` e `.h`:

---

## 🎨 Sobre os gráficos – de onde vieram

Os sprites e o cenário foram baixados do **[CraftPix.net](https://craftpix.net)** – um site maravilhoso com assets 2D gratuitos e pagos. Lá você encontra personagens, fundos, objetos e muito mais. Super recomendo para quem está começando a criar jogos.

---

## 🕹️ Como rodar o projeto (sim, é fácil!)

Se você quiser testar o jogo no seu computador, siga estes passos:

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/LuizFernando90/Aulas-ED1.git
   cd meu-repositorio

💭 O que aprendi com este projeto
Este trabalho foi uma grande experiência. Além de praticar C e Allegro, aprendi na prática:
Como gerenciar memória dinâmica (malloc/free) com segurança.
A importância de estruturas de dados (a fila encaixou perfeitamente para os power‑ups).
Como salvar e carregar dados em arquivos binários – algo que parecia complicado, mas é bem poderoso.
A arte de depurar animações e colisões (juro que o herói piscou por um tempão!).

🔮 Próximos passos – o que gostaria de melhorar
Se eu tivesse mais tempo, adicionaria:
🎵 Sons e música ambiente.
🧊 Mais tipos de power‑ups (congelar inimigos, velocidade, escudo).
🌙 Fases com dificuldade progressiva.
📝 Tela inicial para o jogador digitar o nome.
🎮 Suporte a joystick.

Feito com 💙 e muito café por Luiz Fernando Aº Lopes.
Obrigado por visitar este projeto! Se você gostou, deixe uma ⭐ no repositório – isso me incentiva a continuar criando.
