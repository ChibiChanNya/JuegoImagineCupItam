#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

double x,y;
double fr;
GLuint texture;
Image image;
float timeStep;
Music music;
SoundBuffer buffer;
Sound sound;

float personaje [16] = {
        // positions    // texture coordinates
         0,   0,  0, 0,
        40,   0,  1, 0,
        40,  40,  1, 1,
         0,  40,  0, 1,
    };

void cargaText(GLuint* textura, Image* image){
    // Load an OpenGL texture.
    // We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
    // but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
    *textura = 0;
    image->loadFromFile("sprite.png");
    glGenTextures(1, textura);
    glBindTexture(GL_TEXTURE_2D, *textura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
}
void init(RenderWindow* window){
	// Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window->getSize().x, window->getSize().y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window->getSize().x) / window->getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
}
void cargaCosas(){
    music.openFromFile("Song5.ogg");
    buffer.loadFromFile("canon.wav");
	sound.setBuffer(buffer);
	music.setLoop(true);
	music.play();
}
void idle(Clock* clock){
	timeStep = clock->restart().asMilliseconds();
	fr += timeStep*5/100;
	if(fr > 4) fr-= 4;
	if(Keyboard::isKeyPressed(sf::Keyboard::A)){
		x-= .1;
	}
	if(Keyboard::isKeyPressed(sf::Keyboard::D)){
		x+= .1;
	}
	if(Keyboard::isKeyPressed(sf::Keyboard::S)){
		y-= .1;
	}
	if(Keyboard::isKeyPressed(sf::Keyboard::W)){
		y+= .1;
	}
	if(Keyboard::isKeyPressed(sf::Keyboard::Space)){
		sound.play();
	}
}
void display(RenderWindow* window){
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glTexCoord2d(floor(fr)/4,1);glVertex3f(0,0,-100);
		glTexCoord2d(floor(fr)/4,0);glVertex3f(0,50,-100);
		glTexCoord2d((floor(fr)+1)/4,0);glVertex3f(50,50,-100);
		glTexCoord2d((floor(fr)+1)/4,1);glVertex3f(50,0,-100); 
	glEnd();
    glDrawArrays(GL_QUADS, 0, 4);

    // Finally, display the rendered frame on screen
    window->display();

}
int main()
{
    // Request a 24-bits depth buffer when creating the window
    ContextSettings contextSettings;
    contextSettings.depthBits = 24;

    // Create the main window
    RenderWindow window(sf::VideoMode(800, 600), "Juego", ::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

	cargaText(&texture,&image);
    init(&window);
    cargaCosas();

    // Create a clock for measuring the time elapsed
    Clock clock;

    // Start game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
                window.close();

            // Adjust the viewport when the window is resized
            if (event.type == Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }        
        idle(&clock);
        display(&window);
    }

    // Don't forget to destroy our texture
    glDeleteTextures(1, &texture);

    return EXIT_SUCCESS;
}
