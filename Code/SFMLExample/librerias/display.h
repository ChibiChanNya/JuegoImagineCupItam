void display(RenderWindow* window){
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-x,-y,0);
    
    mapa.dibujaMapa();

    // Finally, display the rendered frame on screen
    window->display();

}
