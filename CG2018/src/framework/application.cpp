#include "application.h"
#include "utils.h"
#include "image.h"

int modo = 0;
int changeRoute = 0;
float count = 0;

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
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
		//if you read mouse position from the event, careful, Y is reversed, use mouse_position instead
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
