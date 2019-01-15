#include "application.h"
#include "utils.h"
#include "image.h"

int modo = 0;
int changeRoute = 0;
float count = 0;
int size = 200;
float r = rand();
int *arrayX = new int[size];
int *arrayY = new int[size];
int *randoms = new int[size];

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

void drawForms(Image* img) 
{
	int randomColor1 = (((frand()) * 255) % 255);
	int randomColor2 = (((frand()) * 255) % 255);
	int randomColor3 = (((frand()) * 255) % 255);

	//Right
	
		for (int y = 298; y < 302; y++) {
			if ((420 + count) > 470) {
				for (int x = 420; x < 470; x++) {
					img->setPixelSafe(x, y, Color(255, 0, 0)); //random color
				}
			}
			else {
				img->setPixelSafe(420 + count, y, Color(255, 0, 0)); //random color
			}

		}
	count = count + 0.1;	
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
void bigPixel(Image* img, int a) {
	img->setPixelSafe(a % 800, a % 600 , Color(255, 255, 255)); //random color
	img->setPixelSafe(a % 800 + 1, a % 600, Color(255, 255, 255)); //random color
	img->setPixelSafe(a % 800, a % 600 + 1, Color(255, 255, 255)); //random color
	img->setPixelSafe(a % 800 + 1, a % 600 + 1, Color(255, 255, 255)); //random color
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
		img->setPixelSafe(x1, y1 , Color(255, 255, 255)); //random color
		img->setPixelSafe(x2, y1, Color(255, 255, 255)); //random color
		img->setPixelSafe(x1, y2, Color(255, 255, 255)); //random color
		img->setPixelSafe(x2, y2, Color(255, 255, 255)); //random color
	}
	count = count + 0.01;
}
//render one frame
void Application::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	Image framebuffer( window_width, window_height );

	if (modo == 1){
		dividePixel(&framebuffer);
		showImage(&framebuffer);
	}
	else if (modo == 2) {
		bigerPixel(&framebuffer);
		drawForms(&framebuffer);
		showImage(&framebuffer);
	}
	else if (modo == 3) {
		drawSnow(&framebuffer);
		showImage(&framebuffer);
	}
	else{
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
			int a = size + 200;
			for (int i = size; i < a; i++) {
				arrayX[i] = (rand() % 800);
			}
			for (int i = size; i < a; i++) {
				arrayY[i] = (rand() % 600);
			}
			for (int i = size; i < a; i++) {
				randoms[i] = rand();
			}
			size = size + 200;
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
