# Trabalho de Métodos Numéricos 2

Essa branch*[gui]* contém testes de UI para este projeto, utilizando a [biblioteca Dear ImGui](https://github.com/ocornut/imgui).

O código fonte do projeto está em ./src, a maioria dos arquivos de header são implementações de métodos numéricos.

## Como compilar

Primeiramente, instale o SDL2, que é a unica dependência do projeto que não está incluida no repositório:

```bash
# MSYS2 mingw:
pacman -S mingw-w64-x86_64-SDL2

# Debian acho
apt install libsdl2-dev

# TODO Descobrir o pacote pra outras plataformas,
```

Depois só compilar com o cmake, independente da plataforma: *(Se eu tiver configurado tudo direito)*

```bash
mkdir build
cd build

# Mude -G pra outro gerador se você utiliza outro (eg. Ninja)
cmake -G "Unix Makefiles" ..

# Compilar com o make no nosso caso
make
```

> Na verdade mesmo eu só tava afim de testar como usar a ImGui e precisava de qualquer desculpa, não é como se tivesse muita coisa pra mostrar na tela nesse projeto.
