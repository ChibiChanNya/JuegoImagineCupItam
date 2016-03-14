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
    
    windowWidth = window->getSize().x;
    windowHeight = window->getSize().y;
    cargaJuego();
}
