# Gamenge::Renderer

**Author:** Matthew Mumau <mpmumau@gmail.com>  
**License:** MIT License (see LICENSE file for more information)

## Project Overview
Gamenge is a set of a game-related libraries, built in module form, and intended to be used ala-carte. The full suite of components to be included in the Gamenge project will include a 3D rendering engine, and entity-component simulation system, integration with Bullet 3D, an audio interface library and more. 

## Renderer Component
This repository contains the source for the Renderer component of the Gamenge suite. It may be used as a standalone 3D rendering library, or, as intended, in conjuction with other components in the Gamenge suite.

## Dependencies

You must install the GLEW, GLM and assimp packages prior to building this source, as they are dependencies of the project.

## Installation

CMake scripts are provided for a standard CMake installation process.

1. Clone this repository to a location of your choice.

2. Make a directory called `build` from the root of that directory.

3. Enter that directory (e.g. `cd build`).

4. Run cmake (e.g. `cmake ..`).

5. Run `make`.

6. Run `make install`.

## Including In Your Project

Simply require the package Gamenge::Renderer in your own CMake script.

## Use

The Gamenge::Renderer library focuses on a class that's part of the Gamenge namespace, called Gamenge::Renderer.

Create an instance of a `Gamenge::Renderer` object within your application, and call its `init` function to initialize its state.

Calls to that objects `render` function will renderer to the active OpenGL context, which you should have initialized prior to running the above functions.

## Renderables

The Renderer class iterates over a set of Renderable objects during a call to `render`. Those objects can be added to the collection of Renderable objects within the Renderer by calling `addRenderable` on the renderer. 

You must add OpenGL shaders, mesh objects and texture objects to the renderer prior to being able to add and render Renderables. Add those with the `addShader`, `addMesh` and `addTexture` functions prior to adding any renderables.

## More Information

Consult the documents in the `docs` folder for detailed information about the use of the above functions, and more.