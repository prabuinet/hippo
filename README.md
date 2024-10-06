# hippo

following game engine series from:

[tutorial series](https://www.youtube.com/watch?v=wMk182vENjk&list=PL7lh9ryRNHSIzqKzEdYPG94B0uvfqhHpb&ab_channel=Progrematic)

https://github.com/progrematic/hippo


### to generate sln
python cli.py gensln

### build
python cli.py buildsln

### run
python cli.py run

### build and run
python cli.py buildsln run


### Graphics pipeline

- vbo
- ebo
- vao
- meshes
- shaders
- hippo pipeline architecture


#### vbo
- contigous chunk of memory
- lives on gpu
- used to refresent any data you want your gpu/shaders to access
- primarily used for:
  - vertex positions
  - textture uvs
  - normals
  - vertex colors
  - etc.,
- use single or multiple vbo:
  - if data is static use single vbo
  - if data is dynamic use multiple vbo
