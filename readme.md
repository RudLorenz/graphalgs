# Graph algos

  A simple graph class with nice visualisation.

## Requirements

  1. C++11 compatible compiler
  2. CMake

## Usage

  Clone the repository:

  ```bash
  git clone https://github.com/RudLorenz/graphalgs.git && cd graphalgs
  ```

  Let CMake create required makefiles and compile the project with make

  ```bash
  mkdir build
  cd build
  cmake ../
  make
  ```

  For Windows Visual Studio users CMake will automatically create all required project files: `graphsalg.sln`.

### Examples

  Show help file

  ```bash
  ./graphsalg -h
  ```

  Find all hamilton path in graph from interactive input

  ```bash
  ./graphsalg -i --hamilton
  ```

  Read graph from file, find all articulation points, write graph as json

  ```bash
  ./graphsalg -f graph.in -a -o graph.json -j
  ```

  Read graph from file, find all articulation point, delete if any found, write result graph as json

  ```bash
  ./graphsalg -f graph.in -a -d -o graph.json -j
  ```

  **Note**: the first string in `input_file` should contain the vertex count. Same goes for non interactive matrix input: the first value should be vertex count (or matrix side).

  A graph sample can be found in `sample` directory.

### Visualisation

  To visualise a graph write it as JSON in file `graph.json` and place it with `visual.html`.

  Note: `visual.html` **WILL NOT WORK IN CHROME**.