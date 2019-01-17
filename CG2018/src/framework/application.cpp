#include "application.h"
#include "utils.h"
#include "image.h"

int modo = 0;
int changeRoute = 0;
float count = 0;
int size = 1000;
float r = rand();
int *arrayX = new int[size];
int *arrayY = new int[size];
int *randoms = new int[size];
int clicX = 0;
int clicY = 0;

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
void bigerPixel(Image* img)
{
	int randomColor1 = (((frand()) * 255) % 255);
	int randomColor2 = (((frand()) * 255) % 255);
	int randomColor3 = (((frand()) * 255) % 255);
	for(int x = 380; x<420; x++)
		for (int y = 280; y < 320; y++) {
			img->setPixelSafe(x, y, Color(randomColor1, randomColor2, randomColor3)); //random color
		}
}
void spiral(Image* img, float x, float y) {
	float angle = 0.0f;

	// Space between the spirals
	int a = 2, b = 2;
	float x1, y1;
	for (int i = 0; i < 150; i = i++)
	{
		angle = 0.1 * i;
		x1 = (a + b * angle) * cos(angle);
		y1 = (a + b * angle) * sin(angle);
		img->setPixelSafe(x1 + x , y1 + y, Color(255, 255, 255));
	}
}

void circle(Image* img, int posX, int posY) {
	float radius1 = 100 * count; // radius for the big circle
	float radius2 = 50 * count; // radius for the small cirle

	for (int angle = 0; angle < 360; angle += 1) {
		// calculate x and y by using parametic formulas of each circle
		int x1 = (radius1 * cos(angle));
		int y1 = (radius1 * sin(angle));
		int x2 = (radius2 * cos(angle));
		int y2 = (radius2 * sin(angle));

		// moving cordinates toward center of the display for each circle
		int cx1 = posX + x1;
		int cy1 = posY + y1;
		int cx2 = posX + x2;
		int cy2 = posY + y2;
		
		// degradate the color until it disapears
		int colorChanging1 = 255 - count * 250;
		int colorChanging2 = 255 - (count - 0.15) * 200;

		if (colorChanging1 <= 0) {
			colorChanging1 = 0;
		}
		if (colorChanging2 <= 0) {
			colorChanging2 = 0;
		}

		// character which made the circle
		img->setPixelSafe(cx1, cy1, Color(colorChanging1, 0, 0));
		if (count > 0.15){
			img->setPixelSafe(cx2, cy2, Color(colorChanging2, 0, 0));
		}
	}
	count = count + 0.01;
}
void triangle(Image* img, int x, int y) {
	int i, j, k, n;
	n = 25;

	for (k = x; k <= n; k++)
	{
		for (j = y; j <= n - k; j++)
			img->setPixelSafe(k, j, Color(255, 255, 255));
		/*for (i = y; i <= 2 * k - 1; i++)
			img->setPixelSafe(i, j, Color(255, 255, 255));*/
	}
}
void circleSimple(Image* img, int posX, int posY) {
	float radius = 25; // radius for the big circle

	for (int angle = 0; angle < 360; angle += 1) {
		// calculate x and y by using parametic formulas of each circle
		int x = (radius * cos(angle));
		int y = (radius * sin(angle));

		// moving cordinates toward center of the display for each circle
		int cx = posX + x;
		int cy = posY + y;

		// character which made the circle
		img->setPixelSafe(cx, cy, Color(255, 255, 255));
	}
}
void drawForms(Image* img)
{
	circleSimple(img, 200, 200);
	circleSimple(img, 600, 400);
	spiral(img, 200, 300);
	spiral(img, 600, 300);
	triangle(img, 400, 300);

}
void dividePixel(Image* img) {
	int randomColor1 = (((frand()) * 255) % 255);
	int randomColor2 = (((frand()) * 255) % 255);
	int randomColor3 = (((frand()) * 255) % 255);

		//Down left
		for (int x = 380; x < 400; x++)
			for (int y = 280; y < 300; y++) {
				if (changeRoute == 1) {
					for (int z = 180; z < 201; z++) {
						img->setPixelSafe(z + 20 + 40 * -sin(count + 1.45), y + 100*cos(3*count), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x - count * 40, y, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Down right
		for (int x = 400; x < 420; x++)
			for (int y = 280; y < 300; y++) {
				if (changeRoute == 1) {
					for (int z = 80; z < 101; z++) {
						img->setPixelSafe(x, z + 20 + 40 * -sin(count + 1.45), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x, y - count * 40, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Up left
		for (int x = 380; x < 400; x++)
			for (int y = 300; y < 320; y++) {
				if (changeRoute == 1) {
					for (int z = 480; z < 501; z++) {
						img->setPixelSafe(x, z + 20 + 40 * sin(count + 1.45), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x , y + count * 40, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		//Up right
		for (int x = 400; x < 420; x++)
			for (int y = 300; y < 320; y++) {
				if (x + count * 40 > 600) {
					changeRoute = 1;
				}
				if (changeRoute == 1) {
					for (int z = 580; z < 601; z++) {
						img->setPixelSafe(z + 20 + 40 * sin(count + 1.45), y + 100*-cos(3 * count), Color(randomColor1, randomColor2, randomColor3)); //random color
					}
				}
				else {
					img->setPixelSafe(x + count * 40, y, Color(randomColor1, randomColor2, randomColor3)); //random color
				}
			}
		count = count + 0.05;
}

void drawSnow(Image* img) {
	for (int i = 0; i < size; i++) {
		int x1 = arrayX[i] + sin(count * (randoms[i] % 10 + 3)) * 20;
		int x2 = arrayX[i] + sin(count * (randoms[i] % 10 + 3)) * 20 + 1;
		int y1 = arrayY[i] - count * (arrayX[i] % 40) + 3;
		int y2 = arrayY[i] - count * (arrayX[i] % 40) + 3 + 1;
		if (y1 < 0) {
			y1 = y1 + 600;
			y2 = y2 + 600;
		}
		img->setPixelSafe(x1, y1 , Color(255, 255, 255));
		img->setPixelSafe(x2, y1, Color(255, 255, 255)); 
		img->setPixelSafe(x1, y2, Color(255, 255, 255)); 
		img->setPixelSafe(x2, y2, Color(255, 255, 255)); 
	}
	count = count + 0.001;
}
//render one frame
void Application::render(void)
{

	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer( window_width, window_height );
	Image framebuffer2(800, 600);

	if (modo == 1){
		
		framebuffer2.fill(Color(0, 0, 0));
		dividePixel(&framebuffer);
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
		count = 0;
		changeRoute = 0;
		modo = 0;
		
	}
	if (keystate[SDL_SCANCODE_1]) //if key 1 is pressed
	{
		count = 0;
		changeRoute = 0;
		modo = 1;
	}
	if (keystate[SDL_SCANCODE_2]) //if key 2 is pressed
	{
		count = 0;
		modo = 2;
	}
	if (keystate[SDL_SCANCODE_3]) //if key 2 is pressed
	{
		count = 0;
		modo = 3;
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
		if (modo == 3) {
			if (size < 0) {
				size = 0;
			}
			else {
				size = size - 100;
			}
			if (size == 0) {
				size = size + 1000;
			}
			
			
			
		}
		else {
			clicX = mouse_position.x;
			clicY = mouse_position.y;
			count = 0;
			modo = 5;
		}
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
	for (int i = 0; i < size; i++) {
		arrayX[i] = (rand() % 800);
	}
	for (int i = 0; i < size; i++) {
		arrayY[i] = (rand() % 600);
	}
	for (int i = 0; i < size; i++) {
		randoms[i] = rand();
	}
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
