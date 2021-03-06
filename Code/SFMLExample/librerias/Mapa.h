class Mapa{
	public:
		GLuint textura;
		int width,height;
		Mapa(){
			width = 5087/3;
			height = 4916/3;
		}
		void cargaTextura(string nombreArchivo){
			cargaText(&textura,nombreArchivo);
		}
		void dibujaMapa(){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura);
			glBegin(GL_QUADS);
				glTexCoord2d(0,1);glVertex3f(0,0,-100);
				glTexCoord2d(0,0);glVertex3f(0,height,-100);
				glTexCoord2d(1,0);glVertex3f(width,height,-100);
				glTexCoord2d(1,1);glVertex3f(width,0,-100); 
			glEnd();
		}
};
