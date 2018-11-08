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

  For interactive prompt run the app without any arguments

  ```bash
  ./graphalgs
  ```

  To read graph from file, containing adjacency matrix, pass filename as argument

  ```bash
  ./graphalgs input_file
  ```

  Note: the first string in `input_file` should contain the vertex count

### Visualisation

  To visualise a graph write it as JSON in file `graph.json` and place it with `visual.html`.

  Note: `visual.html` **WILL NOT WORK IN CHROME**.