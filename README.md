# Ruina
A 3D game engine, for experimenting with 3D graphics. The engine runs on OpenGL, 

## Creating and running tests

To add your own test, create a new subclass of Test in the /tests directory, include Test.h and wrap it in the test namespace. Modify the `OnUpdate` and `OnRender` methods to update and draw to the window, and modify `OnImGuiRender` to include any desired UI elements within the test.

Once you are ready to run your test, go to Main.cpp and add the following line of code:

```c++
test_menu->RegisterTest<test::TestMyNewTest>("My New Test");
```

Building and running the project will create a window displaying a menu of all the currently loaded tests.

## Wrapper classes

There are several wrapper classes to simplify the OpenGL functionality. These can all be found in the /src directory, or in its various sub-directories.

### Buffers

- **VertexBuffer**: Instantiating a VertexBuffer object with the necessary data will automatically generate, bind and buffer the data. To rebind the buffer, call `Bind()`. The data will be buffered with the `GL_STATIC_DRAW` flag by default.
- **IndexBuffer**: Functions identically to the VertexBuffer class.
- **VertexBufferLayout**: Call Push<T>(count) to automatically generate the data for a new vertex attribute. These will only be physically generated upon creating a VertexArray.
- **VertexArray**: Call `AddBuffer` while supplying a VertexBuffer and VertexBufferLayout to automatically setup the attribute layouts.

### Geometry

- **Vertex**: Basic struct containing fields for: 3D position values, normal vector values, rgba values, uv texture coordinates, and texture index
- **Cube**: Contains the raw vertex data for a Cube mesh, and methods for (re)generating index/vertex data. Takes an offset ivec3 for specifying a position relative to a chunk.
- **Chunk**: A cubic structure for storing multiple cubes, and rendering them in a single draw call. Use the `SetCube` method to add a new cube at a specified location relative to the chunk, and `GenerateRenderingData` to populate the `m_vertex_data` and `m_index_data` vectors with all the necessary cube vertex/index data.

### GUI

All of the ImGui wrapper classes are found in the /gui directory, and are generally self-explanatory. The `Draw()` method is used to draw the element when desired.

### Other

- **Texture**: The Texture constructor takes in a path and sets up all the necessary parameters for drawing the texture in a "sensible" mode (ie. with linear min/mag filtering, and clamping to edge). You can then call `Bind(slot)` to bind the texture for rendering.

- **Shader**: The Shader class currently takes in a Vertex and Fragment shader path, which it parses and compiles upon instantiation. You can then call `Bind()` to bind the shader. In order to set uniforms, there are several setters included in the class, such as `SetUniform1i` and `SetUniform4f` that take in the name of the uniform, and the data to be passed in.
