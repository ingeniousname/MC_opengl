<h2>MC-OpenGL</h2>

A simple minecraft-like scene developed using OpenGL library for drawing.

The project has only very basic functionalities like placing/destroying blocks, walking, noise terrain generator, simple sun lighting. I've done in some time ago and it requires heavy refactoring, but I can't be bothered right now (university). If I were to change it, I'd probably start from scratch - writing this code was mostly an OpenGL learning experience for me.

Move using WSAD, jump with space, place/destroy blocks with left/right mouse button.

Compilation requires linking -lglfw3, -lglew32 and -lopengl32 , hopefully my cmake file works for you :)