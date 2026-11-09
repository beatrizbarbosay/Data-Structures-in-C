<div align="center">

# ⚙️ Data Structures & Algorithms in C

**MC202 · University of Campinas (UNICAMP) 🇧🇷**  
*C · Algorithms · Memory Management · Problem Solving*

</div>

A collection of my programming assignments from **MC202 — Data Structures**, exploring how fundamental data structures work **from scratch in C**.

### 🚀 Selected implementations

| Lab | Project | Core concepts |
|:---:|---|---|
| [04](tarefa04/batcomputador.c) | Custom memory manager | Dynamic allocation, pointers, memory resizing |
| [05](tarefa05/sequencia.c) | Sequence editor | Singly linked lists, insertion, deletion, reversal |
| [06](tarefa06) | Snake simulation | Linked lists, dynamic 2D arrays, memory management |
| [07](tarefa07/otimizar.c) | Boolean expression optimizer | Binary trees, recursion, De Morgan's laws |
| [08](tarefa08/cidades.c) | Spatial city index | **Quadtree**, insertion, search, spatial queries |
| [09](tarefa09/cache.c) | Cache replacement simulation | **Binary heap**, priority management |
| [10](tarefa10/corretor.c) | Spelling checker | **Hash table**, collision handling with chaining |
| [12](tarefa12) | Distribution-center selection | **Graphs, adjacency matrices, Dijkstra's algorithm** |

More exercises are organized in folders `tarefa00`–`tarefa13`, including C fundamentals, arrays, string processing, and algorithmic problem solving.

### 🛠️ Running the code

The assignments are **independent programs**. Most have their own `Makefile` and input/output fixtures under `testes/`.

For example, from the repository root (with GCC and Make installed):

```bash
make -C tarefa09
./tarefa09/cache < tarefa09/testes/grande1.in
```

Individual lab behavior and required input formats vary. This is archived university coursework; not all exercises are complete or independently verified on modern systems.

