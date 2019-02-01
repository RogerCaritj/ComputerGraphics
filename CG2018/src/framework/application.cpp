#include "application.h"
#include "utils.h"
#include "image.h"

Teneis que implementar el algoritmo de pintado de lineas, circulos y rellenado de triangulos.

//Debeis implementar los siguientes métodos de la clase Image :
//	void drawLine(int x0, int y0, int x1, int y1, Color & c);
//	void drawCircle(int x, int y, int r, Color & c, bool fill);
//	void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color & c, bool fill);
//Para las lineas usad DDA, si al final teneis tiempo y quereis probad de implementar el algoritmo de bresenham(es mucho mas rapido) mejor.
//Si programais bresenham aseguraos de que las lineas de bresenham funcionan en todos los octantes.
//Permitid al usuario poder clickar en la pantalla e ir añadiendo nuevos puntos(tanto para lineas, 
//como para circulos y triangulos), no es valido que los valores de los vertices de las primitivas ya vengan definidos por codigo.
//Las primitivas tienen que poderse pintar sobre la imagen que ya hay pintada, de manera que el usuario pueda pintar un circulo, 
//luego una linea, luego un triangulo, luego otro circulo, y se vea el resultado con todas ellas pintadas, como en cualquier aplicacion de 
//dibujo(no vale ir borrando el framebuffer cada vez, intentad crear un framebuffer global donde vayais acumulando las primitivas).
//Permitir al usuario elegir qué figura pintar usando el teclado(p.e: 1. DDA, 2. Bresenham, 3. Circulos, 4. Triangulos) y tratad que no haya 
//que hacer combinaciones raras de teclado para completar las figuras, que baste con hacer dos clicks en la pantalla para definir una linea, 
//dos para definir un circulo(primero centro, segundo borde del circulo) o tres para un triangulo.

int mode = 0;

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//here add your init stuff
}

//Draw a line using DDA Algorithm
void drawLine(Image img ,int x0, int y0, int x1, int y1, Color & c) {
	
	//DDA Algorithm
	float x = 0, y = 0;
	float dx, dy;
	int steps;

	dx = x1 - x0; //difference of x
	dy = y1 - y0; //difference of y
	x = x0 + sgn(x0)*0.5; //to see if the lines are going down or up (negative of positive)
	y = y0 + sgn(x0)*0.5; 
	
	if (abs(dx) > abs(dy))
		steps = abs(dx); //calculate the number of iterations to paint the pixels
	else
		steps = abs(dy);

	float Xincr = dx / (float)steps; //increment for x in each pixel
	float Yincr = dy / (float)steps; //increment for y in each pixel

	for (int v = 0; v < steps; v++)
	{
		x = x + Xincr; //paint each pixel every Xincr
		y = y + Yincr; //paint each pixel every Yincr
		setPixelSafe(round(x), round(y), c);
	}
}

//Draw a circle given position and radious
void drawCircle(Image img, int x, int y, int r, Color & c, bool fill) {
	
	int x, y, v;

	x1 = 0;
	y1 = r;
	v = 1 - r;
	setPixel(x, y, c); //paint the center point of the circle
	while (y > x) {
		if (v < 0) {
			v = v + 2 * x + 3;
			x++;
		}
		else {
			v = v + 2 * (x - y) + 5;
			x++;
			y--;
		}
		//Solve the problem of drawing in each octant
		setPixelSafe(x, y, c);
		setPixelSafe(x + x1, y + y1, c); 
		setPixelSafe(x - x1, y + y1, c);
		setPixelSafe(x + x1, y - y1, c);
		setPixelSafe(x - x1, y - y1, c);
		setPixelSafe(x + y1, y + x1, c);
		setPixelSafe(x - y1, y + x1, c);
		setPixelSafe(x + y1, y - x1, c);
		setPixelSafe(x - y1, y - x1, c);

		if (fill == true) {								
			for (int i = -x; i < x; i++) {				
				for (int j = -y; j < y; j++) {
					setPixelSafe(x + i, y + j, c);
				}
			}
			for (int i = -y; i < y; i++) {
				for (int j = -x; j < x; j++)
					setPixelSafe(x + i, y + j, c);
			}
		}
	}
}

//Draw a triangle given 3 dots
void drawTriangle(Image img, int x0, int y0, int x1, int y1, int x2, int y2, Color & c, bool fill) {

	//Draw the triangle
	drawLine(img, x0, y0, x1, y1, c);
	drawLine(img, x1, y1, x2, y2, c);
	drawLine(img, x2, y2, x0, y0, c);
	if (fill == true) {
		//Fill inside the triangle
	}
	
}

//render one frame
void Application::render(void)
{

	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer( window_width, window_height );
	if (modo == 1){
		framebuffer.fill(Color(0, 0, 0));
		drawLine(&framebuffer, 0, 0, 500, 500, Color(255, 255, 255));
		showImage(&framebuffer);
	}
	else if (modo == 2) {
		spiral(&framebuffer, 400, 300);
		drawForms(&framebuffer);
		showImage(&framebuffer);
	}
	else if (modo == 3) {
		framebuffer2.fill(Color(0, 0, 0));
		drawSnow(&framebuffer);
		showImage(&framebuffer);
	}
	else if (modo == 4) {
		framebuffer2.fill(Color(0, 0, 0));
		//drawImage(&framebuffer3);
		showImage(&framebuffer3);
	}
	else if (modo == 5) {
		circle(&framebuffer2, clicX, clicY);
		showImage(&framebuffer2);
	}
	else{
		framebuffer2.fill(Color(0, 0, 0));
		bigerPixel(&framebuffer);
		showImage(&framebuffer);
	}

	//here you can add your code to fill the framebuffer

	//send image to screen
	
}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (keystate[SDL_SCANCODE_SPACE]) //if key space is pressed
	{
		mode = 0;
	}
	if (keystate[SDL_SCANCODE_1]) //if key 1 is pressed
	{
		mode = 1;
	}
	if (keystate[SDL_SCANCODE_2]) //if key 2 is pressed
	{
		mode = 2;
	}
	if (keystate[SDL_SCANCODE_3]) //if key 2 is pressed
	{
		mode = 3;
	}
	if (keystate[SDL_SCANCODE_4]) //if key 2 is pressed
	{
		mode = 4;
	}


	//to read mouse position use mouse_position
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch(event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			exit(0); 
			break; //ESC key, kill the app
	}
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //LEFT mouse pressed
	{
		
	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
